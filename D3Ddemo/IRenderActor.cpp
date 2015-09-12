#include "stdafx.h"
#include "IRenderActor.h"


IRenderActor::IRenderActor(void)
{

}


IRenderActor::~IRenderActor(void)
{

}

bool IRenderActor::Init(IRenderRes* resource)
{
	return SetRes(resource);
}

bool IRenderActor::SetRes(IRenderRes* resource)
{
	if(!resource)
		return false;
	m_Res = resource;
	return true;
}

void IRenderActor::SetPosition(const Vec3& vec)
{
	m_Pos = vec;
}

void IRenderActor::CalculateMatrix()
{
	D3DXMatrixTranslation(&m_Matrix, m_Pos.x, m_Pos.y, m_Pos.z);
}