/*!
 * \file AnimInstance.h
 *
 * \author puppet_master
 * \date ���� 2015
 * \��������ʵ���ࣺ����ֱ��ʹ�õĹ�������ʵ�����ڲ�����������������ָ���뵥���Ŀ�������
 */
#ifndef __ANIMINSTANCE_H_
#define __ANIMINSTANCE_H_

#include "D3DXAnimation.h"

class CAnimInstance
{
private:
	CD3DXAnimation* m_pAnimMesh;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	D3DXMATRIX		m_Matrix;
	float m_fSpeed;
	bool  m_bIsLoop;
public:
	CAnimInstance(void);
	~CAnimInstance(void);

	//��ʼ��һ����������ʵ��,��ö���������Դָ�룬��������һ�������Ķ���������
	bool Init(CD3DXAnimation* mesh);

	//����ʵ��
	void Render();

	//�������Ʋ��Ŷ���
	bool PlayAnimation(LPCTSTR name, bool isLoop = true);

	//���¶���
	void Update(float delayTime);

	//���ö����ٶ�
	void SetSpeed(float speed);

	//��ö����ٶ�
	float GetSpeed()const{return m_fSpeed;}

	//���¾���
	void SetMatrix(const LPD3DXMATRIX matrix);

	//��þ���
	D3DMATRIX GetMatrix(){return m_Matrix;}

	//��ù�����������
	int GetAnimationNum() const;

	//���ݶ�����Ż�ö�����
	LPD3DXANIMATIONSET GetAnimationSet(int index) const;
};

#endif


