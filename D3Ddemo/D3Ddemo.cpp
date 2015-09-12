// D3DDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "D3DDemo.h"
#include "DirectInput.h"
#include "CameraKernel.h"
#include "Terrain.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Particle.h"
#include "D3DXAnimation.h"
#include "AnimInstance.h"
#include <time.h>

#define MAX_LOADSTRING 100


//ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
HWND                g_hWnd;
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

//---------����3D������Ҫ������------------
LPDIRECT3D9 g_pD3D = NULL;				//D3D�ӿ�ָ��
LPDIRECT3DDEVICE9 g_pDevice = NULL;		//D3D�豸ָ��
CDirectInput* g_pDirectInput = NULL;	//����ָ��
CCameraKernel*      g_pCamera = NULL;    //�����ָ��
CMesh*        g_pMesh1       = NULL;	//�������ָ��1
CMesh*        g_pMesh2       = NULL;	//�������ָ��2
CMesh*        g_pMesh3       = NULL;	//�������ָ��3
CD3DXAnimation* g_pAnimation = NULL;	//�����������ָ��1
CD3DXAnimation* g_pAnimation1 = NULL;	//�����������ָ��2
std::vector<CAnimInstance*> g_pAnimVector;//����ʵ��ָ������


D3DXMATRIX g_matWorld;					//�������



void onCreatD3D()
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!g_pD3D)
		return;

	//���Ӳ���豸�����ķ���
	/*D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);*/

	//��������Ϣ����Ļ��С�����ص�����
	D3DDISPLAYMODE d3ddm;
	ZeroMemory(&d3ddm, sizeof(d3ddm));

	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);


	//����ȫ��ģʽ
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	/*d3dpp.Windowed = false;
	d3dpp.BackBufferWidth = d3ddm.Width;
	d3dpp.BackBufferHeight = d3ddm.Height;*/

	d3dpp.Windowed = true;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ԭ���������ݶ���

	//�Ƿ����Զ����ģ�建��
	d3dpp.EnableAutoDepthStencil = true;
	//��ǰ�Զ����ģ�建��ĸ�ʽ
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//ÿ�����ص���16λ�Ĵ洢�ռ䣬�洢��������ľ���
	

	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

	if (!g_pDevice)
		return;

	//������Ⱦ״̬�������������ֵ
	g_pDevice->SetRenderState(D3DRS_ZENABLE, true);

	//������Ⱦ״̬���رյƹ�
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	//������Ⱦ״̬���ü�ģʽ
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//������Ⱦ״̬����Ȳ���
	g_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);   //����Ȳ��Ժ�����ΪD3DCMP_LESS
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);     //��Ȳ��Գɹ��󣬸�����Ȼ���

	D3DXMatrixTranslation(&g_matWorld, 0.0F, 0.0F, 0.0F);
}

void CreateMesh()
{
	g_pMesh1 = new CMesh(g_pDevice);
	g_pMesh1->CreateMesh("dragon.X");

	//g_pMesh2 = new CMesh(g_pDevice);
	//g_pMesh2->CreateMesh("dragon.X");

	//g_pMesh3 = new CMesh(g_pDevice);
	//g_pMesh3->CreateMesh("tiny.x");
}

