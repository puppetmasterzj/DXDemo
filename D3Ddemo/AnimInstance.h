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
#include "IRenderActor.h"

class CAnimInstance : public IRenderActor 
{
private:
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	float m_fSpeed;
	bool  m_bIsLoop;
public:
	CAnimInstance(void);
	~CAnimInstance(void);

	//��ʼ��һ����������ʵ��,��ö���������Դָ�룬��������һ�������Ķ���������
	virtual bool Init(IRenderRes* resource) override;

	//����ʵ��
	//virtual void Render() override;

	//�������Ʋ��Ŷ���
	bool PlayAnimation(LPCTSTR name, bool isLoop = true);

	//���¶���
	virtual void Update(float delayTime) override;

	//���ö����ٶ�
	void SetSpeed(float speed);

	//��ö����ٶ�
	float GetSpeed()const{return m_fSpeed;}

	//��ù�����������
	int GetAnimationNum() const;

	//���ݶ�����Ż�ö�����
	LPD3DXANIMATIONSET GetAnimationSet(int index) const;
};

#endif


