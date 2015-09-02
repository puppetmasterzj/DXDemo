#ifndef __CDIRECTINPUT_H_
#define __CDIRECTINPUT_H_

#include "DInput.h"
//添加库文件
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma once
class CDirectInput
{
private:
	IDirectInput8* m_pDirectInput;					//DirectInput接口对象
	IDirectInputDevice8* m_KeyboardDevice;			//键盘设备接口
	char m_keyBuffer[256];							//用于保存键盘键值的数组

	IDirectInputDevice8* m_MouseDevice;				//鼠标设备接口
	DIMOUSESTATE m_MouseState;						//鼠标键值存储结构体
public:
	CDirectInput(void);
	virtual ~CDirectInput(void);

	//初始化DirectInput以及键盘鼠标设备
	HRESULT Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);

	//获得输入信息
	void GetInput();

	//检测键盘某按键是否被按下
	bool IsKeyDown(int iKey);

	//检测鼠标某按键是否被按下
	bool IsMouseButtonDown(int iButton);

	//获得鼠标X轴坐标值
	float MouseDX();

	//获得鼠标Y轴坐标值
	float MouseDY();

	//获得鼠标Z轴（鼠标滚轮）坐标值
	float MouseDZ();
};
#endif
