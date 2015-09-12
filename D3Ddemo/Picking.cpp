#include "stdafx.h"
#include "Picking.h"


Picking::Picking(IDirect3DDevice9* device) : m_pDevice(device)
{

}


Picking::~Picking(void)
{

}

void Picking::CalculatePickingRay(int x, int y, Ray* ray)
{
	D3DVIEWPORT9 viewport;
	m_pDevice->GetViewport(&viewport);

	D3DXMATRIX proj_matrix;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &proj_matrix);

	float px = ((( 2.0f * x) / viewport.Width)  - 1.0f) / proj_matrix(0, 0);
	float py = (((-2.0f * y) / viewport.Height) + 1.0f) / proj_matrix(1, 1);

	ray->m_vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray->m_vDirection = D3DXVECTOR3(px, py, 1.0f);
}

void Picking::TransformRay(Ray* ray, D3DXMATRIX* matrix)
{
	//转化射线的起始点, w = 1.
	D3DXVec3TransformCoord(&ray->m_vOrigin, &ray->m_vOrigin, matrix);

	//转化射线的方向向量, w = 0.
	D3DXVec3TransformNormal(&ray->m_vDirection, &ray->m_vDirection, matrix);

	//单位化方向向量
	D3DXVec3Normalize(&ray->m_vDirection, &ray->m_vDirection);
}

bool Picking::Ray_SphereIntersect(const Ray* ray, const BoundingSphere* sphere)
{
	D3DXVECTOR3 v = ray->m_vOrigin - sphere->m_vCenter;

	float b = 2.0f * D3DXVec3Dot(&ray->m_vDirection, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->m_fRadius * sphere->m_fRadius);

	float discriminant = (b * b) - (4.0f * c);

	if(discriminant < 0.0f)
		return false;

	discriminant = sqrt(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	return (s0 >= 0.0f || s1 >= 0.0f);
}

bool Picking::IsPicked(int x, int y, const BoundingSphere* sphere)
{
	Ray ray;
	CalculatePickingRay(x, y, &ray);

	D3DXMATRIX view_matrix, inverse_matrix;
	m_pDevice->GetTransform(D3DTS_VIEW, &view_matrix);
	//求出View矩阵的逆矩阵
	D3DXMatrixInverse(&inverse_matrix, NULL, &view_matrix);

	TransformRay(&ray, &inverse_matrix);

	return Ray_SphereIntersect(&ray, sphere); 
}