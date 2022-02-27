#include "IMGUITree.h"

CIMGUITree::CIMGUITree()	:
	m_OpenFunc(nullptr),
	m_CloseFunc(nullptr)
{
}

CIMGUITree::~CIMGUITree()
{
}

bool CIMGUITree::Init()
{
	if (!CIMGUIWidget::Init())
		return false;

	return true;
}

bool CIMGUITree::Render()
{
	if (!CIMGUIWidget::Render())
		return false;

	else if (ImGui::TreeNode(m_Name.c_str()))
	{
		if (m_OpenFunc)
			m_OpenFunc();

		ImGui::TreePop();
	}

	else
	{
		if (m_CloseFunc)
			m_CloseFunc();
	}

	return true;
}
