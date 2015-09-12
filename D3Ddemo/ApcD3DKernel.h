/*!
 * \file ApcD3DKernel.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \Apc引擎D3D渲染核心模块
 * \封装D3D底层相关内容
 */
#ifndef __APCD3DKERNEL_H_
#define __APCD3DKERNEL_H_

class ApcD3DKernel
{
public:
	ApcD3DKernel(void);
	~ApcD3DKernel(void);

	//初始化
	bool Init(HWND hWnd);
	//进行渲染

}

#endif
;

