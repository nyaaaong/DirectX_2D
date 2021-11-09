#pragma once

#include "GameInfo.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_tRS;
	static bool m_bLoop;

public:
	bool Init(HINSTANCE hInst, const TCHAR* cName, unsigned int iWidth, unsigned int iHeight, int iIconID, bool bWindowMode = true);
	int Run();

private:
	ATOM Register(const TCHAR* cName, int IconID);
	BOOL Create(const TCHAR* cName);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CEngine)
};

