#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Text.h"

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
	/*CSharedPtr<CText>	m_MouseXText;
	CSharedPtr<CText>	m_MouseYText;
	CSharedPtr<CText>	m_WorldMouseXText;
	CSharedPtr<CText>	m_WorldMouseYText;
	CSharedPtr<CText>	m_MouseDirXText;
	CSharedPtr<CText>	m_MouseDirYText;
	CSharedPtr<CText>	m_MouseAngleText;*/
	CSharedPtr<CText>	m_DebugText;
	char	m_Text[256];

public:
	void SetDebugText(const char* Text)
	{
		strcpy_s(m_Text, Text);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMainWidget* Clone();
};

