/*!
 * \file IBounding.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \包围体接口类，所有的包围盒，包围球等都继承该类的接口
 */
#ifndef __IBOUNDING_H_
#define __IBOUNDING_H_

#include "IRenderActor.h"

class IBounding : public IRenderActor
{
public:
	IBounding(void);
	virtual ~IBounding(void);
};

#endif



