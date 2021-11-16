#pragma once

#include "GameInfo.h"

class CDevice
{
private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pTargetView; // BackBuffer에 픽셀을 쓰기 위해 TargetView에 연결해준다.
	ID3D11DepthStencilView* m_pDepthView; // 깊이 버퍼, 스텐실 버퍼를 쓰기 위해 DepthView에 연결해준다.
	HWND	m_hWnd;
	Resolution	m_tRS;

public:
	ID3D11Device* GetDevice()	const
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* GetContext()	const
	{
		return m_pContext;
	}

	IDXGISwapChain* GetSwapChain()	const
	{
		return m_pSwapChain;
	}

	const Resolution& GetResolution()	const
	{
		return m_tRS;
	}

public:
	bool Init(HWND hWnd, unsigned int iWidth, unsigned int iHeight, bool bWindowMode);
	void ClearRenderTarget(float fClearColor[4]);
	void ClearDepthStencil(float fDepth, unsigned char fStencil);
	void RenderStart();
	void Flip();

	DECLARE_SINGLE(CDevice)
};

