/*!
 * \file D3DXAnimation.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \��װ��΢���Դ��Ĺ���������ع���,�ڲ�������ȡ�������������ŵȹ��ܡ�
 * \������ֱ��ʹ�ã���Ҫ��¡һ������������������������ʵ���ſ���ʹ��
 */

#ifndef __D3DXANIMATION_H_
#define __D3DXANIMATION_H_

#include "AllocateHierarchy.h"
#include "IRenderRes.h"

class CD3DXAnimation : public IRenderRes
{
private:
	CAllocateHierarchy* m_pAllocateHier;			//������������ģ��ָ��
	LPD3DXFRAME			m_pFrameRoot;				//֡
	LPD3DXANIMATIONCONTROLLER m_pAnimController;	//����������
private:
	//һЩ΢���Դ����������ڹ���������������Ƹ��µĺ����������װ����ʹ����Щ�ӿ�

	void DrawMeshContainer( IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase );
	void DrawFrame( IDirect3DDevice9* pd3dDevice, LPD3DXFRAME pFrame );
	HRESULT SetupBoneMatrixPointers( LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot );
	void UpdateFrameMatrices( LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix );
public:
	CD3DXAnimation(IDirect3DDevice9* device);
	~CD3DXAnimation(void);

	//�ṩ�����Ľӿ�

	//������������
	virtual HRESULT Init(LPCTSTR filename) override;

	//���ƹ�������������
	LPD3DXANIMATIONCONTROLLER CloneAnimCtrl(void);

	//���ƹ�������
	virtual void Render(const LPD3DXMATRIX matrix) override;

};

#endif


