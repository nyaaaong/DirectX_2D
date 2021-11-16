#include "Engine.h"
#include "Device.h"
#include "Resource/ResourceManager.h"

DEFINITION_SINGLE(CEngine)

bool	CEngine::m_bLoop = true;

CEngine::CEngine()	:
	m_hInst(0),
	m_hWnd(0),
	m_tRS{},
	m_fClearColor{}
{
	m_fClearColor[0] = 0.64f;
	m_fClearColor[1] = 0.8f;
	m_fClearColor[2] = 0.63f;
}

CEngine::~CEngine()
{
	CResourceManager::DestroyInst();
	CDevice::DestroyInst();
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* cName, unsigned int iWidth, unsigned int iHeight, int iIconID, bool bWindowMode)
{
	m_hInst = hInst;

	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	Register(cName, iIconID);
	Create(cName);

	return Init(hInst, m_hWnd, iWidth, iHeight, bWindowMode);
}

bool CEngine::Init(HINSTANCE hInst, HWND hWnd, unsigned int iWidth, unsigned int iHeight, bool bWindowMode)
{
	m_hInst = hInst;
	m_hWnd = hWnd;

	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	if (!CDevice::GetInst()->Init(hWnd, iWidth, iHeight, bWindowMode))
		return false;

	if (!CResourceManager::GetInst()->Init())
		return false;

    return true;
}

int CEngine::Run()
{
	MSG msg = {};

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CEngine::Logic()
{
	Update(0.f);
	PostUpdate(0.f);
	Render(0.f);
}

bool CEngine::Update(float fTime)
{
    return true;
}

bool CEngine::PostUpdate(float fTime)
{
    return true;
}

bool CEngine::Render(float fTime)
{
	CDevice::GetInst()->RenderStart();
	CDevice::GetInst()->ClearRenderTarget(m_fClearColor);
	CDevice::GetInst()->ClearDepthStencil(1.f, 0);

	CDevice::GetInst()->Flip();

    return true;
}

ATOM CEngine::Register(const TCHAR* cName, int IconID)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = cName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IconID));

	return RegisterClassExW(&wcex);
}

BOOL CEngine::Create(const TCHAR* cName)
{
	m_hWnd = CreateWindowW(cName, cName, WS_OVERLAPPEDWINDOW, 600, 250, m_tRS.iWidth, m_tRS.iHeight, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return FALSE;

	RECT    rc = { 0, 0, (LONG)m_tRS.iWidth, (LONG)m_tRS.iHeight };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 600, 250, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
