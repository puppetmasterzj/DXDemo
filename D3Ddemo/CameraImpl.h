/*!
 * \file CameraImpl.h
 *
 * \author puppet_master
 * \date ���� 2015
 * \������ӿڣ�����������Ļ��࣬��Ըýӿ�ʵ�֣����ṩһ��������������������ڴ��������
 * 
 */
#ifndef __CAMERAIMPL_H_
#define __CAMERAIMPL_H_

#include "CameraKernel.h"

class CameraImpl
{
private:
	CCameraKernel* m_pKernel;	//���������ָ��
public:
	CameraImpl(void);
	virtual ~CameraImpl(void);

	//��ʼ��
	virtual void Init(CCameraKernel* kernel) = 0;

	//����
	virtual void Reset() = 0;

	//����
	virtual void Update() = 0;

	//����
	virtual void OnEvent() = 0;
};

#endif


