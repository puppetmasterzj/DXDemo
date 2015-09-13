// D3DDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "D3DDemo.h"
#include "DirectInput.h"
#include "CameraKernel.h"
#include "Terrain.h"
#include "D3DXMesh.h"
#include "SkyBox.h"
#include "Particle.h"
#include "D3DXAnimation.h"
#include "AnimInstance.h"
#include "Picking.h"
#include <time.h>
#include "MeshInstance.h"

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
Picking*	  g_PickingSystem = NULL;	//ʰȡϵͳָ��
D3DXMesh*        g_pMesh1       = NULL;	//�������ָ��1
D3DXMesh*        g_pMesh2       = NULL;	//�������ָ��2
D3DXMesh*        g_pMesh3       = NULL;	//�������ָ��3
CD3DXAnimation* g_pAnimation = NULL;	//�����������ָ��1
CD3DXAnimation* g_pAnimation1 = NULL;	//�����������ָ��2
std::vector<CAnimInstance*> g_pAnimVector;//����ʵ��ָ������
std::vector<IRenderActor*> g_pActorVector;//�ɻ�������ʵ��ָ������

CTerrain* g_pTerrian = NULL;			//����ϵͳָ��
CParticle* g_pParticle = NULL;
CSkyBox* g_pSkybox = NULL;


D3DXMATRIX g_matWorld;					//�������

BoundingSphere g_BoundingSphere;

//D3DSURFACE_DESC g_pBackBuffer;
//D3DXVECTOR3 g_Mdesc;
//D3DXVECTOR3 g_Voc;
//
//BOOL pointCheck(HWND hWnd)
//{
//	D3DXVECTOR3			vPickRayOrig;
//	D3DXVECTOR3			vPickRayDir;
//	LPD3DXBUFFER		pAllHits1;
//	DWORD				CountOfHits1 = 0;
//	RECT			    WndRect;
//	POINT				ptCursor;
//	BOOL				hit;
//	GetCursorPos(&ptCursor);
//	//ClientToScreen(hWnd,&ptCursor);
//	GetWindowRect(hWnd,&WndRect);
//	if(ptCursor.x>WndRect.right||ptCursor.x<WndRect.left||ptCursor.y>WndRect.bottom||ptCursor.y<WndRect.top)
//	{
//		return NULL;
//	}
//	D3DXMATRIX matProj;
//	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
//	D3DXMATRIX matView;
//	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
//	D3DXMATRIX matWorld;
//	g_pDevice->GetTransform(D3DTS_WORLD, &matWorld);
//
//	D3DXVECTOR3 v;
//
//	v.x =  ( ( ( 2.0f * ptCursor.x ) / g_pBackBuffer.Width  ) - 1 ) / matProj._11;
//	v.y = -( ( ( 2.0f * ptCursor.y ) / g_pBackBuffer.Height ) - 1 ) / matProj._22;
//	v.z =  1.0f;
//
//	D3DXMATRIX matWorldView =  matView;
//	D3DXMATRIX m;
//	D3DXMatrixInverse(&m, NULL, &matWorldView);
//
//	vPickRayDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
//	vPickRayDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32;
//	vPickRayDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;
//
//	vPickRayOrig.x = m._41;
//	vPickRayOrig.y = m._42;
//	vPickRayOrig.z = m._43;
//
//	D3DXIntersect(g_pMesh1->GetMeshPointer(), &vPickRayOrig, &vPickRayDir, &hit, NULL, 
//		NULL, NULL, NULL, &pAllHits1, &CountOfHits1);
//	if(hit)
//	{
//		MessageBox(g_hWnd, "hehehe", "Hit!!", NULL);
//	}
//	else
//	{
//		return !hit;
//	}
//	return hit;
//}

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

	/*d3dpp.Windowed = true;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;*/

	d3dpp.BackBufferWidth            = 800;
	d3dpp.BackBufferHeight           = 600;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 2;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; //������ԭ���������ݶ���
	d3dpp.hDeviceWindow              = g_hWnd;
	d3dpp.Windowed                   = true;
	d3dpp.EnableAutoDepthStencil     = true;				//�Ƿ����Զ����ģ�建��
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;		//��ǰ�Զ����ģ�建��ĸ�ʽ
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//���������ָ�ʽ��ʹ�����ָ�ʽʱ���������Զ�����ʱ����˸������
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	
	//d3dpp.EnableAutoDepthStencil = true;
	
	
	

	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

	if (!g_pDevice)
		return;

	////ʰȡ��أ���ʱ���롣BackBuffer
	//IDirect3DSurface9* pBackBuffer = NULL;
	//g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//pBackBuffer->GetDesc(&g_pBackBuffer);
	//pBackBuffer->Release();


	//������Ⱦ״̬�������������ֵ
	g_pDevice->SetRenderState(D3DRS_ZENABLE, true);

	//������Ⱦ״̬���رյƹ�
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	//������Ⱦ״̬���ü�ģʽ
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//������Ⱦ״̬����Ȳ���
	g_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);     //����Ȳ��Ժ�����ΪD3DCMP_LESS
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);     //��Ȳ��Գɹ��󣬸�����Ȼ���

	D3DXMatrixTranslation(&g_matWorld, 0.0F, 0.0F, 0.0F);

	//��ʼ��ʰȡϵͳ
	g_PickingSystem = new Picking(g_pDevice);
}

