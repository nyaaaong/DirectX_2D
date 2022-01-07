
#include "Widget.h"

CWidget::CWidget()	:
	m_Owner(nullptr),
	m_ZOrder(0)
{
}

CWidget::CWidget(const CWidget& widget)
{
}

CWidget::~CWidget()
{
}

void CWidget::Start()
{
}

bool CWidget::Init()
{
	return true;
}

void CWidget::Update(float DeltaTime)
{
}

void CWidget::PostUpdate(float DeltaTime)
{
}

void CWidget::Render()
{
}
