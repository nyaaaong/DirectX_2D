#include "IMGUIWindow.h"
#include "IMGUIWidget.h"
#include "IMGUIManager.h"

CIMGUIWindow::CIMGUIWindow()	:
	m_Open(true), 
	m_ModalPopup(false),
	m_Start(false),
	m_WindowFlag(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking)
{
}

CIMGUIWindow::~CIMGUIWindow()
{
	size_t	Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();

	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecWidget[i]);
	}

	m_vecWidget.clear();
}

void CIMGUIWindow::Open()
{
	m_Open = true;
}

void CIMGUIWindow::Close()
{
	m_Open = false;
}

void CIMGUIWindow::ClosePopup()
{
	ImGui::CloseCurrentPopup();

	size_t	Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();
}

CIMGUIWidget* CIMGUIWindow::FindWidget(const std::string& Name)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecWidget[i]->m_Name == Name)
			return m_vecWidget[i];
	}

	return nullptr;
}

void CIMGUIWindow::PushTreeInWidget(std::vector<class CIMGUIWidget*>& vecTreeStorage, CIMGUIWidget* target)
{
	vecTreeStorage.push_back(target);
}

bool CIMGUIWindow::Init()
{
	return true;
}

bool CIMGUIWindow::Start()
{
	return true;
}

void CIMGUIWindow::Update(float DeltaTime)
{
	if (!m_Open)
		return;

	if (!ImGui::Begin(m_Name.c_str(), &m_Open, m_WindowFlag))
		m_Open = false;

	CIMGUIManager::GetInst()->SetCurrentFont();

	size_t	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Render();
	}

	CIMGUIManager::GetInst()->ResetCurrentFont();

	ImGui::End();
}
