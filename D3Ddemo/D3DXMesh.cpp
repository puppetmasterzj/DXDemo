#include "stdafx.h"
#include "D3DXMesh.h"
#include "Picking.h"


D3DXMesh::D3DXMesh(LPDIRECT3DDEVICE9 pDevice)
	: IRenderRes(pDevice),
	  m_pMesh(NULL),
	  m_pMaterials(NULL),
	  m_pTextures(NULL),
	  m_dwNumMtrls(0),
	  m_pBoundingSphere(NULL)

{

}


D3DXMesh::~D3DXMesh(void)
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
	SAFE_RELEASE(m_pBoundingSphere);
}

HRESULT D3DXMesh::Init(LPCSTR filename)
{
	LPD3DXBUFFER pAdjBuffer = NULL;
	LPD3DXBUFFER pMtrlBuffer = NULL;

	HRESULT hr = D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, m_pDevice, &pAdjBuffer, &pMtrlBuffer, NULL, &m_dwNumMtrls, &m_pMesh);
	if (hr == S_OK)
	{
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

		//设置资源名称
		SetResourceName(filename);
	}

	return hr;
}

void D3DXMesh::CreateBoundingSphere(BoundingSphere* sphere)
{
	BYTE *v;
	//锁住缓冲区
	m_pMesh->LockVertexBuffer(0, (void**)&v);
	//计算包围盒信息，将包围盒信息存储在sphere中
	D3DXComputeBoundingSphere((D3DXVECTOR3*)v, m_pMesh->GetNumVertices(), D3DXGetFVFVertexSize(m_pMesh->GetFVF()), &sphere->m_vCenter, &sphere->m_fRadius);
	//解锁缓冲区
	m_pMesh->UnlockVertexBuffer();

	//创建网格包围球(网格资源模型)
	D3DXCreateSphere(m_pDevice, sphere->m_fRadius, 10, 10, &m_pBoundingSphere, NULL);
}

void D3DXMesh::Render(const LPD3DXMATRIX matrix)
{
	m_pDevice->SetTransform(D3DTS_WORLD, matrix);
	
	//绘制Mesh
	for (int i = 0; i < m_dwNumMtrls; i++)
	{
		m_pDevice->SetMaterial(&m_pMaterials[i]);
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}

	//包围盒采取线框填充
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pBoundingSphere->DrawSubset(0);
	//恢复渲染状态
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
