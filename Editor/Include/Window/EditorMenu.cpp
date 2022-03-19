
#include "EditorMenu.h"
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

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectCreateButton = AddWidget<CIMGUIButton>("CreateObject", 90.f, 20.f);

	m_ObjectCreateButton->SetClickCallback(this, &CEditorMenu::ObjectCreateButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	CIMGUIButton* PlayButton = AddWidget<CIMGUIButton>("Play", 40.f, 20.f);

	PlayButton->SetClickCallback(this, &CEditorMenu::GamePlay);

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

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::BulletKin:
		CPublic::GetInst()->CreateObjectType(Object_Type::BulletKin);
		break;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (Hierarchy)
		Hierarchy->AddObjectList("BulletKin");
}

void CEditorMenu::GamePlay()
{
	if (!CEngine::GetInst()->IsPlay())
		CEngine::GetInst()->SetPlay(true);

	else
		CEngine::GetInst()->SetPlay(false);
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
