/*!
 * \file AABB.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \轴对齐包围盒AABB
 */
#ifndef __AABB_H_
#define __AABB_H_

class AABB
{
private:
	Vec3 m_min;		//左下角坐标
	Vec3 m_max;		//右上角坐标
public:
	AABB(void);
	~AABB(void);

	//判断参数的包围盒和本包围盒是否相交
	bool IsAABBCollided(const AABB& aabb) const;

	//判断点是否在包围盒中
	bool IsPointIn(const Vec3& vec) const;

};

#endif

