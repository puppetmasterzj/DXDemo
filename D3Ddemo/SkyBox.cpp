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

	//�������㻺����
	m_pDevice->CreateVertexBuffer(20 * sizeof(SkyBoxVertex), 0, D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);

	SkyBoxVertex vertices[] = 
	{
		//ǰ��Ķ���
		{-m_fLength / 2, 0.0f, m_fLength / 2, 0.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 0.0f,}, 
		{m_fLength / 2, 0.0f, m_fLength / 2, 1.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, m_fLength / 2,  1.0f, 0.0f,},

		//����Ķ���
		{m_fLength / 2, 0.0f, -m_fLength / 2, 0.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, 0.0f, -m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,},

		//����Ķ���
		{-m_fLength / 2, 0.0f, -m_fLength / 2 , 0.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, 0.0f, m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 1.0f, 0.0f,},

		//����Ķ���
		{m_fLength / 2, 0.0f, m_fLength / 2, 0.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 0.0f,},
		{m_fLength / 2, 0.0f, -m_fLength / 2, 1.0f, 1.0f,},
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,},

		//����Ķ���
		{m_fLength / 2, m_fLength / 2, -m_fLength / 2, 1.0f, 0.0f,}, 
		{m_fLength / 2, m_fLength / 2, m_fLength / 2, 1.0f, 1.0f,},
		{-m_fLength / 2, m_fLength / 2, -m_fLength / 2, 0.0f, 0.0f,},
		{-m_fLength / 2, m_fLength / 2, m_fLength / 2, 0.0f, 1.0f,},
	};
	//��䶨�㻺������
	void* pVertices = NULL;
	//����
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//�����������ݵ���������
	memcpy(pVertices, vertices, sizeof(vertices));
	//����
	m_pVertexBuffer->Unlock();



	return true;
}

//bool CSkyBox::InitSkyBox( float Length )
//{
//	m_fLength=Length;
//
//	//1.�������������㻺��
//	m_pDevice->CreateVertexBuffer( 20 * sizeof(SkyBoxVertex), 0, 
//		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0 );
//
//	//��һ���ṹ��Ѷ���������׼����
//	SkyBoxVertex vertices[] =
//	{
//		//ǰ����ĸ�����
//		{ -m_fLength/2, 0.0f,    m_fLength/2, 0.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,   m_fLength/2, 0.0f, 0.0f, },
//		{  m_fLength/2, 0.0f,    m_fLength/2, 1.0f, 1.0f, },
//		{  m_fLength/2, m_fLength/2,   m_fLength/2, 1.0f, 0.0f, },
//
//		//������ĸ�����
//		{  m_fLength/2, 0.0f,   -m_fLength/2, 0.0f, 1.0f, },
//		{  m_fLength/2, m_fLength/2,  -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, 0.0f,   -m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,  -m_fLength/2, 1.0f, 0.0f, },
//
//		//������ĸ�����
//		{ -m_fLength/2, 0.0f,   -m_fLength/2, 0.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,  -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, 0.0f,    m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2,   m_fLength/2, 1.0f, 0.0f, },
//
//		//������ĸ�����
//		{ m_fLength/2, 0.0f,   m_fLength/2, 0.0f, 1.0f, },
//		{ m_fLength/2, m_fLength/2,  m_fLength/2, 0.0f, 0.0f, },
//		{ m_fLength/2, 0.0f,  -m_fLength/2, 1.0f, 1.0f, },
//		{ m_fLength/2, m_fLength/2, -m_fLength/2, 1.0f, 0.0f, },
//
//		//������ĸ�����
//		{  m_fLength/2, m_fLength/2, -m_fLength/2, 1.0f, 0.0f, },
//		{  m_fLength/2, m_fLength/2,  m_fLength/2, 1.0f, 1.0f, },
//		{ -m_fLength/2, m_fLength/2, -m_fLength/2, 0.0f, 0.0f, },
//		{ -m_fLength/2, m_fLength/2,  m_fLength/2, 0.0f, 1.0f, },
//
//	};
//
//	//׼����䶥������
//	void* pVertices;
//	//2.����
//	m_pVertexBuffer->Lock( 0, 0, (void**)&pVertices, 0 );
//	//3.���ʡ��ѽṹ���е�����ֱ�ӿ������㻺������
//	memcpy( pVertices, vertices, sizeof(vertices) );
//	//4.����
//	m_pVertexBuffer->Unlock();
//
//	return TRUE;
//}

bool CSkyBox::InitSkyBoxTexture(LPSTR szFrontTexture, LPSTR szBackTexture, LPSTR szLeftTexture, LPSTR szRightTexture, LPSTR szTopTexture)
{
	//���ļ��м�����պ�����
	D3DXCreateTextureFromFile(m_pDevice, szFrontTexture, &m_pTexture[0]);//ǰ
	D3DXCreateTextureFromFile(m_pDevice, szBackTexture, &m_pTexture[1]);//��
	D3DXCreateTextureFromFile(m_pDevice, szLeftTexture, &m_pTexture[2]);//��
	D3DXCreateTextureFromFile(m_pDevice, szRightTexture, &m_pTexture[3]);//��
	D3DXCreateTextureFromFile(m_pDevice, szTopTexture, &m_pTexture[4]);//��
	
	return true;
}

void CSkyBox::RenderSkyBox(D3DXMATRIX *matWorld, bool bRenderFrame /* = false */)
{
	//������ɫ��ϵĵ�һ�������������
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//������ɫ��ϵĵ�һ������ȡ�������ɫֵ
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	//����任
	m_pDevice->SetTransform(D3DTS_WORLD, matWorld);
	//������Դ��
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SkyBoxVertex));
	//���������ʽ
	m_pDevice->SetFVF(D3DFVF_SKYBOX);

	//����
	for(int i = 0; i < 5; i++)
	{
		m_pDevice->SetTexture(0, m_pTexture[i]);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}