#include "IMGUIWidget.h"

CIMGUIWidget::CIMGUIWidget() :
    m_Owner(nullptr),
    m_Font(nullptr),
    m_Color{ 1.f, 1.f, 1.f, 1.f },
    m_Size{ 100.f, 100.f },
	m_Enable(true),
	m_MouseCheck(false),
	m_IsHovered(false),
	m_IsClicked(false)
{
}

CIMGUIWidget::~CIMGUIWidget()
{
}


bool CIMGUIWidget::Init()
{
    return true;
}

bool CIMGUIWidget::Render()
{
	return m_Enable;
}

void CIMGUIWidget::CheckItemHovered()
{
	if (m_MouseCheck)
		m_IsHovered = ImGui::IsItemHovered();
}

void CIMGUIWidget::CheckItemClicked()
{
	if (m_MouseCheck)
		m_IsClicked = ImGui::IsItemClicked();
}
