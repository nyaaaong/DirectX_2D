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
	CSharedPtr<CButton>	m_Button;

	CSharedPtr<CButton>	m_Button1;
	CSharedPtr<CText>	m_Button1Text;
	CSharedPtr<CNumber>	m_Hour;
	CSharedPtr<CNumber>	m_Minute;
	CSharedPtr<CNumber>	m_Second;

	CSharedPtr<CSliderBar>	m_SliderBar;
	CSharedPtr<CSlider>		m_Slider;

	CSharedPtr<CImage>		m_Image;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMainWidget* Clone();

public:
	void StartButtonClick();
	void Button1Click();

private:
	void SetScale(float val);
};

