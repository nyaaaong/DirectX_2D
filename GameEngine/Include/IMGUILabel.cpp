#include "IMGUILabel.h"

CIMGUILabel::CIMGUILabel()
{
    m_Align = ImVec2(0.f, 0.f);
}

CIMGUILabel::~CIMGUILabel()
{
}

bool CIMGUILabel::Init()
{
    return true;
}

bool CIMGUILabel::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, m_Align);

    ImGui::PushStyleColor(ImGuiCol_Button, m_Color.Value);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_Color.Value);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_Color.Value);

    ImGui::Button(m_Name.c_str(), m_Size);

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();

	return true;
}
