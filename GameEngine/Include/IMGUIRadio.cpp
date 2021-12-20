#include "IMGUIRadio.h"

CIMGUIRadio::CIMGUIRadio()	:
	m_FinalValue(nullptr),
	m_ButtonValue(0)
{
}

CIMGUIRadio::~CIMGUIRadio()
{
}

void CIMGUIRadio::RadioButton(int* FinalVal, int ButtonVal)
{
	m_FinalValue = FinalVal;
	m_ButtonValue = ButtonVal;
}

bool CIMGUIRadio::Init()
{
	if (!CIMGUIWidget::Init())
		return false;

	return true;
}

bool CIMGUIRadio::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	else if (!m_FinalValue)
		return false;

	ImGui::RadioButton(m_Name.c_str(), m_FinalValue, m_ButtonValue);
	
	return true;
}
