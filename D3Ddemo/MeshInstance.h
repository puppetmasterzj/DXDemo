/*!
 * \file MeshInstance.h
 *
 * \author puppet_master
 * \date 九月 2015
 * 
 * \网格实例类，引用网格资源指针
 */


#ifndef __MESHINSTANCE_H_
#define __MESHINSTANCE_H_

#include "IRenderActor.h"

class D3DXMesh;

class MeshInstance : public IRenderActor
{
public:
	MeshInstance(void);
	virtual ~MeshInstance(void);

	//通过网格资源指针初始化网格实例
	//virtual bool Init(IRenderRes* resource) override;

	//绘制实例
	virtual void Render() override;
};

#endif

