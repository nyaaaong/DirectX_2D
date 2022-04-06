
#include "PlayerWidget.h"

CPlayerWidget::CPlayerWidget()
{
}

CPlayerWidget::CPlayerWidget(const CPlayerWidget& window)	:
	CWidgetWindow(window)
{
	m_HPBar = FindWidget<CProgressBar>("HPBar");
}

CPlayerWidget::~CPlayerWidget()
{
}

void CPlayerWidget::Start()
{
	CWidgetWindow::Start();
}

bool CPlayerWidget::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetSize(100.f, 5.f);
	m_HPBar->SetTextureTint(255, 0, 0, 255);

	Vector2	RenderPos = m_HPBar->GetRenderPos();
	m_HPBar->SetPos(RenderPos.x, RenderPos.y - 10.f);

	return true;
}

void CPlayerWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerWidget::Render()
{
	CWidgetWindow::Render();
}

CPlayerWidget* CPlayerWidget::Clone()
{
	return DBG_NEW CPlayerWidget(*this);
}

void CPlayerWidget::AddHPPercent(float Percent)
{
	m_HPBar->AddPercent(Percent);
}

void CPlayerWidget::SetHPPercent(float Percent)
{
	m_HPBar->SetPercent(Percent);
}

void CPlayerWidget::SetHPDir(ProgressBar_Dir Dir)
{
	m_HPBar->SetDir(Dir);
}
