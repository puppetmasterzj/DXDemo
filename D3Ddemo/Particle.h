/*!
 * \file Particle.h
 *
 * \author puppet_master
 * \date 八月 2015
 *
 * 粒子系统的实现
 */
#ifndef __CPARTICLE_H_
#define __CPARTICLE_H_
#include "stdafx.h"

#pragma once
//粒子定点格式
struct POINTVERTEX
{
	float x, y, z;
	float u, v;
};
#define D3DFVF_POINTVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

//粒子结构体定义
struct ParticleStruct
{
	float x, y, z;				//坐标
	float rotationX;			//绕X轴旋转角度
	float rotationY;			//绕Y轴旋转角度
	float speed;				//下落速度
	float rotationSpeed;		//旋转速度
};

const int PARTICLE_NUMBER = 3000;			//粒子数量
const int AREA_WIDTH = 10000;				//粒子系统区域宽度
const int AREA_LENGTH = 10000;				//粒子系统区域长度
const int AREA_HEIGHT = 10000;				//粒子系统区域高度

class CParticle
{
private:

	LPDIRECT3DDEVICE9 m_pDevice;					//设备指针
	ParticleStruct m_Particle[PARTICLE_NUMBER];		//粒子结构体数组
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		//顶点缓冲区
	LPDIRECT3DTEXTURE9 m_pTexture;					//粒子纹理
public:
	CParticle(LPDIRECT3DDEVICE9);
	virtual ~CParticle(void);

	//初始化粒子系统
	bool InitParticle();
	//更新粒子
	bool UpdateParticle(float);
	//绘制粒子
	bool RenderParticle();
};

#endif


