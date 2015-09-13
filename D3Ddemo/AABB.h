/*!
 * \file AABB.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \������Χ��AABB
 */
#ifndef __AABB_H_
#define __AABB_H_

class AABB
{
private:
	Vec3 m_min;		//���½�����
	Vec3 m_max;		//���Ͻ�����
public:
	AABB(void);
	~AABB(void);

	//�жϲ����İ�Χ�кͱ���Χ���Ƿ��ཻ
	bool IsAABBCollided(const AABB& aabb) const;

	//�жϵ��Ƿ��ڰ�Χ����
	bool IsPointIn(const Vec3& vec) const;

};

#endif

