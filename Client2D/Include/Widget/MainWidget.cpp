#include "MainWidget.h"

CMainWidget::CMainWidget()
{
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

void CMainWidget::StartButtonClick()
{
	//MessageBox(0, TEXT("Click"), TEXT("Click"), MB_OK);
}
