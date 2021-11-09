#include "Engine.h"

DEFINITION_SINGLE(CEngine)

bool	CEngine::m_bLoop = true;

CEngine::CEngine()	:
	m_hInst(0),
	m_hWnd(0),
	m_tRS{}
{
}

CEngine::~CEngine()
{
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* cName, unsigned int iWidth, unsigned int iHeight, int iIconID, bool bWindowMode)
{
	m_hInst = hInst;

	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	Register(cName, iIconID);
	Create(cName);

	return true;
}

int CEngine::Run()
{
	MSG msg = {};

	while (m_bLoop)
	{
		// GetMessage�� �޼����� ���� ��� �ٸ����� �� �� ����.
		// �޼����� �ö����� ����ϰ� �ִ� �ð��� �������� ����Ÿ���̶�� �Ѵ�.
		// ������ �޼����� �ִ� �ð����� ���� �ð��� �ξ� ���.
		// �׷��� ������ �������� ����Ÿ�ӵ��� ������ ���۵� �� �ְ� �����Ѵ�.
		// PeekMessage�� �޼���ť���� �޼����� ���´�.
		// �׷��� ���� �޼����� ���ٸ� false�� �����ϸ鼭 �ٷ� ����������
		// �޼����� �ִٸ� true�� �����ϸ鼭 �ش� �޼����� �����´�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// WM_KEYDOWN �̶�� �޼����� �ִ�. �̴� Ű���� Ű�� �������� �߻��Ǵ� �޼���
			// �̴�. TranslateMessage �Լ������� �޼����� �������ָ� WM_KEYDOWN ������
			// �Ǵ����ְ� ������ Ű�� ���� Ű������ �Ǵ��ؼ� �Ϲ� ���� Ű��� WM_CHAR���
			// �޽����� ���� �޼��� ť�� �߰����ְ� �ȴ�.
			TranslateMessage(&msg);

			// DispatchMessage �Լ��� �޼����� ������ ���ν����� �����ش�.
			DispatchMessage(&msg);
		}

		// �����찡 ����Ÿ���� ��� ����� ������ �ȴ�.
		else
		{
		}
	}

	return (int)msg.wParam;
}

ATOM CEngine::Register(const TCHAR* cName, int IconID)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	// �۾������� �ٲ� �ٽ� �׸��Բ� ���ش�. ���ο� ���� ��� �ٽ� �׸���.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// �޼����� ť�� �������� �ش� �޼����� �������� ������ �޼����� ���ڷ� �����ؼ�
	// ȣ������ �Լ��� �����Ѵ�.
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	// Window Instance�� �����Ѵ�.
	wcex.hInstance = m_hInst;

	// ���������� ��������� ����� ������ �̹����� �����Ѵ�.
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));


	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	// �����ڵ� ���ڿ��� ����Ҷ� L"" �� �ٿ��� ����� �Ѵ�.
	// TEXT ��ũ�δ� "" �տ� L �� �ٿ��� L"" �� ������ش�.
	// �����ڵ��϶��� �̷��� ���ְ� multibyte  �϶��� �׳� "" �� ������ش�.
	wcex.lpszClassName = cName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IconID));

	return RegisterClassExW(&wcex);
}

BOOL CEngine::Create(const TCHAR* cName)
{
	m_hWnd = CreateWindowW(cName, cName, WS_OVERLAPPEDWINDOW, 0, 0, m_tRS.iWidth, m_tRS.iHeight, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return FALSE;

	// Ŭ���̾�Ʈ ������ 1280, 720���� ������ش�.
	// RECT : �簢���� ǥ���ϴ� ����ü�̴�.
	// left, top, right, bottom 4���� ������ �����Ǿ� �ִ�.
	RECT    rc = { 0, 0, (LONG)m_tRS.iWidth, (LONG)m_tRS.iHeight };

	// 1������ : Ŭ���̾�Ʈ ������ ũ�⸦ �����Ѵ�.
	// �� �Լ��� �Ϸ�Ǹ� rc���� ���� Ŭ���̾�Ʈ ������ ���ϴ� ũ�� �� �� �ִ�
	// ��ü �������� left, top, right, bottom ������ ������ �ȴ�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ ���� Rect�� �̿��ؼ� ������ ũ�⸦ �����Ѵ�.
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	// SW_SHOW : ������â�� ȭ�鿡 �����ش�.
	// SW_HIDE : â�� ����� ������ ȭ�鿡 �����ִ°� �ƴϴ�.
	ShowWindow(m_hWnd, SW_SHOW);

	// UpdateWindow �Լ��� ������ �κ��� �ִٸ� �����϶�� ����� �����ִ� �Լ��̴�.
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

		// HDC : ȭ�鿡 ����ϱ� ���� �׸��� �����̴�.
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
