
#include "ObjectHierarchy.h"
#include "Public.h"
#include "IMGUIListBox.h"
#include "IMGUIManager.h"
#include "IMGUISameLine.h"
#include "TileMapWindow.h"
#include "Scene/SceneManager.h"

CObjectHierarchy::CObjectHierarchy()	:
	m_ObjectListWidget(nullptr),
	m_SelectObjectInfo(nullptr)
{
}

CObjectHierarchy::~CObjectHierarchy()
{
}

void CObjectHierarchy::AddObjectList(const char* Name)
{
	m_ObjectListWidget->AddItem(Name);
}

void CObjectHierarchy::ClearObjectList()
{
	m_ObjectListWidget->Clear();
}

bool CObjectHierarchy::Init()
{
	CIMGUIWindow::Init();

	m_ObjectListWidget = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 200.f);
	m_ObjectListWidget->SetHideName(true);
	m_ObjectListWidget->SetPageItemCount(15);
	m_ObjectListWidget->SetSelectCallback(this, &CObjectHierarchy::SelectObject);

	return true;
}

void CObjectHierarchy::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CObjectHierarchy::SelectObject(int Index, const char* Item)
{
	CGameObject* Object = CSceneManager::GetInst()->GetScene()->FindObject(Item);

	if (!Object)
	{
		// ���� ���� ��ϵ� ������Ʈ�� ��ã�Ҵٸ� Ÿ�ϸ��� �ƴ� ������Ʈ ������ �� �� �ִ�
		Object_Info*	Data = CPublic::GetInst()->FindObjectInfo(Item);

		m_SelectObjectInfo = Data;
		m_SelectObject = nullptr;

		if (!m_SelectObjectInfo)
			return;
	}

	else
	{
		m_SelectObject = Object;
		m_SelectObjectInfo = nullptr;
	}
}