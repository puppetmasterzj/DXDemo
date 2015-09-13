#include "stdafx.h"
#include "SkyBox.h"


CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pDevice)
	:m_pDevice(pDevice),
	 m_pVertexBuffer(NULL),
	 m_fLength(0.0f)
{
	for (int i = 0; i < 5; i++)
		m_pTexture[i] = NULL;
}


CSkyBox::~CSkyBox(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
}

bool CSkyBox::InitSkyBox(float length)
{
	m_fLength = length;

	//创建定点缓冲区
	m_pDevice->CreateVertexBuffer(20 * sizeof(SkyBoxVertex), 0, D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);

	SkyBoxVertex vertices[] = 
	{
		//前面的顶点
		{-m_fLength / 2, 0.0f, m_fLength / 2, 0.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 0.0f,}, 
		{m_fLength / 2, 0.0f, m_fLength / 2, 1.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, m_fLength / 2,  1.0f, 0.0f,},

		//后面的顶点
		{m_fLength / 2, 0.0f, -m_fLength / 2, 0.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, 0.0f, -m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,},

		//左面的顶点
		{-m_fLength / 2, 0.0f, -m_fLength / 2 , 0.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, 0.0f, m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 1.0f, 0.0f,},

		//右面的顶点
		{m_fLength / 2, 0.0f, m_fLength / 2, 0.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 0.0f,},
		{m_fLength / 2, 0.0f, -m_fLength / 2, 1.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,},

		//上面的顶点
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,}, 
		{m_fLength / 2, m_fLength / 2, m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 1.0f,},
	};
	//填充定点缓冲数据
	void* pVertices = NULL;
	//加锁
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//拷贝顶点数据到缓冲区中
	memcpy(pVertices, vertices, sizeof(vertices));
	//解锁
	m_pVertexBuffer->Unlock();



	return true;
}

//bool CSkyBox::InitSkyBox( float Length )
//{
//	m_fLength=Length;
//
//	//1.创建。创建顶点缓存
//	m_pDevice->CreateVertexBuffer( 20 * sizeof(SkyBoxVertex), 0, 
//		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0 );
//
//	//用一个结构体把顶点数据先准备好
//	SkyBoxVertex vertices[] =
//	{
//		//前面的四个顶点
//		{ -m_fLength/2, 0.0f,    m_fLength/2, 0.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,   m_fLength/2, 0.0f, 0.0f, },
//		{  m_fLength/2, 0.0f,    m_fLength/2, 1.0f, 1.0f, },
//		{  m_fLength/2, m_fLength/2,   m_fLength/2, 1.0f, 0.0f, },
//
//		//背面的四个顶点
//		{  m_fLength/2, 0.0f,   -m_fLength/2, 0.0f, 1.0f, },
//		{  m_fLength/2, m_fLength/2,  -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, 0.0f,   -m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,  -m_fLength/2, 1.0f, 0.0f, },
//
//		//左面的四个顶点
//		{ -m_fLength/2, 0.0f,   -m_fLength/2, 0.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,  -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, 0.0f,    m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,   m_fLength/2, 1.0f, 0.0f, },
//
//		//右面的四个顶点
//		{ m_fLength/2, 0.0f,   m_fLength/2, 0.0f, 1.0f, },
//		{ m_fLength/2, m_fLength/2,  m_fLength/2, 0.0f, 0.0f, },
//		{ m_fLength/2, 0.0f,  -m_fLength/2, 1.0f, 1.0f, },
//		{ m_fLength/2, m_fLength/2, -m_fLength/2, 1.0f, 0.0f, },
//
//		//上面的四个顶点
//		{  m_fLength/2, m_fLength/2, -m_fLength/2, 1.0f, 0.0f, },
//		{  m_fLength/2, m_fLength/2,  m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2, -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, m_fLength/2,  m_fLength/2, 0.0f, 1.0f, },
//
//	};
//
//	//准备填充顶点数据
//	void* pVertices;
//	//2.加锁
//	m_pVertexBuffer->Lock( 0, 0, (void**)&pVertices, 0 );
//	//3.访问。把结构体中的数据直接拷到顶点缓冲区中
//	memcpy( pVertices, vertices, sizeof(vertices) );
//	//4.解锁
//	m_pVertexBuffer->Unlock();
//
//	return TRUE;
//}

bool CSkyBox::InitSkyBoxTexture(LPSTR szFrontTexture, LPSTR szBackTexture, LPSTR szLeftTexture, LPSTR szRightTexture, LPSTR szTopTexture)
{
	//从文件中加载天空盒纹理
	D3DXCreateTextureFromFile(m_pDevice, szFrontTexture, &m_pTexture[0]);//前
	D3DXCreateTextureFromFile(m_pDevice, szBackTexture, &m_pTexture[1]);//后
	D3DXCreateTextureFromFile(m_pDevice, szLeftTexture, &m_pTexture[2]);//左
	D3DXCreateTextureFromFile(m_pDevice, szRightTexture, &m_pTexture[3]);//右
	D3DXCreateTextureFromFile(m_pDevice, szTopTexture, &m_pTexture[4]);//上
	
	return true;
}

void CSkyBox::RenderSkyBox(D3DXMATRIX *matWorld, bool bRenderFrame /* = false */)
{
	//纹理颜色混合的第一个参数用于输出
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//纹理颜色混合的第一个参数取纹理的颜色值
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	//世界变换
	m_pDevice->SetTransform(D3DTS_WORLD, matWorld);
	//设置资源流
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SkyBoxVertex));
	//设置灵活顶点格式
	m_pDevice->SetFVF(D3DFVF_SKYBOX);

	//绘制
	for(int i = 0; i < 5; i++)
	{
		m_pDevice->SetTexture(0, m_pTexture[i]);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}