void CreateMesh()
{

	g_pMesh1 = new D3DXMesh(g_pDevice);
	g_pMesh1->Init("dragon.X");
	g_pMesh1->CreateBoundingSphere(&g_BoundingSphere);

	for (unsigned int i = 0; i < 10; i++)
	{
		MeshInstance* instance = new MeshInstance();
		instance->Init(g_pMesh1);
		instance->SetPosition(Vec3(i * 100, 1000, 0));
		instance->SetScale(Vec3(i * 0.1, i * 0.1, i * 0.1));
		instance->CalculateMatrix();
		g_pActorVector.push_back(instance);
	}


	//g_pMesh2 = new CMesh(g_pDevice);
	//g_pMesh2->CreateMesh("dragon.X");

	//g_pMesh3 = new CMesh(g_pDevice);
	//g_pMesh3->CreateMesh("tiny.x");
}

void CreateCamera()
{
	g_pCamera = new CCameraKernel(g_pDevice);
	g_pCamera->SetCameraPosition(&D3DXVECTOR3(0.0f, 1000.0f, -500.0f));
	g_pCamera->SetTargetPosition(&D3DXVECTOR3(0.0f, 1000.0f, 0.0f));
	g_pCamera->SetViewMatrix();
	g_pCamera->SetProjectionMartix();
}

void CreateAnimationMesh()
{
	//g_pAnimation = new CD3DXAnimation(g_pDevice);
	//g_pAnimation->Init("lxq.X");

	g_pAnimation1 = new CD3DXAnimation(g_pDevice);
	if (g_pAnimation1->Init("lxq.X") == S_OK)
	{
		srand((int)time(0));

		for (int i = 0; i < 10; i++)
		{
			CAnimInstance* instance = new CAnimInstance();
			instance->Init(g_pAnimation1);
			//D3DXMatrixTranslation(&matWorld4, i * 15.0f, 1000.0f, 0.0f);  
			instance->SetPosition(Vec3(i * 100.0f, 1000.0f, 0.0f));
			instance->SetScale(Vec3(1.0f, 1.0f, 1.0f));
			instance->CalculateMatrix();
			instance->PlayAnimation(instance->GetAnimationSet(rand()%1)->GetName(), true);
			g_pActorVector.push_back(instance);
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

void CreateEnvironment()
{
	//��������ϵͳ
	g_pTerrian = new CTerrain(g_pDevice);
	g_pTerrian->LoadTerrainFromFile(TEXT("heighmap.raw"), TEXT("terraintexture.jpg"));  
	g_pTerrian->InitTerrain(200, 200, 100.0f, 10.0f);

	//������պ�
	g_pSkybox = new CSkyBox(g_pDevice);  
	g_pSkybox->InitSkyBox(10000.0f);  
	g_pSkybox->InitSkyBoxTexture("skyfront.png", "skyback.png", "skyleft.png", "skyright.png", "skytop.png"); 

	g_pParticle = new CParticle(g_pDevice);
	g_pParticle->InitParticle();
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

	//��ʼ������
	CreateEnvironment();
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

	for (unsigned int i = 0; i < g_pActorVector.size(); i++)
	{
		g_pActorVector[i]->Update(fElapsedTime);
	}

	//����ȷ������任����浽g_matWorld��
	D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, fPosZ);

	/*pointCheck(g_hWnd);*/

	////����ʰȡϵͳ
	//int x = g_pDirectInput->MouseDX();
	//int y = g_pDirectInput->MouseDY();
	//if ( x > 200 && x < 1000 && y > 200 && y < 800)
	//{
	//	
	//}
}

void onRender(float fElasedTime)
{
	//ǰ����������0��NULLʱ�����������Ϸ���ڵ����ݣ�����Ǻ�̨��
	//������������Ķ���ǰ���ʾ�����ɫ�������������ʾ�����Ȼ�����,D3DCLEAR_STENCIL���ģ�建����
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,100,100), 1.0f, 0);

	g_pDevice->BeginScene();

	//D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, 0.0f);

	//g_pMesh1->Render(&g_matWorld);
	
	for (unsigned int i = 0; i < g_pActorVector.size(); i++)
	{
		g_pActorVector[i]->Render();
	}
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pSkybox->RenderSkyBox(&g_matWorld);
	g_pTerrian->RenderTerrain(&g_matWorld, false);
	g_pParticle->UpdateParticle(fElasedTime);
	g_pParticle->RenderParticle();
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
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (g_PickingSystem->IsPicked(x, y, &g_BoundingSphere))
			MessageBox(g_hWnd, "PickTest OK!", "Information", NULL);
			break;
		}
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
