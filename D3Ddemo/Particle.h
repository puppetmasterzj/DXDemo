/*!
 * \file Particle.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * ����ϵͳ��ʵ��
 */
#ifndef __CPARTICLE_H_
#define __CPARTICLE_H_
#include "stdafx.h"

#pragma once
//���Ӷ����ʽ
struct POINTVERTEX
{
	float x, y, z;
	float u, v;
};
#define D3DFVF_POINTVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

//���ӽṹ�嶨��
struct ParticleStruct
{
	float x, y, z;				//����
	float rotationX;			//��X����ת�Ƕ�
	float rotationY;			//��Y����ת�Ƕ�
	float speed;				//�����ٶ�
	float rotationSpeed;		//��ת�ٶ�
};

const int PARTICLE_NUMBER = 3000;			//��������
const int AREA_WIDTH = 10000;				//����ϵͳ������
const int AREA_LENGTH = 10000;				//����ϵͳ���򳤶�
const int AREA_HEIGHT = 10000;				//����ϵͳ����߶�

class CParticle
{
private:

	LPDIRECT3DDEVICE9 m_pDevice;					//�豸ָ��
	ParticleStruct m_Particle[PARTICLE_NUMBER];		//���ӽṹ������
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		//���㻺����
	LPDIRECT3DTEXTURE9 m_pTexture;					//��������
public:
	CParticle(LPDIRECT3DDEVICE9);
	virtual ~CParticle(void);

	//��ʼ������ϵͳ
	bool InitParticle();
	//��������
	bool UpdateParticle(float);
	//��������
	bool RenderParticle();
};

#endif


