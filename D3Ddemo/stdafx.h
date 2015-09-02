// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <timeapi.h>


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}}  
#endif // !SAFE_RELEASE

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete p; p = NULL;}}
#endif // !SAFE_DELETE


#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
