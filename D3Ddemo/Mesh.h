/*!
 * \file Mesh.h
 *
 * \author zhangjian_dev
 * \date ���� 2015
 *����ģ���ࣺ������ģ���Լ�����ģ��
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
	
	//�����������
	void CreateMesh(LPSTR filename);
	//�����������
	void DrawMesh(const D3DXMATRIXA16& matWorld);

	//����ģ�͵�Alpha����ֵ
	void AddAlphaValue();
	void ReduceAlphaValue();

private:

	LPDIRECT3DDEVICE9 m_pDevice;		    //D3D�豸ָ��
	LPD3DXMESH m_pMesh;						//�������
	LPDIRECT3DTEXTURE9* m_pTextures;		//����������Ϣ
	D3DMATERIAL9* m_pMaterials;				//���������Ϣ
	DWORD m_dwNumMtrls;						//���������Ŀ
};


#endif // !__MESH_H_

