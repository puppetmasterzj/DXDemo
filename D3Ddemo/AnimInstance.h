/*!
 * \file AnimInstance.h
 *
 * \author puppet_master
 * \date 九月 2015
 * \骨骼动画实例类：可以直接使用的骨骼动画实例，内部包含骨骼动画绘制指针与单独的控制器。
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

	//初始化一个动画网格实例,获得动画网格资源指针，并拷贝出一个单独的动画控制器
	virtual bool Init(IRenderRes* resource) override;

	//绘制实例
	//virtual void Render() override;

	//根据名称播放动画
	bool PlayAnimation(LPCTSTR name, bool isLoop = true);

	//更新动画
	virtual void Update(float delayTime) override;

	//设置动画速度
	void SetSpeed(float speed);

	//获得动画速度
	float GetSpeed()const{return m_fSpeed;}

	//获得骨骼动画个数
	int GetAnimationNum() const;

	//根据动画编号获得动画集
	LPD3DXANIMATIONSET GetAnimationSet(int index) const;
};

#endif


