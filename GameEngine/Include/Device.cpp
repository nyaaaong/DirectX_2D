#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()	:
	m_pDevice(nullptr),
	m_pContext(nullptr),
	m_pSwapChain(nullptr),
	m_pTargetView(nullptr),
	m_pDepthView(nullptr),
	m_hWnd(0),
	m_tRS{}
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_pDepthView);
	SAFE_RELEASE(m_pTargetView);

	SAFE_RELEASE(m_pSwapChain);

	if (m_pContext)
		m_pContext->ClearState();

	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

bool CDevice::Init(HWND hWnd, unsigned int iWidth, unsigned int iHeight, bool bWindowMode)
{
	m_hWnd = hWnd;
	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	unsigned int iFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // 나중에 폰트 출력을 위해 BRGA로 맞춰준다.

#ifdef _DEBUG
	iFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	DXGI_SWAP_CHAIN_DESC	tSwapDesc = {};

	tSwapDesc.BufferDesc.Width = iWidth;
	tSwapDesc.BufferDesc.Height = iHeight;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 60; // RefreshRate는 주사율을 말한다
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapDesc.OutputWindow = hWnd;
	tSwapDesc.SampleDesc.Count = 1;
	tSwapDesc.SampleDesc.Quality = 0;
	tSwapDesc.Windowed = bWindowMode;
	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL	eLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	eLevel1 = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, iFlag, &eLevel, 1, D3D11_SDK_VERSION, &tSwapDesc, &m_pSwapChain, &m_pDevice, &eLevel1, &m_pContext)))
		return false;

	// SwapChain이 갖고 있는 백버퍼를 얻어온다
	ID3D11Texture2D* pBackBuffer = nullptr;

	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

	// BackBuffer과 연결된 RenderTargetView를 생성한다
	m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pTargetView);

	SAFE_RELEASE(pBackBuffer);

	// 깊이 버퍼를 만든다
	D3D11_TEXTURE2D_DESC	tDepthDesc = {};

	tDepthDesc.Width = iWidth;
	tDepthDesc.Height = iHeight;
	tDepthDesc.ArraySize = 1;
	tDepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tDepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tDepthDesc.Usage = D3D11_USAGE_DEFAULT;
	tDepthDesc.SampleDesc.Count = 1;
	tDepthDesc.SampleDesc.Quality = 0;
	tDepthDesc.MipLevels = 1;

	ID3D11Texture2D* pDepthBuffer = nullptr;

	m_pDevice->CreateTexture2D(&tDepthDesc, nullptr, &pDepthBuffer);
	m_pDevice->CreateDepthStencilView(pDepthBuffer, nullptr, &m_pDepthView);

	SAFE_RELEASE(pDepthBuffer);

	D3D11_VIEWPORT	tVP = {};

	tVP.Width = (float)iWidth;
	tVP.Height = (float)iHeight;
	tVP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &tVP);

	return true;
}

void CDevice::ClearRenderTarget(float fClearColor[4])
{
	m_pContext->ClearRenderTargetView(m_pTargetView, fClearColor);
}

void CDevice::ClearDepthStencil(float fDepth, unsigned char fStencil)
{
	m_pContext->ClearDepthStencilView(m_pDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, fDepth, fStencil);
}

void CDevice::RenderStart()
{
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthView);
}

void CDevice::Flip()
{
	m_pSwapChain->Present(0, 0);
}
