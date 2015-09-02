#include "stdafx.h"
#include "DirectInput.h"


CDirectInput::CDirectInput(void)
{
	//����ֵ
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	m_MouseDevice = NULL;

	ZeroMemory(m_keyBuffer, sizeof(m_keyBuffer));
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}


CDirectInput::~CDirectInput(void)
{
	//�ͷŶ���
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
	//��ʼ���ӿڶ���
	DirectInput8Create(
		hInstance,					//����ʵ���ľ��
		0x0800,		//0x0800��ǰʹ�õ�DirectInput�汾��
		IID_IDirectInput8,			//�ӿڱ�ʶ��ʹ��IID_IDirectInput8����
		(void**)&m_pDirectInput,	//�����ĽӿڵĶ����ָ��
		NULL						//COM���������������ΪNULL
		);

	//��ʼ�������豸
	m_pDirectInput->CreateDevice(		//�����豸
		GUID_SysKeyboard,				//GUIDֵ���������ͼ����к궨�壬�����豸��Ҫͨ��ö���ҳ�
		&m_KeyboardDevice,				//�����豸ָ���ָ��
		NULL							//COM��ز�����ΪNULL
		);
	m_KeyboardDevice->SetCooperativeLevel(//����Э������
		hWnd,								//���ھ��
		keyboardCoopFlags					//Э������ǰ̨��̨����ռ�Ƕ�ռ��
		);
	m_KeyboardDevice->SetDataFormat(		//�������ݸ�ʽ
		&c_dfDIKeyboard);					//�������ȵ����ݸ�ʽ���궨��
	m_KeyboardDevice->Acquire();			//����豸����Ȩ
	m_KeyboardDevice->Poll();				//��ѯ�豸

	//��ʼ������豸
	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_MouseDevice, NULL);
	m_MouseDevice->SetCooperativeLevel(hWnd, mouseCoopFlags);
	m_MouseDevice->SetDataFormat(&c_dfDIMouse);
	m_MouseDevice->Acquire();
	m_MouseDevice->Poll();
	return true;
}

void CDirectInput::GetInput()
{
	//��ü���������Ϣ
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	if (hr)
	{
		m_KeyboardDevice->Acquire();
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	}

	//������������Ϣ
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
