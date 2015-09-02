/*!
 * \file Mesh.h
 *
 * \author zhangjian_dev
 * \date 七月 2015
 *网格模型类：负责导入模型以及绘制模型
 * 
 */
#ifndef __MESH_H_
#define __MESH_H_
#pragma once
#include "stdafx.h"

class CMesh
{
public:
	CMesh(LPDIRECT3DDEVICE9 pDevice);
	~CMesh(void);
	
	//创建网格对象
	void CreateMesh(LPSTR filename);
	//绘制网格对象
	void DrawMesh(const D3DXMATRIXA16& matWorld);

	//更改模型的Alpha分量值
	void AddAlphaValue();
	void ReduceAlphaValue();

private:

	LPDIRECT3DDEVICE9 m_pDevice;		    //D3D设备指针
	LPD3DXMESH m_pMesh;						//网格对象
	LPDIRECT3DTEXTURE9* m_pTextures;		//网格纹理信息
	D3DMATERIAL9* m_pMaterials;				//网格材质信息
	DWORD m_dwNumMtrls;						//网格材质数目
};


#endif // !__MESH_H_

