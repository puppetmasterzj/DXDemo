#include "stdafx.h"
#include "CameraKernel.h"


CCameraKernel::CCameraKernel(IDirect3DDevice9* pDevice)
	:m_pDevice(pDevice),
	 m_vLookVector(D3DXVECTOR3(0.0f, 0.0f, 1.0f)),
	 m_vUpVector(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
	 m_vRightVector(D3DXVECTOR3(1.0f, 0.0f, 0.0f)),
	 m_vCameraPosition(D3DXVECTOR3(0.0f, 0.0f, -200.0f)),
	 m_vTargetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{

}


CCameraKernel::~CCameraKernel(void)
{

}

void CCameraKernel::CalculateViewMatrix(D3DXMATRIX *pMatrix)
{
	//�淶����������ʹ֮��Ϊ��������

	//�淶���۲�����
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);
	//ʹ��������۲�������ֱ
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
	//�淶��������
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);
	//����������������ֱ
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
	//�淶��������
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);

	//����ȡ���任����
	pMatrix->_11 = m_vRightVector.x;
	pMatrix->_12 = m_vUpVector.x;
	pMatrix->_13 = m_vLookVector.x;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = m_vRightVector.y;
	pMatrix->_22 = m_vUpVector.y;
	pMatrix->_23 = m_vLookVector.y;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = m_vRightVector.z;
	pMatrix->_32 = m_vUpVector.z;
	pMatrix->_33 = m_vLookVector.z;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = -D3DXVec3Dot(&m_vRightVector, &m_vCameraPosition);
	pMatrix->_42 = -D3DXVec3Dot(&m_vUpVector, &m_vCameraPosition);
	pMatrix->_43 = -D3DXVec3Dot(&m_vLookVector, &m_vCameraPosition);
	pMatrix->_44 = 1.0f;
}

void CCameraKernel::SetTargetPosition(D3DXVECTOR3* pVector)
{
	if (pVector)
		m_vTargetPosition = (*pVector);
	else
		m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//�۲��λ�ü�ȥ�����λ�õõ���������
	m_vLookVector = m_vTargetPosition - m_vCameraPosition;

	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);

	//�������淶��upV��rightV
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);
}

void CCameraKernel::SetCameraPosition(D3DXVECTOR3* pVector /* = NULL */)
{
	D3DXVECTOR3 v = D3DXVECTOR3(0.0f, 0.0f, -200.0f);
	m_vCameraPosition = pVector ? (*pVector) : v;
}

void CCameraKernel::SetViewMatrix(D3DXMATRIX* pMatrix /* = NULL */)
{
	if (pMatrix)
		m_matView = *pMatrix;
	else
		CalculateViewMatrix(&m_matView);
	m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	m_vRightVector = D3DXVECTOR3(m_matView._11, m_matView._12, m_matView._13);
	m_vUpVector = D3DXVECTOR3(m_matView._21, m_matView._22, m_matView._23);
	m_vLookVector = D3DXVECTOR3(m_matView._31, m_matView._32, m_matView._33);
}

void CCameraKernel::SetProjectionMartix(D3DMATRIX* pMatrix /* = NULL */)
{
	if (pMatrix)
		m_matProj = *pMatrix;
	else
		D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0F, 800 / 600, 1.0f, 30000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

//ƽ�Ʋ���
void CCameraKernel::MoveAlongRightVec(float fUnits)
{
	m_vCameraPosition += m_vRightVector * fUnits;
	m_vTargetPosition += m_vRightVector * fUnits;
}

void CCameraKernel::MoveAlongUpVec(float fUnits)
{
	m_vCameraPosition += m_vUpVector * fUnits;
	m_vTargetPosition += m_vUpVector * fUnits;
}

void CCameraKernel::MoveAlongLookVec(float fUnits)
{
	m_vCameraPosition += m_vLookVector * fUnits;
	m_vTargetPosition += m_vLookVector * fUnits;
}

//��ת����
void CCameraKernel::RotationRightVec(float fAngle)
{
	//������ת֮��ľ���
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r, &m_vRightVector, fAngle);
	//��m_vUp������m_vLook������m_vRight������תfAngle�Ƕ�
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &r);
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &r);
	//���¹۲��λ��
	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);
}

void CCameraKernel::RotationUpVec(float fAngle)
{
	//������ת֮��ľ���
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r, &m_vUpVector, fAngle);
	//��m_vRight������m_vLook������m_vUp������תfAngle�Ƕ�
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &r);
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &r);
	//���¹۲��λ��
	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);
}

void CCameraKernel::RotationLookVec(float fAngle)
{
	//������ת֮��ľ���
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r, &m_vLookVector, fAngle);
	//��m_vUp������m_vRight������m_vLook������תfAngle�Ƕ�
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &r);
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &r);
	//���¹۲��λ��
	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);
}