void CreateCamera()
{
	g_pCamera = new CCameraKernel(g_pDevice);
	g_pCamera->SetCameraPosition(&D3DXVECTOR3(0.0f, 0.0f, -500.0f));
	g_pCamera->SetTargetPosition(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_pCamera->SetViewMatrix();
	g_pCamera->SetProjectionMartix();
}

void CreateAnimationMesh()
{
	//g_pAnimation = new CD3DXAnimation(g_pDevice);
	//g_pAnimation->Init("lxq.X");

	g_pAnimation1 = new CD3DXAnimation(g_pDevice);
	if (g_pAnimation1->Init("tiny.X") == S_OK)
	{
		D3DXMATRIX matWorld1, matWorld2, matWorld3, matWorld4, matWorld5;  
		D3DXMatrixRotationX(&matWorld2, -90.0f);
		D3DXMatrixRotationZ(&matWorld1, 180.0f);
		D3DXMatrixRotationY(&matWorld5, -30.0f);
		D3DXMatrixScaling(&matWorld3, 0.1f, 0.1f, 0.1f);
		matWorld1 = matWorld3 * matWorld1 *matWorld2;

		srand((int)time(0));

		for (int i = 0; i < 1; i++)
		{
			CAnimInstance* instance = new CAnimInstance();
			instance->Init(g_pAnimation1);
			D3DXMatrixTranslation(&matWorld4, i * 15.0f, -20.0f, 0.0f);  
			instance->SetMatrix(&(matWorld1 * matWorld4));
			instance->PlayAnimation(instance->GetAnimationSet(rand()%1)->GetName(), true);
			g_pAnimVector.push_back(instance);
		}
	}
	else
	{
		MessageBox(g_hWnd, "��ȡģ��ʧ��", "error", NULL);
	}

	
}

void SetLight()
{
	// ���ù���
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type          = D3DLIGHT_POINT;
	light.Ambient       = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse       = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular      = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	//light.Direction     = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	light.Position      = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	light.Attenuation0  = 1.0f;
	light.Attenuation1  = 0.0f;
	light.Attenuation2  = 0.0f;
	light.Range			= 5000.0f;
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}



void onInit()
{
	//��ʼ��D3D
	onCreatD3D();

	//����Meshģ��
	CreateMesh();

	//���������
	CreateCamera();

	//���ù���
	SetLight();

	//������������
	CreateAnimationMesh();
}



void onDestroy()
{
	SAFE_DELETE(g_pDirectInput);
	SAFE_DELETE(g_pCamera);
	SAFE_RELEASE(g_pDevice);
	SAFE_DELETE(g_pMesh1);
	SAFE_DELETE(g_pMesh2);
	SAFE_DELETE(g_pMesh3);
	SAFE_DELETE(g_pAnimation);
}

void onLogic(float fElapsedTime)
{
	//ʹ��DirectInput���ȡ����
	g_pDirectInput->GetInput();

	// ��������������ƶ��ӽ�
	if (g_pDirectInput->IsKeyDown(DIK_A))  g_pCamera->MoveAlongRightVec(-10.0f);
	if (g_pDirectInput->IsKeyDown(DIK_D))  g_pCamera->MoveAlongRightVec( 10.0f);
	if (g_pDirectInput->IsKeyDown(DIK_W)) g_pCamera->MoveAlongLookVec( 10.0f);
	if (g_pDirectInput->IsKeyDown(DIK_S))  g_pCamera->MoveAlongLookVec(-10.0f);
	if (g_pDirectInput->IsKeyDown(DIK_I))  g_pCamera->MoveAlongUpVec( 10.0f);
	if (g_pDirectInput->IsKeyDown(DIK_K))  g_pCamera->MoveAlongUpVec(-10.0f);

	//���������������ת�ӽ�
	if (g_pDirectInput->IsKeyDown(DIK_LEFT))  g_pCamera->RotationUpVec(-0.003f);
	if (g_pDirectInput->IsKeyDown(DIK_RIGHT))  g_pCamera->RotationUpVec( 0.003f);
	if (g_pDirectInput->IsKeyDown(DIK_UP))  g_pCamera->RotationRightVec(-0.003f);
	if (g_pDirectInput->IsKeyDown(DIK_DOWN))  g_pCamera->RotationRightVec( 0.003f);
	if (g_pDirectInput->IsKeyDown(DIK_J)) g_pCamera->RotationLookVec(-0.001f);
	if (g_pDirectInput->IsKeyDown(DIK_L)) g_pCamera->RotationLookVec( 0.001f);


	if (g_pDirectInput->IsKeyDown((DIK_P)))

	{
		delete g_pAnimVector[g_pAnimVector.size() - 1];
		g_pAnimVector.pop_back();
	}

	//������������������������ת
	//g_pCamera->RotationUpVec(g_pDirectInput->MouseDX()* 0.001f);
	//g_pCamera->RotationRightVec(g_pDirectInput->MouseDY() * 0.001f);

	//�����ֿ��ƹ۲����������
	static FLOAT fPosZ=0.0f;
	fPosZ += g_pDirectInput->MouseDZ()*3.0f;

	//���㲢����ȡ���任����
	D3DXMATRIX matView;
	g_pCamera->CalculateViewMatrix(&matView);
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);

	//����ȷ������任����浽g_matWorld��
	D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, fPosZ);
}

void onRender(float fElasedTime)
{
	//ǰ����������0��NULLʱ�����������Ϸ���ڵ����ݣ�����Ǻ�̨��
	//������������Ķ���ǰ���ʾ�����ɫ�������������ʾ�����Ȼ�����,D3DCLEAR_STENCIL���ģ�建����
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,100,100), 1.0f, 0);

	g_pDevice->BeginScene();

	g_pMesh1->DrawMesh(g_matWorld);
	

	for (int i = 0; i < g_pAnimVector.size(); i++)
	{
		g_pAnimVector[i]->Update(fElasedTime);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pAnimVector[i]->Render();
	}

	g_pDevice->EndScene();


	g_pDevice->Present(NULL, NULL, NULL, NULL);
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_D3DDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DDEMO));

	

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			static DWORD dwTime = timeGetTime();
			DWORD dwCurrentTime = timeGetTime();
			DWORD dwElapsedTime = dwCurrentTime - dwTime;
			float fElapsedTime = dwElapsedTime * 0.001f;

			//------------��Ⱦ���߼����ִ���----------
			onLogic(fElapsedTime);
			onRender(fElapsedTime);
			//-----------------------------------------
			if (dwElapsedTime < 1000 / 60)
			{
				Sleep(1000/ 60 - dwElapsedTime);
			}
			dwTime = dwCurrentTime;
		}
	}

	onDestroy();
	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DDEMO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_D3DDEMO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!g_hWnd)
   {
      return FALSE;
   }

  //��ʼ��DirectInput��
   g_pDirectInput = new CDirectInput();
   g_pDirectInput->Init(g_hWnd, hInst, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);

   SetMenu(g_hWnd, NULL);
   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   onInit();

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND g_hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(g_hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(g_hWnd, message, wParam, lParam);
	}
	return 0;
}
