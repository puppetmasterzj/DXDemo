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

void IRenderActor::Render()
{
	m_Res->Render(&m_Matrix);
}

void IRenderActor::Update(float elapsedtime)
{
	CalculateMatrix();
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

void IRenderActor::SetScale(const Vec3& scale)
{
	m_Scale = scale;
}

void IRenderActor::SetRotationX(float angle)
{
	m_Rotation.x = angle;
}

void IRenderActor::SetRotationY(float angle)
{
	m_Rotation.y = angle;
}

void IRenderActor::SetRotationZ(float angle)
{
	m_Rotation.z = angle;
}

void IRenderActor::CalculateMatrix()
{
	//Æ½ÒÆ¾ØÕó
	D3DXMatrixTranslation(&m_Matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	//Ëõ·Å¾ØÕó
	Matrix scalMatrix;
	D3DXMatrixScaling(&scalMatrix, m_Scale.x, m_Scale.y, m_Scale.z);
	//Ðý×ª¾ØÕó
	Matrix rotationMatrixX, rotationMatrixY, rotationMatrixZ;
	D3DXMatrixRotationX(&rotationMatrixX, m_Rotation.x);
	D3DXMatrixRotationY(&rotationMatrixY, m_Rotation.y);
	D3DXMatrixRotationZ(&rotationMatrixZ, m_Rotation.z);

	m_Matrix = scalMatrix *rotationMatrixX * rotationMatrixY * rotationMatrixZ * m_Matrix;
}