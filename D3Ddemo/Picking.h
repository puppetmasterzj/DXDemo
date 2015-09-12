/*!
 * \file Picking.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \拾取功能类
 * \步骤：1.根据二维坐标以及摄像机矩阵计算投影射线
 * \	  2.将射线转化到模型的坐标系中
 * \	  3.遍历所有对象最终得到拾取的对象
 * \
 * \单例或者静态类
 */
#ifndef __PICKING_H_
#define __PICKING_H_

//射线结构体
struct Ray
{
	D3DXVECTOR3 m_vOrigin;			//起点
	D3DXVECTOR3 m_vDirection;		//方向

	//构造函数(默认初始点为0，方向为向Z轴正向)
	Ray(const D3DXVECTOR3& origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f), const D3DXVECTOR3& direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f)) : m_vOrigin(origin), m_vDirection(direction)
	{ 

	}
};

//包围球结构体
struct BoundingSphere
{
	D3DXVECTOR3 m_vCenter;			//中点
	float		m_fRadius;			//半径

	//构造函数
	BoundingSphere(const D3DXVECTOR3& center = D3DXVECTOR3(0.0f, 0.0f, 0.0f), float radius = 1.0f) : m_vCenter(center), m_fRadius(radius)
	{

	}
}; 


//拾取相关类
class Picking
{
private:
	IDirect3DDevice9*   m_pDevice;			//D3D设备
public:
	Picking(IDirect3DDevice9* device);
	~Picking(void);

	//计算拾取射线，输入为鼠标在窗口中的坐标，结果为一个未经过变换的射线，通过指针传参，返回成功与否。
	void CalculatePickingRay(int x, int y, Ray* ray);
	
	//对射线进行变换
	void TransformRay(Ray* ray, D3DXMATRIX* matrix);

	//判断包围球和射线是否相交
	bool Ray_SphereIntersect(const Ray* ray, const BoundingSphere* sphere);

	//提供给外界的接口，接受鼠标坐标&对象包围球指针，判断是否相交
	bool IsPicked(int x, int y, const BoundingSphere* sphere);
};
#endif


