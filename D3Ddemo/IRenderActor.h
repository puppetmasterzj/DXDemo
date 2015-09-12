/*!
 * \file RenderActor.h
 *
 * \author zhangjian_dev
 * \date ���� 2015
 *
 * \����Ⱦ����ӿڣ����п���Ⱦ�Ķ��󶼼̳иýӿ�
 */
#ifndef __IRENDERACTOR_H_
#define __IRENDERACTOR_H_

#include "IRenderRes.h"

class IRenderActor
{
private:
	Vec3 m_Pos;				//λ�ã�ģ������������ϵ�е�λ��,x,y,z���꣩
	Vec3 m_Scale;			//����ϵ������ԭʼģ����ȣ���Ӧx,y,z�᷽������ϵ����
	Vec3 m_Rotation;		//��ת�Ƕȣ���ԭʼģ����ȣ���Ӧx,y,z����ת�ĽǶȣ�
	Matrix m_Matrix;		//�������
	IRenderRes* m_Res;		//��Դָ��
public:
	IRenderActor();
	virtual ~IRenderActor();

	//��ʼ��
	virtual bool Init(IRenderRes* resource);

	//����
	virtual void Render() = 0;

	//��Դָ��
	bool SetRes(IRenderRes* resource);
	IRenderRes* GetRes() const
	{
		return m_Res;
	}

	//λ��
	void SetPosition(const Vec3& vec);
	Vec3 GetPosition() const
	{
		return m_Pos;
	}

	//����(��һ����Ԫ����ʾ���������򶼿�������)
	void SetScale(const Vec3& scale);
	
	//��ת
	void SetRotationX();


	//�����������
	void CalculateMatrix();
	//����������
	Matrix GetMatrix() const
	{
		return m_Matrix;
	}


};

#endif