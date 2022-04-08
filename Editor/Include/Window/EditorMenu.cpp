
#include "EditorMenu.h"
#include "TileMapWindow.h"
#include "Public.h"
#include "PathManager.h"
#include "ObjectHierarchy.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUITextInput.h"
#include "IMGUIComboBox.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../EditorManager.h"

CEditorMenu::CEditorMenu()	:
	m_ObjectCreateButton(nullptr),
	m_ObjectDeleteButton(nullptr),
	m_ObjectCombo(nullptr),
	m_Public(nullptr)
{
}

CEditorMenu::~CEditorMenu()
{
}

bool CEditorMenu::Init()
{
	CIMGUIWindow::Init();

	m_ObjectCombo = AddWidget<CIMGUIComboBox>("Object", 150.f, 20.f);

	m_ObjectCombo->SetHideName(true);
	m_ObjectCombo->AddItem("Monster : BulletKin");
	m_ObjectCombo->AddItem("Monster : Bandana");
	m_ObjectCombo->AddItem("Monster : ShotgunKin1");
	m_ObjectCombo->AddItem("Monster : ShotgunKin2");
	m_ObjectCombo->AddItem("Player : PlayerPos");
	m_ObjectCombo->AddItem("Boss : BulletKing");

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectCreateButton = AddWidget<CIMGUIButton>("Create", 70.f, 20.f);

	m_ObjectCreateButton->SetClickCallback(this, &CEditorMenu::ObjectCreateButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectDeleteButton = AddWidget<CIMGUIButton>("Delete", 70.f, 20.f);

	m_ObjectDeleteButton->SetClickCallback(this, &CEditorMenu::ObjectDeleteButton);

	return true;
}

void CEditorMenu::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CEditorMenu::ObjectCreateButton()
{
	// 오브젝트 생성.
	int	SelectIndex = m_ObjectCombo->GetSelectIndex();

	if (SelectIndex == -1 || !CEditorManager::GetInst()->HasTileMap())
		return;

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::M_BulletKin:
		if (Hierarchy->FindObjectList("M_BulletKin"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::M_BulletKin);
		break;
	case CreateObject_Type::M_Bandana:
		if (Hierarchy->FindObjectList("M_Bandana"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::M_Bandana);
		break;
	case CreateObject_Type::M_ShotgunKin1:
		if (Hierarchy->FindObjectList("M_ShotgunKin1"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::M_ShotgunKin1);
		break;
	case CreateObject_Type::M_ShotgunKin2:
		if (Hierarchy->FindObjectList("M_ShotgunKin2"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::M_ShotgunKin2);
		break;
	case CreateObject_Type::P_PlayerPos:
		if (Hierarchy->FindObjectList("P_PlayerPos"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::P_PlayerPos);
		break;
	case CreateObject_Type::B_BulletKing:
		if (Hierarchy->FindObjectList("B_BulletKing"))
			return;
		CPublic::GetInst()->CreateObjectType(Object_Type::B_BulletKing);
		break;
	}

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::M_BulletKin:
		Hierarchy->AddObjectList("M_BulletKin");
		break;
	case CreateObject_Type::M_Bandana:
		Hierarchy->AddObjectList("M_Bandana");
		break;
	case CreateObject_Type::M_ShotgunKin1:
		Hierarchy->AddObjectList("M_ShotgunKin1");
		break;
	case CreateObject_Type::M_ShotgunKin2:
		Hierarchy->AddObjectList("M_ShotgunKin2");
		break;
	case CreateObject_Type::P_PlayerPos:
		Hierarchy->AddObjectList("P_PlayerPos");
		break;
	case CreateObject_Type::B_BulletKing:
		Hierarchy->AddObjectList("B_BulletKing");
		break;
	}
}

void CEditorMenu::ObjectDeleteButton()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	Object_Type	SelectType = Hierarchy->GetSelectObjectType();

	if (SelectType == Object_Type::Max || !CEditorManager::GetInst()->HasTileMap())
		return;

	std::string	Name;

	switch (SelectType)
	{
	case Object_Type::M_BulletKin:
		Name = "M_BulletKin";
		break;
	case Object_Type::M_Bandana:
		Name = "M_Bandana";
		break;
	case Object_Type::M_ShotgunKin1:
		Name = "M_ShotgunKin1";
		break;
	case Object_Type::M_ShotgunKin2:
		Name = "M_ShotgunKin2";
		break;
	case Object_Type::P_PlayerPos:
		Name = "P_PlayerPos";
		break;
	case Object_Type::B_BulletKing:
		Name = "B_BulletKing";
		break;
	}

	Hierarchy->DeleteObjectList(Name.c_str());

	CPublic::GetInst()->ClearObjectWorldPos(SelectType);
	CPublic::GetInst()->DeleteObjectType(SelectType);

	CEditorManager::GetInst()->GetTileMapWindow()->DeleteTile(SelectType);
}

void CEditorMenu::LoadSceneObject()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (Hierarchy)
	{
		Hierarchy->ClearObjectList();

		std::vector<std::string>	vecObjectName;

		CPublic::GetInst()->GetObjectName(vecObjectName);

		size_t Size = vecObjectName.size();

		for (size_t i = 0; i < Size; ++i)
		{
			Hierarchy->AddObjectList(vecObjectName[i].c_str());
		}
	}
}
