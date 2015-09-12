/*!
 * \file Mesh.h
 *
 * \author zhangjian_dev
 * \date 七月 2015
 *网格模型类：负责导入模型以及绘制模型
 * 
 */
#ifndef __D3DXMESH_H_
#define __D3DXMESH_H_
#pragma once
#include "stdafx.h"
#include "IRenderRes.h"
struct BoundingSphere;

class D3DXMesh : public IRenderRes
{
public:
	D3DXMesh(LPDIRECT3DDEVICE9 pDevice);
	~D3DXMesh(void);
	
	//创建网格对象
	virtual HRESULT Init(LPCSTR filename) override;

	//创建网格模型包围球
	void CreateBoundingSphere(BoundingSphere* sphere);

	//绘制网格对象
	virtual void Render(const LPD3DXMATRIX matrix);

	//获得原生网格资源指针
	LPD3DXMESH GetMeshPointer()
	{return m_pMesh;}

private:
	
	LPD3DXMESH m_pMesh;						//网格对象
	LPDIRECT3DTEXTURE9* m_pTextures;		//网格纹理信息
	D3DMATERIAL9* m_pMaterials;				//网格材质信息
	DWORD m_dwNumMtrls;						//网格材质数目

	LPD3DXMESH m_pBoundingSphere;			//模型包围球
};


#endif // !__MESH_H_

