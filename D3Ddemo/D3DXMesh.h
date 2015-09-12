/*!
 * \file Mesh.h
 *
 * \author zhangjian_dev
 * \date ���� 2015
 *����ģ���ࣺ������ģ���Լ�����ģ��
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
	
	//�����������
	virtual HRESULT Init(LPCSTR filename) override;

	//��������ģ�Ͱ�Χ��
	void CreateBoundingSphere(BoundingSphere* sphere);

	//�����������
	virtual void Render(const LPD3DXMATRIX matrix);

	//���ԭ��������Դָ��
	LPD3DXMESH GetMeshPointer()
	{return m_pMesh;}

private:
	
	LPD3DXMESH m_pMesh;						//�������
	LPDIRECT3DTEXTURE9* m_pTextures;		//����������Ϣ
	D3DMATERIAL9* m_pMaterials;				//���������Ϣ
	DWORD m_dwNumMtrls;						//���������Ŀ

	LPD3DXMESH m_pBoundingSphere;			//ģ�Ͱ�Χ��
};


#endif // !__MESH_H_

