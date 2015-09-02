#include "stdafx.h"
#include "DirectInput.h"


CDirectInput::CDirectInput(void)
{
	//赋初值
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	m_MouseDevice = NULL;

	ZeroMemory(m_keyBuffer, sizeof(m_keyBuffer));
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}


CDirectInput::~CDirectInput(void)
{
	//释放对象
	if (m_KeyboardDevice)
		m_KeyboardDevice->Unacquire();
	if (m_MouseDevice)
		m_MouseDevice->Unacquire();
	SAFE_RELEASE(m_MouseDevice);
	SAFE_RELEASE(m_KeyboardDevice);
	SAFE_RELEASE(m_pDirectInput);
}

HRESULT CDirectInput::Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	//初始化接口对象
	DirectInput8Create(
		hInstance,					//程序实例的句柄
		0x0800,		//0x0800当前使用的DirectInput版本号
		IID_IDirectInput8,			//接口标识，使用IID_IDirectInput8即可
		(void**)&m_pDirectInput,	//创建的接口的对象的指针
		NULL						//COM对象相关联参数，为NULL
		);

	//初始化键盘设备
	m_pDirectInput->CreateDevice(		//创建设备
		GUID_SysKeyboard,				//GUID值，对于鼠标和键盘有宏定义，其余设备需要通过枚举找出
		&m_KeyboardDevice,				//键盘设备指针的指针
		NULL							//COM相关参数，为NULL
		);
	m_KeyboardDevice->SetCooperativeLevel(//设置协作级别
		hWnd,								//窗口句柄
		keyboardCoopFlags					//协作级别（前台后台，独占非独占）
		);
	m_KeyboardDevice->SetDataFormat(		//设置数据格式
		&c_dfDIKeyboard);					//键盘鼠标等的数据格式，宏定义
	m_KeyboardDevice->Acquire();			//获得设备控制权
	m_KeyboardDevice->Poll();				//轮询设备

	//初始化鼠标设备
	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_MouseDevice, NULL);
	m_MouseDevice->SetCooperativeLevel(hWnd, mouseCoopFlags);
	m_MouseDevice->SetDataFormat(&c_dfDIMouse);
	m_MouseDevice->Acquire();
	m_MouseDevice->Poll();
	return true;
}

void CDirectInput::GetInput()
{
	//获得键盘输入消息
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	if (hr)
	{
		m_KeyboardDevice->Acquire();
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	}

	//获得鼠标输入信息
	hr = m_MouseDevice->GetDeviceState(sizeof(m_MouseState), (void**)&m_MouseState);
	if (hr)
	{
		m_MouseDevice->Acquire();
		m_MouseDevice->GetDeviceState(sizeof(m_MouseState), (void**)&m_MouseState);
	}
}

bool CDirectInput::IsKeyDown(int iKey)
{
	if (m_keyBuffer[iKey] & 0x80)
		return true;
	return false;
}

bool CDirectInput::IsMouseButtonDown(int iButton)
{
	return (m_MouseState.rgbButtons[iButton] & 0x80) != 0;
}

float CDirectInput::MouseDX()
{
	return (float) m_MouseState.lX;
}

float CDirectInput::MouseDY()
{
	return (float) m_MouseState.lY;
}

float CDirectInput::MouseDZ()
{
	return (float) m_MouseState.lZ;
}
