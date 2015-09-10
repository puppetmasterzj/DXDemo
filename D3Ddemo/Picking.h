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

class Picking
{
public:
	Picking(void);
	~Picking(void);
};
#endif


