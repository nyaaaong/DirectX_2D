
#include "EditorMenu.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "Engine.h"
#include "PathManager.h"
#include "../EditorManager.h"
#include "../Object/SpriteEditObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "ObjectHierarchy.h"
#include "../EditorManager.h"
#include "IMGUIManager.h"

CEditorMenu::CEditorMenu()	:
	m_ObjectCreateButton(nullptr),
	m_ObjectNameInput(nullptr),
	m_ObjectCombo(nullptr),
	m_ComponentCreateButton(nullptr),
	m_ComponentNameInput(nullptr),
	m_ComponentCombo(nullptr)
{
}

CEditorMenu::~CEditorMenu()
{
}

bool CEditorMenu::Init()
{
	CIMGUIWindow::Init();

	m_ObjectCombo = AddWidget<CIMGUIComboBox>("Object", 200.f, 20.f);

	m_ObjectCombo->SetHideName(true);
	m_ObjectCombo->AddItem("GameObject");
	m_ObjectCombo->AddItem("Player");

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectNameInput = AddWidget<CIMGUITextInput>("ObjectName", 200.f, 20.f);
	m_ObjectNameInput->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectCreateButton = AddWidget<CIMGUIButton>("CreateObject", 200.f, 20.f);

	m_ObjectCreateButton->SetClickCallback(this, &CEditorMenu::ObjectCreateButton);


	// Component
	m_ComponentCombo = AddWidget<CIMGUIComboBox>("Component", 200.f, 20.f);

	m_ComponentCombo->SetHideName(true);
	m_ComponentCombo->AddItem("SpriteComponent");
	m_ComponentCombo->AddItem("StaticMeshComponent");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentNameInput = AddWidget<CIMGUITextInput>("ComponentName", 200.f, 20.f);
	m_ComponentNameInput->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentCreateButton = AddWidget<CIMGUIButton>("CreateComponent", 200.f, 20.f);

	m_ComponentCreateButton->SetClickCallback(this, &CEditorMenu::ComponentCreateButton);

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
	if (SelectIndex == -1)
		return;

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::GameObject:
		CSceneManager::GetInst()->GetScene()->CreateGameObject<CGameObject>(m_ObjectNameInput->GetTextMultibyte());
		break;
	case CreateObject_Type::Player:
		break;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (Hierarchy)
	{
		Hierarchy->AddObjectList(m_ObjectNameInput->GetTextMultibyte());
	}
}

void CEditorMenu::ComponentCreateButton()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	CGameObject* Obj = nullptr;

	if (Hierarchy)
	{
		CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

		if (ObjList->GetSelectIndex() == -1)
			return;

		Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());
	}

	if (!Obj)
		return;

	// 오브젝트 생성.
	int	SelectIndex = m_ComponentCombo->GetSelectIndex();
	if (SelectIndex == -1)
		return;

	switch ((SceneComponent_Type)SelectIndex)
	{
	case SceneComponent_Type::Sprite:
		Obj->CreateComponent<CSpriteComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::StaticMesh:
		Obj->CreateComponent<CStaticMeshComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	}

	if (Hierarchy)
	{
		CIMGUIListBox* ComponentList = Hierarchy->GetComponentList();

		ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
	}
}
