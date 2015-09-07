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

class CameraImpl
{
	//���������
	enum CamType	
	{
		FirstView = 0,	//��һ�˳��ӽ�
		ThirdFirmView,	//�����˳��ӽǣ��̶���
		ThirdFreeView,	//�����˳��ӽǣ���
		GodView,		//�ϵ��ӽ�
		TracView		//������˾�
	};

public:
	CameraImpl(void);
	virtual ~CameraImpl(void);

	//��ʼ��
	void Init();

	//����
	void Update();

	//����
	void Reset();

	//
};

#endif


