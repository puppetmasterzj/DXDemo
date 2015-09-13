/*!
 * \file CameraKernel.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \摄像机核心类，封装DX的投影变换&VIEW变换
 */
#ifndef __CAMERAKERNEL_H_
#define __CAMERAKERNEL_H_

#include "stdafx.h"

class CCameraKernel
{
private:
	//成员变量
	IDirect3DDevice9* m_pDevice;		//D3D设备对象
	D3DXVECTOR3 m_vRightVector;	        //右分量向量
	D3DXVECTOR3 m_vUpVector;			//上分量向量
	D3DXVECTOR3 m_vLookVector;			//观察分量向量
	D3DXVECTOR3 m_vCameraPosition;		//摄像机位置
	D3DXVECTOR3 m_vTargetPosition;		//观察目标位置
	D3DXMATRIX  m_matView;				//取景变换矩阵
	D3DXMATRIX  m_matProj;				//投影变换矩阵

public:
	CCameraKernel(IDirect3DDevice9* pDevice);
	~CCameraKernel(void);

	//计算取景变换矩阵
	void CalculateViewMatrix(D3DXMATRIX *pMatrix);
	//获得投影矩阵
	void GetProjectionMatrix(D3DXMATRIX* pMatrix){*pMatrix = m_matProj;}
	//获得当前摄像机位置向量
	void GetCameraPosition(D3DXVECTOR3* pVector){*pVector = m_vCameraPosition;}
	//返回当前观察向量
	void GetLookVector(D3DXVECTOR3* pVector){*pVector = m_vLookVector;}
	//设置摄像机观察位置向量（默认参数为NULL）
	void  SetTargetPosition(D3DXVECTOR3* pVector = NULL);
	//设置摄像机所在位置向量(默认参数为NULL)
	void SetCameraPosition(D3DXVECTOR3* pVector = NULL);
	//设置取景变换矩阵(默认参数为NULL)
	void SetViewMatrix(D3DXMATRIX* pMatrix = NULL);
	//设置投影变换矩阵(默认参数为NULL)
	void SetProjectionMartix(D3DMATRIX* pMatrix = NULL);



	//沿着right分量平移
	void MoveAlongRightVec(float fUnits);
	//沿着up分量平移
	void MoveAlongUpVec(float fUnits);
	//沿着look分量平移
	void MoveAlongLookVec(float fUnits);


	//沿着right分量旋转
	void RotationRightVec(float fAngle);
	//沿着up分量旋转
	void RotationUpVec(float fAngle);
	//沿着look分量旋转
	void RotationLookVec(float fAngle);
};

#endif // 

