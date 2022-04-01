
#include "ObjectHierarchy.h"
#include "Public.h"
#include "IMGUIListBox.h"
#include "IMGUIManager.h"
#include "IMGUISameLine.h"
#include "TileMapWindow.h"
#include "Scene/SceneManager.h"

CObjectHierarchy::CObjectHierarchy()	:
	m_ObjectListWidget(nullptr),
	m_SelectObjectType(Object_Type::Max)
{
}

CObjectHierarchy::~CObjectHierarchy()
{
}

void CObjectHierarchy::AddObjectList(const char* Name)
{
	m_ObjectListWidget->AddItem(Name);
}

void CObjectHierarchy::DeleteObjectList(const char* Name)
{
	m_ObjectListWidget->DeleteItem(Name);

	m_SelectObjectType = Object_Type::Max;

	SelectCancleObjectList();
}

void CObjectHierarchy::ClearObjectList()
{
	m_ObjectListWidget->Clear();

	m_SelectObjectType = Object_Type::Max;

	SelectCancleObjectList();
}

void CObjectHierarchy::SelectCancleObjectList()
{
	m_ObjectListWidget->SetSelectCancel(true);
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
	Object_Type	Type = CPublic::GetInst()->GetMultibyteToType(Item);

	if (CPublic::GetInst()->FindObjectType(Type))
		m_SelectObjectType = Type;
}