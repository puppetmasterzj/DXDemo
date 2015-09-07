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

class CameraImpl
{
	//摄像机类型
	enum CamType	
	{
		FirstView = 0,	//第一人称视角
		ThirdFirmView,	//第三人称视角（固定）
		ThirdFreeView,	//第三人称视角（灵活）
		GodView,		//上帝视角
		TracView		//摄像机运镜
	};

public:
	CameraImpl(void);
	virtual ~CameraImpl(void);

	//初始化
	void Init();

	//更新
	void Update();

	//重置
	void Reset();

	//
};

#endif


