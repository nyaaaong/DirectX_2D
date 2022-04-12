
#include "BossWidget.h"
#include "Engine.h"

CBossWidget::CBossWidget()	:
	m_Text{}
{
}

CBossWidget::CBossWidget(const CBossWidget& window) :
	CWidgetWindow(window)
{
	m_HPBarBack = FindWidget<CImage>("HPBarBack");
	m_HPBar = FindWidget<CProgressBar>("HPBar");

	memset(m_Text, 0, sizeof(char) * 256);
}

CBossWidget::~CBossWidget()
{
}

bool CBossWidget::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(1280.f, 720.f);

	m_HPBarBack = CreateWidget<CImage>("HPBarBack");
	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	
	m_HPBarBack->SetTexture("HPBarBack", TEXT("UI/HPBarBack.png"));
	m_HPBarBack->SetSize(534.f, 37.f);
	m_HPBarBack->SetZOrder(1);

	m_HPBar->SetPos(48.f, 10.f);
	m_HPBar->SetSize(438.f, 16.f);
	m_HPBar->SetTextureTint(255, 51, 0, 255);
	m_HPBar->SetDir(ProgressBar_Dir::RightToLeft);

	return true;
}

void CBossWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

CBossWidget* CBossWidget::Clone()
{
	return DBG_NEW CBossWidget(*this);
}

void CBossWidget::Enable(bool Enable)
{
	CWidgetWindow::Enable(Enable);

	m_HPBarBack->Enable(Enable);
	m_HPBar->Enable(Enable);
}
