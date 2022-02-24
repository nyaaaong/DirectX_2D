#include "IMGUIListBox.h"

CIMGUIListBox::CIMGUIListBox()  :
	m_Select(false),
	m_SelectIndex(-1),
	m_SelectCancel(false),
	m_PageItemCount(3),
	m_Sort(false)
{
}

CIMGUIListBox::~CIMGUIListBox()
{
}

bool CIMGUIListBox::Init()
{
	if (!CIMGUIWidget::Init())
		return false;

	return true;
}

bool CIMGUIListBox::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	if (m_SelectCancel)
	{
		m_SelectCancel = false;

		m_SelectIndex = -1;
	}

	ImVec2  Size = ImVec2(m_Size.x, m_PageItemCount * ImGui::GetTextLineHeightWithSpacing());

	if (ImGui::BeginListBox(m_Name.c_str(), Size))
	{
		size_t  ItemCount = m_vecItemUTF8.size();

		for (size_t i = 0; i < ItemCount; ++i)
		{
			m_Select = m_SelectIndex == i;

			if (ImGui::Selectable(m_vecItemUTF8[i].c_str(), m_Select))
			{
				if (m_SelectIndex != i && m_SelectCallback)
					m_SelectCallback((int)i, m_vecItem[i].c_str());

				m_SelectIndex = (int)i;
			}

			//if (m_Select)
			//	ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	return true;
}
