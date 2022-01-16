#include "MainWidget.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::CMainWidget(const CMainWidget& window) :
	CWidgetWindow(window)
{
	m_Button = FindWidget<CButton>("Button");
	m_Button1 = FindWidget<CButton>("Button1");
	m_Button1Text = FindWidget<CText>("Text");
}


CMainWidget::~CMainWidget()
{
}

void CMainWidget::Start()
{
}

bool CMainWidget::Init()
{
    if (!CWidgetWindow::Init())
        return false;

	SetSize(1280.f, 720.f);

    m_Button = CreateWidget<CButton>("Button");

    m_Button->SetPos(400.f, 300.f);
    m_Button->SetSize(200.f, 50.f);
    m_Button->SetTexture(Button_State::Normal, "StartButton", TEXT("Start.png"));

    m_Button->SetTextureTint(Button_State::Normal, 100, 100, 100, 255);
	m_Button->SetTexture(Button_State::MouseOn, "StartButton", TEXT("Start.png"));
	m_Button->SetTexture(Button_State::Click, "StartButton", TEXT("Start.png"));

	m_Button->SetTextureTint(Button_State::Normal, 220, 220, 220, 255);
	m_Button->SetTextureTint(Button_State::MouseOn, 255, 255, 255, 255);
	m_Button->SetTextureTint(Button_State::Click, 150, 150, 150, 255);

	m_Button->SetClickCallback<CMainWidget>(this, &CMainWidget::StartButtonClick);

	m_Button->SetSound(Button_Sound_State::MouseOn, "UI", "ButtonMouseOn", "TeemoSmile.mp3");
	m_Button->SetSound(Button_Sound_State::Click, "UI", "ButtonClick", "TeemoStartClicck.mp3");

	m_Button1 = CreateWidget<CButton>("Button1");

	m_Button1->SetPos(50.f, 200.f);
	m_Button1->SetSize(100.f, 40.f);

	m_Button1->SetTextureTint(Button_State::Normal, 220, 220, 220, 255);
	m_Button1->SetTextureTint(Button_State::MouseOn, 255, 255, 255, 255);
	m_Button1->SetTextureTint(Button_State::Click, 150, 150, 150, 255);

	m_Button1->SetSound(Button_Sound_State::MouseOn, "UI", "ButtonMouseOn", "TeemoSmile.mp3");
	m_Button1->SetSound(Button_Sound_State::Click, "UI", "ButtonClick", "TeemoStartClicck.mp3");

	m_Button1->SetClickCallback<CMainWidget>(this, &CMainWidget::Button1Click);

	m_Button1Text = CreateWidget<CText>("Text");

	m_Button1Text->SetText(TEXT("Button1"));
	m_Button1Text->SetPos(50.f, 200.f);
	m_Button1Text->SetSize(100.f, 40.f);
	m_Button1Text->SetZOrder(1);
	m_Button1Text->SetColor(1.f, 0.f, 0.f);
	//m_Button1Text->SetOpacity(0.5f);
	m_Button1Text->SetAlignH(TEXT_ALIGN_H::Center);
	m_Button1Text->SetShadowEnable(true);
	m_Button1Text->SetShadowOffset(2.f, 2.f);

	m_SliderBar = CreateWidget<CSliderBar>("SliderBar");
	m_SliderBar->SetTexture("SliderBar", TEXT("SliderBar.png"));
	m_SliderBar->SetPos(400.f, 100.f);
	m_SliderBar->SetSize(760.f, 10.f);

	m_Slider = CreateWidget<CSlider>("Slider");
	m_Slider->SetTexture("Slider", TEXT("Slider.png"));
	m_Slider->SetSize(76.f, 28.f);
	m_Slider->SetSliderInfo<CSliderBar>(m_SliderBar);
	m_Slider->SetSliderCallback<CMainWidget>(this, &CMainWidget::SetScale);

    return true;
}

void CMainWidget::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);
}

void CMainWidget::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CMainWidget::Render()
{
    CWidgetWindow::Render();
}

CMainWidget* CMainWidget::Clone()
{
	return DBG_NEW CMainWidget(*this);
}

void CMainWidget::StartButtonClick()
{
	//MessageBox(0, TEXT("Click"), TEXT("Click"), MB_OK);
}

void CMainWidget::Button1Click()
{
}

void CMainWidget::SetScale(float val)
{

}
