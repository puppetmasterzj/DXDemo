#include "stdafx.h"
#include "Particle.h"
#include <time.h>


CParticle::CParticle(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;
}


CParticle::~CParticle(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTexture);
}

bool CParticle::InitParticle()
{
	srand((unsigned int)time(0));
	//初始化雪花粒子数组
	for(int i = 0; i < PARTICLE_NUMBER; i++)
	{
		m_Particle[i].x = rand() % AREA_LENGTH - AREA_LENGTH / 2.0f;
		m_Particle[i].y = rand() % AREA_HEIGHT;
		m_Particle[i].z = rand() % AREA_WIDTH - AREA_WIDTH / 2.0f;
		m_Particle[i].speed = 500 + rand() % 500;
		m_Particle[i].rotationSpeed = 5.0f + rand() % 10 / 10.0f;
	}

	//创建雪花粒子顶点缓存
	m_pDevice->CreateVertexBuffer(4 * sizeof(POINTVERTEX), 0, D3DFVF_POINTVERTEX, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	//填充顶点缓存
	POINTVERTEX vertices[] = 
	{
		{-10.0f, 0.0f, 0.0f, 0.0f, 1.0f},
		{-10.0f, 20.0f, 0.0f, 0.0f, 0.0f},
		{ 10.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{ 10.0f, 20.0f, 0.0f, 1.0f, 0.0f}
	};
	//加锁
	VOID* pVertices;
	m_pVertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	//拷贝顶点数据
	memcpy(pVertices, vertices, sizeof(vertices));
	//解锁
	m_pVertexBuffer->Unlock();

	//加载纹理
	D3DXCreateTextureFromFile(m_pDevice, "snow.jpg", &m_pTexture);

	return true;
}

bool CParticle::UpdateParticle(float fElapsedTime)
{
	for(int i = 0; i < PARTICLE_NUMBER; i++)
	{
		m_Particle[i].y -= m_Particle[i].speed * fElapsedTime;
		if (m_Particle[i].y < 0)
			m_Particle[i].y = AREA_HEIGHT;
		m_Particle[i].rotationX += m_Particle[i].rotationSpeed * fElapsedTime;
		m_Particle[i].rotationY += m_Particle[i].rotationSpeed * fElapsedTime;
	}
	return true;
}

bool CParticle::RenderParticle()
{
	//禁用照明
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//设置纹理
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//设置Alpha混合系数
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);//打开alpha混合
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);//源混合系数为1
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//目标混合系数为1

	//设置不剔除背面
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//渲染
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//设置世界矩阵(这里设置为局部静态变量，类似全局变量，但是又比全局变量容易维护，作用域仅为该函数)
		static D3DXMATRIX matTrans, matYaw, matPitch, matWorld;
		D3DXMatrixRotationX(&matPitch, m_Particle[i].rotationX);
		D3DXMatrixRotationY(&matYaw, m_Particle[i].rotationY);
		D3DXMatrixTranslation(&matTrans, m_Particle[i].x, m_Particle[i].y, m_Particle[i].z);
		matWorld = matPitch * matYaw * matTrans;
		m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

		//设置纹理
		m_pDevice->SetTexture(0, m_pTexture);

		//绘制相关
		m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(POINTVERTEX));
		m_pDevice->SetFVF(D3DFVF_POINTVERTEX);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//绘制完成后恢复原状态：Alpha混合，背面剔除，光照，防止出现渲染状态泄露，影响其他对象绘制
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	return true;
}

