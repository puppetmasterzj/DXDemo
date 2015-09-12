/*!
 * \file RenderActor.h
 *
 * \author zhangjian_dev
 * \date 九月 2015
 *
 * \可渲染对象接口，所有可渲染的对象都继承该接口
 */
#ifndef __IRENDERACTOR_H_
#define __IRENDERACTOR_H_

#include "IRenderRes.h"

class IRenderActor
{
private:
	Vec3 m_Pos;				//位置（模型在世界坐标系中的位置,x,y,z坐标）
	Vec3 m_Scale;			//缩放系数（与原始模型相比，对应x,y,z轴方向缩放系数）
	Vec3 m_Rotation;		//旋转角度（与原始模型相比，对应x,y,z轴旋转的角度）
	Matrix m_Matrix;		//世界矩阵
	IRenderRes* m_Res;		//资源指针
public:
	IRenderActor();
	virtual ~IRenderActor();

	//初始化
	virtual bool Init(IRenderRes* resource);

	//绘制
	virtual void Render() = 0;

	//资源指针
	bool SetRes(IRenderRes* resource);
	IRenderRes* GetRes() const
	{
		return m_Res;
	}

	//位置
	void SetPosition(const Vec3& vec);
	Vec3 GetPosition() const
	{
		return m_Pos;
	}

	//缩放(用一个三元数表示，各个方向都可能缩放)
	void SetScale(const Vec3& scale);
	
	//旋转
	void SetRotationX();


	//计算世界矩阵
	void CalculateMatrix();
	//获得世界矩阵
	Matrix GetMatrix() const
	{
		return m_Matrix;
	}


};

#endif