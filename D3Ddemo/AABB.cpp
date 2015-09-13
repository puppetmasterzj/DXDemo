#include "stdafx.h"
#include "AABB.h"


AABB::AABB(void)
{
}


AABB::~AABB(void)
{
}

bool AABB::IsPointIn(const Vec3& vec) const
{
	return (vec.x >= m_min.x) && (vec.x <= m_max.x) && 
		(vec.y >= m_min.y) && (vec.y <= m_max.y) &&
		(vec.z >= m_min.z) && (vec.z <= m_max.z);
}

bool AABB::IsAABBCollided(const AABB& aabb) const
{
	return true;
}
