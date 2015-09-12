#include "stdafx.h"
#include "IRenderRes.h"


IRenderRes::IRenderRes(LPDIRECT3DDEVICE9 device)
	: m_pDevice(device),
	  m_filename("NULL")
{

}


IRenderRes::~IRenderRes(void)
{

}

void IRenderRes::SetResourceName(LPCTSTR name)
{
	if (name)
	m_filename = name;
}