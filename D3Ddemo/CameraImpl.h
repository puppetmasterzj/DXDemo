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
<<<<<<< HEAD
	//���������
	enum CamType	
	{
		FirstView = 0,	//��һ�˳��ӽ�
		ThirdFirmView,	//�����˳��ӽǣ��̶���
		ThirdFreeView,	//�����˳��ӽǣ���
		GodView,		//�ϵ��ӽ�
		TracView		//������˾�
	};

=======
private:
	CCameraKernel* m_pKernel;	//���������ָ��
>>>>>>> origin/master
public:
	CameraImpl(void);
	virtual ~CameraImpl(void);

	//��ʼ��
<<<<<<< HEAD
	void Init();

	//����
	void Update();

	//����
	void Reset();
=======
	virtual void Init(CCameraKernel* kernel) = 0;

	//����
	virtual void Reset() = 0;

	//����
	virtual void Update() = 0;
>>>>>>> origin/master

	//����
	virtual void OnEvent() = 0;
};

#endif


