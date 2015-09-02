#ifndef __CDIRECTINPUT_H_
#define __CDIRECTINPUT_H_

#include "DInput.h"
//��ӿ��ļ�
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma once
class CDirectInput
{
private:
	IDirectInput8* m_pDirectInput;					//DirectInput�ӿڶ���
	IDirectInputDevice8* m_KeyboardDevice;			//�����豸�ӿ�
	char m_keyBuffer[256];							//���ڱ�����̼�ֵ������

	IDirectInputDevice8* m_MouseDevice;				//����豸�ӿ�
	DIMOUSESTATE m_MouseState;						//����ֵ�洢�ṹ��
public:
	CDirectInput(void);
	virtual ~CDirectInput(void);

	//��ʼ��DirectInput�Լ���������豸
	HRESULT Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);

	//���������Ϣ
	void GetInput();

	//������ĳ�����Ƿ񱻰���
	bool IsKeyDown(int iKey);

	//������ĳ�����Ƿ񱻰���
	bool IsMouseButtonDown(int iButton);

	//������X������ֵ
	float MouseDX();

	//������Y������ֵ
	float MouseDY();

	//������Z�ᣨ�����֣�����ֵ
	float MouseDZ();
};
#endif
