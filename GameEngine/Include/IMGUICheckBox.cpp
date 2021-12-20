#include "IMGUICheckBox.h"

CIMGUICheckBox::CIMGUICheckBox()	:
	m_Check(nullptr)
{
}

CIMGUICheckBox::~CIMGUICheckBox()
{
}

void CIMGUICheckBox::CheckBox(bool* Check)
{
	m_Check = Check;
}

bool CIMGUICheckBox::Init()
{
	if (!CIMGUIWidget::Init())
		return false;

	return true;
}

bool CIMGUICheckBox::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	ImGui::Checkbox(m_Name.c_str(), m_Check);

	return true;
}
