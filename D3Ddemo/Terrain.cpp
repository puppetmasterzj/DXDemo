#include "stdafx.h"
#include "Terrain.h"
#include <fstream>


CTerrain::CTerrain(IDirect3DDevice9 *pDv)
{
	//各种初始化
	m_pDevice = pDv;
	m_pTexture = NULL;
	m_pIndexBuffer = NULL;
	m_pVertexBuffer = NULL;
	m_nCellsPerRow = 0;
	m_nCellsPerCol = 0;
	m_nVertsPerRow = 0;
	m_nVertesPerCol = 0;
	m_nNumVertices = 0;
	m_fTerrainWidth = 0.0f;
	m_fTerrainDepth = 0.0f;
	m_fCellSpacing = 0.0f;
	m_fHeightScale = 0.0f;
}

CTerrain::~CTerrain(void)
{
}


bool CTerrain::LoadTerrainFromFile(std::string RawFilename, std::string TextureFilename)
{
	//打开文件
	using namespace std;
	ifstream inFile;
	inFile.open(RawFilename, std::ios::binary);
	//移动到文件尾
	inFile.seekg(0, std::ios::end);
	std::vector<BYTE> inData(inFile.tellg());
	inFile.seekg(std::ios::beg);
	inFile.read((char*)&inData[0], inData.size());
	inFile.close();

	m_vHeightInfo.resize(inData.size());
	for (unsigned int i = 0; i < inData.size(); i++)
	{
		m_vHeightInfo[i] = inData[i];
	}

	//加载地形纹理
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, TextureFilename.c_str() ,&m_pTexture)))
		return false;

	return true;
}

bool CTerrain::InitTerrain(int nRows, int nCols, float fSpace, float fScale)
{
	m_nCellsPerRow = nRows;
	m_nCellsPerCol = nCols;
	m_fCellSpacing = fSpace;
	m_fHeightScale = fScale;
	m_fTerrainWidth = m_fCellSpacing * m_nCellsPerRow;
	m_fTerrainDepth = m_fCellSpacing * m_nCellsPerCol;
	m_nVertsPerRow = m_nCellsPerRow + 1;
	m_nVertesPerCol = m_nCellsPerCol + 1;
	m_nNumVertices = m_nVertsPerRow * m_nVertesPerCol;

	//将高度与高度系数相乘，得到范围更广的高度
	for (unsigned int i = 0; i < m_vHeightInfo.size(); i++)
	{
		m_vHeightInfo[i] *= m_fHeightScale;
	}

	//处理顶点
	//创建
	if (FAILED(m_pDevice->CreateVertexBuffer(m_nNumVertices * sizeof(TERRAINVERTEX), D3DUSAGE_WRITEONLY, TERRAINVERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0)))
		return false;
	//加锁
	TERRAINVERTEX *pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	
	//访问，赋值
	float fStartX = -m_fTerrainWidth / 2.0f; //起点的X坐标
	float fEndX   =  m_fTerrainWidth / 2.0f; //终点的X坐标
	float fStartZ =  m_fTerrainDepth / 2.0f; //起点的Z坐标
	float fEndZ   = -m_fTerrainDepth / 2.0f; //终点的Z坐标
	float fCoordU = 3.0f / (float)m_nCellsPerRow;//指定纹理的横坐标
	float fCoordV = 3.0f / (float)m_nCellsPerCol;//指定纹理的纵坐标

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z > fEndZ; z -= m_fCellSpacing, i++)
	{
		j = 0;
		for (float x = fStartX; x < fEndX; x += m_fCellSpacing, j++)
		{
			nIndex = i * m_nCellsPerRow + j; //指定顶点在顶点缓存的位置
			pVertices[nIndex] = TERRAINVERTEX(x, m_vHeightInfo[nIndex], z, j * fCoordU, i * fCoordV);//将高度值以及纹理坐标信息赋值
			nIndex++;
		}
	}
	
	//解锁
	m_pVertexBuffer->Unlock();

	//处理索引

	//创建索引
	if(FAILED(m_pDevice->CreateIndexBuffer(m_nNumVertices * 6 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
		return false;
	
	//加锁
	WORD* pIndices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	//赋值
	nIndex = 0;
	for (int row = 0; row < m_nCellsPerRow - 1; row++)//行遍历
	{
		for (int col = 0; col < m_nCellsPerCol - 1; col++)//列遍历
		{
			//三角形ABC三个顶点
			pIndices[nIndex] = row * m_nCellsPerRow + col;//A
			pIndices[nIndex + 1] = row * m_nCellsPerRow + col + 1;//B
			pIndices[nIndex + 2] = (row + 1) * m_nCellsPerRow + col;//C

			//三角形CBD三个顶点
			pIndices[nIndex + 3] = (row + 1) * m_nCellsPerRow + col;//C
			pIndices[nIndex + 4] = row * m_nCellsPerRow + col + 1;//B
			pIndices[nIndex + 5] = (row + 1) * m_nCellsPerRow + col + 1;//D

			nIndex += 6;
		}
	}
	
	//解锁
	m_pIndexBuffer->Unlock();
	
	return true;
}

bool CTerrain::RenderTerrain(D3DXMATRIX *pMatWorld, bool bRenderFrame)
{
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TERRAINVERTEX));
	m_pDevice->SetFVF(TERRAINVERTEX::FVF);
	m_pDevice->SetIndices(m_pIndexBuffer);
	m_pDevice->SetTexture(0, m_pTexture);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetTransform(D3DTS_WORLD, pMatWorld);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nNumVertices, 0, m_nNumVertices * 2);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pDevice->SetTexture(0, 0);
	

	return true;
}