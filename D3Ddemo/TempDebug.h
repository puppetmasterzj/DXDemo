#ifndef __TEMPDEBUG_H
#define __TEMPDEBUG_H_

#include "stdafx.h"
#include <debugapi.h>

void TempDebug(LPCTSTR str)
{
#ifdef _DEBUG
	OutputDebugString(str);
#endif
}

#endif