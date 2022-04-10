#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Text.h"
#include "Widget/Image.h"
#include "Widget/ProgressBar.h"

class CBossWidget :
	public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;

protected:
	CBossWidget();
	CBossWidget(const CBossWidget& window);
	virtual ~CBossWidget();

private:
	CSharedPtr<CText>			m_FPSText;
	CSharedPtr<CText>			m_DebugText;
	CSharedPtr<CImage>			m_HPBarBack;
	CSharedPtr<CProgressBar>	m_HPBar;
	float	m_Percent;
	char	m_Text[256];

public:
	void SetPercent(float Percent)
	{
		m_Percent = Percent;
	}

	void AddPercent(float Percent)
	{
		m_Percent += Percent;

		if (m_Percent < 0.f)
			m_Percent = 0.f;

		else if (m_Percent > 1.f)
			m_Percent = 1.f;
	}

	void SetText(const char* Text)
	{
		strcpy_s(m_Text, Text);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBossWidget* Clone();
};