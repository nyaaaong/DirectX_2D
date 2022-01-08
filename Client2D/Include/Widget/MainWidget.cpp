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

    m_Button = CreateWidget<CButton>("Button");

    m_Button->SetPos(400.f, 300.f);
    m_Button->SetSize(200.f, 50.f);
    m_Button->SetTexture(Button_State::Normal, "StartButton", TEXT("Start.png"));

    m_Button->SetTextureTint(Button_State::Normal, 100, 100, 100, 255);

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
