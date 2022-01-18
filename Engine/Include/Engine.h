#pragma once

#include "GameInfo.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_RS;
	static bool	m_Loop;
	float		m_ClearColor[4];
	class CTimer* m_Timer;
	bool		m_Start;
	bool		m_Play;
	Engine_Space	m_Space;
	Mouse_State		m_MouseState;
	CSharedPtr<class CWidgetWindow>	m_MouseWidget[(int)Mouse_State::Max];

public:
	Engine_Space GetEngineSpace()	const
	{
		return m_Space;
	}

	void SetEngineSpace(Engine_Space Space)
	{
		m_Space = Space;
	}

	bool IsPlay()	const
	{
		return m_Play;
	}

	void SetPlay(bool Play)
	{
		m_Play = Play;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Name, unsigned int Width,
		unsigned int Height, int IconID,
		bool WindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, unsigned int Width,
		unsigned int Height, bool WindowMode = true);
	int Run();
	void Logic();

private:
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	bool Render(float DeltaTime);

private:
	ATOM Register(const TCHAR* Name, int IconID);
	BOOL Create(const TCHAR* Name);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	template <typename T>
	T* CreateMouse(Mouse_State State, const std::string& Name)
	{
		T* Window = DBG_NEW T;

		Window->SetName(Name);

		if (!Window->Init())
		{
			SAFE_RELEASE(Window);
			return nullptr;
		}

		m_MouseWidget[(int)State] = Window;

		return Window;
	}

	DECLARE_SINGLE(CEngine)
};

