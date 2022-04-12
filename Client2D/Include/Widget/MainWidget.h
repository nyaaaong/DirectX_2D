#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Text.h"
#include "Widget/Image.h"

class CMainWidget :
    public CWidgetWindow
{
	friend class CViewport;

protected:
	CMainWidget();
	CMainWidget(const CMainWidget& window);
	virtual ~CMainWidget();

private:
	CSharedPtr<CText>	m_FPSText;
	CSharedPtr<CText>	m_DebugText;
	CSharedPtr<CImage>	m_Fade;
	char	m_Text[256];
	float	m_FadeAlpha;
	float	m_FadeSpeed;
	bool	m_FadeIn;
	bool	m_FadeOut;

public:
	bool IsFadeIn()	const
	{
		return m_FadeIn;
	}

	bool IsFadeOut()	const
	{
		return m_FadeOut;
	}

public:
	void FadeOut()
	{
		m_FadeAlpha = 0.f;

		m_FadeOut = true;
	}

	void FadeIn()
	{
		m_FadeAlpha = 1.f;

		m_FadeIn = true;
	}

	void SetDebugText(const char* Text)
	{
		strcpy_s(m_Text, Text);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMainWidget* Clone();
};

