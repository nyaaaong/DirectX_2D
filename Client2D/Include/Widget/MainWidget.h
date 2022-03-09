#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Button.h"
#include "Widget/Text.h"
#include "Widget/SliderBar.h"
#include "Widget/Slider.h"
#include "Widget/Image.h"
#include "Widget/Number.h"

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
	CSharedPtr<CText>	m_MouseXText;
	CSharedPtr<CText>	m_MouseYText;
	CSharedPtr<CText>	m_WorldMouseXText;
	CSharedPtr<CText>	m_WorldMouseYText;
	CSharedPtr<CText>	m_MouseDirXText;
	CSharedPtr<CText>	m_MouseDirYText;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMainWidget* Clone();
};

