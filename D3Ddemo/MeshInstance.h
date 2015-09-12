/*!
 * \file MeshInstance.h
 *
 * \author puppet_master
 * \date ���� 2015
 * 
 * \����ʵ���࣬����������Դָ��
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

	//ͨ��������Դָ���ʼ������ʵ��
	//virtual bool Init(IRenderRes* resource) override;

	//����ʵ��
	virtual void Render() override;
};

#endif

