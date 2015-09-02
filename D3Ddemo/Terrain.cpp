#include "stdafx.h"
#include "Terrain.h"
#include <fstream>


CTerrain::CTerrain(IDirect3DDevice9 *pDv)
{
	//���ֳ�ʼ��
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
	//���ļ�
	using namespace std;
	ifstream inFile;
	inFile.open(RawFilename, std::ios::binary);
	//�ƶ����ļ�β
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

	//���ص�������
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

	//���߶���߶�ϵ����ˣ��õ���Χ����ĸ߶�
	for (unsigned int i = 0; i < m_vHeightInfo.size(); i++)
	{
		m_vHeightInfo[i] *= m_fHeightScale;
	}

	//������
	//����
	if (FAILED(m_pDevice->CreateVertexBuffer(m_nNumVertices * sizeof(TERRAINVERTEX), D3DUSAGE_WRITEONLY, TERRAINVERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0)))
		return false;
	//����
	TERRAINVERTEX *pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	
	//���ʣ���ֵ
	float fStartX = -m_fTerrainWidth / 2.0f; //����X����
	float fEndX   =  m_fTerrainWidth / 2.0f; //�յ��X����
	float fStartZ =  m_fTerrainDepth / 2.0f; //����Z����
	float fEndZ   = -m_fTerrainDepth / 2.0f; //�յ��Z����
	float fCoordU = 3.0f / (float)m_nCellsPerRow;//ָ������ĺ�����
	float fCoordV = 3.0f / (float)m_nCellsPerCol;//ָ�������������

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z > fEndZ; z -= m_fCellSpacing, i++)
	{
		j = 0;
		for (float x = fStartX; x < fEndX; x += m_fCellSpacing, j++)
		{
			nIndex = i * m_nCellsPerRow + j; //ָ�������ڶ��㻺���λ��
			pVertices[nIndex] = TERRAINVERTEX(x, m_vHeightInfo[nIndex], z, j * fCoordU, i * fCoordV);//���߶�ֵ�Լ�����������Ϣ��ֵ
			nIndex++;
		}
	}
	
	//����
	m_pVertexBuffer->Unlock();

	//��������

	//��������
	if(FAILED(m_pDevice->CreateIndexBuffer(m_nNumVertices * 6 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
		return false;
	
	//����
	WORD* pIndices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	//��ֵ
	nIndex = 0;
	for (int row = 0; row < m_nCellsPerRow - 1; row++)//�б���
	{
		for (int col = 0; col < m_nCellsPerCol - 1; col++)//�б���
		{
			//������ABC��������
			pIndices[nIndex] = row * m_nCellsPerRow + col;//A
			pIndices[nIndex + 1] = row * m_nCellsPerRow + col + 1;//B
			pIndices[nIndex + 2] = (row + 1) * m_nCellsPerRow + col;//C

			//������CBD��������
			pIndices[nIndex + 3] = (row + 1) * m_nCellsPerRow + col;//C
			pIndices[nIndex + 4] = row * m_nCellsPerRow + col + 1;//B
			pIndices[nIndex + 5] = (row + 1) * m_nCellsPerRow + col + 1;//D

			nIndex += 6;
		}
	}
	
	//����
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