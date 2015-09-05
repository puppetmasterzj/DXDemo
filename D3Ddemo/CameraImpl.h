/*!
 * \file CameraImpl.h
 *
 * \author puppet_master
 * \date 九月 2015
 * \摄像机接口：各种摄像机的基类，针对该接口实现，并提供一个灵活的摄像机工厂，用于创建摄像机
 * 
 */
#ifndef __CAMERAIMPL_H_
#define __CAMERAIMPL_H_

#include "CameraKernel.h"

class CameraImpl
{
private:
	CCameraKernel* m_pKernel;	//摄像机核心指针
public:
	CameraImpl(void);
	virtual ~CameraImpl(void);

	//初始化
	virtual void Init(CCameraKernel* kernel) = 0;

	//重置
	virtual void Reset() = 0;

	//更新
	virtual void Update() = 0;

	//操作
	virtual void OnEvent() = 0;
};

#endif


