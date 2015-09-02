#include "stdafx.h"
#include "Mesh.h"


CMesh::CMesh(LPDIRECT3DDEVICE9 pDevice) : m_pDevice(pDevice)
{

}


CMesh::~CMesh(void)
{
	//释放相关资源
	SAFE_DELETE_ARRAY(m_pMaterials);

	if (m_pTextures)
	{
		for (unsigned int i = 0; i < m_dwNumMtrls; i++)
		{
			SAFE_RELEASE(m_pTextures[i]);
		}
		SAFE_DELETE_ARRAY(m_pTextures);
	}

	SAFE_RELEASE(m_pMesh);
}

void CMesh::CreateMesh(LPSTR filename)
{
	LPD3DXBUFFER pAdjBuffer = NULL;
	LPD3DXBUFFER pMtrlBuffer = NULL;

	D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, m_pDevice, &pAdjBuffer, &pMtrlBuffer, NULL, &m_dwNumMtrls, &m_pMesh);

	//读取材质和纹理数据
	D3DXMATERIAL *pMtrl = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();

	m_pMaterials = new D3DMATERIAL9[m_dwNumMtrls];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMtrls];

	for (unsigned int i = 0; i < m_dwNumMtrls; i++)
	{
		//材质信息
		m_pMaterials[i] = pMtrl[i].MatD3D;

		m_pTextures[i] = NULL;
		D3DXCreateTextureFromFileA(m_pDevice, pMtrl[i].pTextureFilename, &m_pTextures[i]);

	}

	//优化网格模型
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_STRIPREORDER, (DWORD*)pAdjBuffer->GetBufferPointer(), NULL, NULL, NULL);

	SAFE_RELEASE(pAdjBuffer);
	SAFE_RELEASE(pMtrlBuffer);
	
}

void CMesh::DrawMesh(const D3DXMATRIXA16& matWorld)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	///Alpha Blend相关

	//开启Alpha融合
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//设置融合因子
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//设置源融合因子
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//设置目标融合因子
	//设置融合运算方式(可以省略，DX默认即为D3DBLENDOP_ADD的融合运算方式)
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	
	//绘制Mesh
	for (int i = 0; i < m_dwNumMtrls; i++)
	{
		m_pDevice->SetMaterial(&m_pMaterials[i]);
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}

//增加Alpha值的函数
void CMesh::AddAlphaValue()
{
	for (unsigned int i = 0; i < m_dwNumMtrls; i++)
	{
		m_pMaterials[i].Diffuse.a += 0.1f;
		if (m_pMaterials[i].Diffuse.a > 1.0f)
			m_pMaterials[i].Diffuse.a = 1.0f;
	}
}

//减少Alpha值的函数
void CMesh::ReduceAlphaValue()
{
	for (unsigned int i = 0; i < m_dwNumMtrls; i++)
	{
		m_pMaterials[i].Diffuse.a -= 0.1f;
		if (m_pMaterials[i].Diffuse.a < 0.0f)
			m_pMaterials[i].Diffuse.a = 0.0f;
	}
}