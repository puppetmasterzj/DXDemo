/*!
 * \file CameraKernel.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \����������࣬��װDX��ͶӰ�任&VIEW�任
 */
#ifndef __CAMERAKERNEL_H_
#define __CAMERAKERNEL_H_

#include "stdafx.h"

class CCameraKernel
{
private:
	//��Ա����
	IDirect3DDevice9* m_pDevice;		//D3D�豸����
	D3DXVECTOR3 m_vRightVector;	        //�ҷ�������
	D3DXVECTOR3 m_vUpVector;			//�Ϸ�������
	D3DXVECTOR3 m_vLookVector;			//�۲��������
	D3DXVECTOR3 m_vCameraPosition;		//�����λ��
	D3DXVECTOR3 m_vTargetPosition;		//�۲�Ŀ��λ��
	D3DXMATRIX  m_matView;				//ȡ���任����
	D3DXMATRIX  m_matProj;				//ͶӰ�任����

public:
	CCameraKernel(IDirect3DDevice9* pDevice);
	~CCameraKernel(void);

	//����ȡ���任����
	void CalculateViewMatrix(D3DXMATRIX *pMatrix);
	//���ͶӰ����
	void GetProjectionMatrix(D3DXMATRIX* pMatrix){*pMatrix = m_matProj;}
	//��õ�ǰ�����λ������
	void GetCameraPosition(D3DXVECTOR3* pVector){*pVector = m_vCameraPosition;}
	//���ص�ǰ�۲�����
	void GetLookVector(D3DXVECTOR3* pVector){*pVector = m_vLookVector;}
	//����������۲�λ��������Ĭ�ϲ���ΪNULL��
	void  SetTargetPosition(D3DXVECTOR3* pVector = NULL);
	//�������������λ������(Ĭ�ϲ���ΪNULL)
	void SetCameraPosition(D3DXVECTOR3* pVector = NULL);
	//����ȡ���任����(Ĭ�ϲ���ΪNULL)
	void SetViewMatrix(D3DXMATRIX* pMatrix = NULL);
	//����ͶӰ�任����(Ĭ�ϲ���ΪNULL)
	void SetProjectionMartix(D3DMATRIX* pMatrix = NULL);



	//����right����ƽ��
	void MoveAlongRightVec(float fUnits);
	//����up����ƽ��
	void MoveAlongUpVec(float fUnits);
	//����look����ƽ��
	void MoveAlongLookVec(float fUnits);


	//����right������ת
	void RotationRightVec(float fAngle);
	//����up������ת
	void RotationUpVec(float fAngle);
	//����look������ת
	void RotationLookVec(float fAngle);
};

#endif // 

