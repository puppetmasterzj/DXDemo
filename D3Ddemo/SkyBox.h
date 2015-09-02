/*!
 * \file SkyBox.h
 *
 * \author puppet_master
 * \date 七月 2015
 *
 * 三维天空盒的封装
 */
#ifndef __SKYBOX_H_
#define __SKYBOX_H_

#pragma once

struct SkyBoxVertex
{
	float x, y, z;  //定点位置
	float u, v;		//纹理位置
};
#define D3DFVF_SKYBOX D3DFVF_XYZ | D3DFVF_TEX1


class CSkyBox
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;			//设备指针
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;//定点缓冲区指针
	LPDIRECT3DTEXTURE9 m_pTexture[5];		//纹理对象指针
	float m_fLength;						//天空盒宽度
public:
	CSkyBox(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CSkyBox(void);

	//初始化天空盒
	bool InitSkyBox(float length);

	//加载纹理
	bool InitSkyBoxTexture(LPSTR szFrontTexture, LPSTR szBackTexture, LPSTR szLeftTexture, LPSTR szRightTexture, LPSTR szTopTexture);
	
	//渲染天空盒
	void RenderSkyBox(D3DXMATRIX *matWorld, bool bRenderFrame = false);
};


#endif
