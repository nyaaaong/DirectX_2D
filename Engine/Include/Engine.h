#pragma once

#include "GameInfo.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_tRS;
	static bool m_bLoop;
	float		m_fClearColor[4];
	class CTimer* m_pTimer;

public:
	bool Init(HINSTANCE hInst, const TCHAR* cName, unsigned int iWidth, unsigned int iHeight, int iIconID, bool bWindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, unsigned int iWidth, unsigned int iHeight, bool bWindowMode = true);
	int Run();
	void Logic();

private:
	bool Update(float fTime);
	bool PostUpdate(float fTime);
	bool Render(float fTime);

private:
	ATOM Register(const TCHAR* cName, int IconID);
	BOOL Create(const TCHAR* cName);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CEngine)
};

