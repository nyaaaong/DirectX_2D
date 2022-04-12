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
	CSharedPtr<CImage>			m_HPBarBack;
	CSharedPtr<CProgressBar>	m_HPBar;
	char	m_Text[256];

public:
	void SetPercent(float Percent)
	{
		m_HPBar->SetPercent(Percent);
	}

	void AddPercent(float Percent)
	{
		m_HPBar->AddPercent(Percent);
	}

	void SetText(const char* Text)
	{
		strcpy_s(m_Text, Text);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBossWidget* Clone();
	virtual void Enable(bool Enable);
};