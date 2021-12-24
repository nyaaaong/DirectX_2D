
#include "EditorMenu.h"
#include "Engine.h"
#include "PathManager.h"
#include "ObjectHierarchy.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "../EditorManager.h"
#include "../Object/Player2D.h"
#include "../Object/SpriteEditObject.h"
#include "../Object/DragObject.h"

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

	CIMGUIButton* SaveSceneButton = AddWidget<CIMGUIButton>("SaveSceneButton", 100.f, 30.f);

	SaveSceneButton->SetClickCallback(this, &CEditorMenu::SaveScene);

	CIMGUIButton* LoadSceneButton = AddWidget<CIMGUIButton>("LoadSceneButton", 100.f, 30.f);

	LoadSceneButton->SetClickCallback(this, &CEditorMenu::LoadScene);

	CIMGUIButton* PlayButton = AddWidget<CIMGUIButton>("Play", 50.f, 50.f);

	PlayButton->SetClickCallback(this, &CEditorMenu::GamePlay);

	return true;
}

void CEditorMenu::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CEditorMenu::ObjectCreateButton()
{
	// ������Ʈ ����.
	int	SelectIndex = m_ObjectCombo->GetSelectIndex();
	if (SelectIndex == -1)
		return;

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::GameObject:
		CSceneManager::GetInst()->GetScene()->CreateGameObject<CGameObject>(m_ObjectNameInput->GetTextMultibyte());
		break;
	case CreateObject_Type::Player:
		CSceneManager::GetInst()->GetScene()->CreateGameObject<CPlayer2D>(m_ObjectNameInput->GetTextMultibyte());
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

	// ������Ʈ ����.
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

void CEditorMenu::SaveScene()
{
	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Scene (*.scn)\0*.scn");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		// .scn�� �پ����� Ȯ��
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	scn[5] = TEXT("ncs.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != scn[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // scn Ȯ���ڰ� ���� �ʾ��� ��� �ٿ��ش�.
			lstrcat(FilePath, TEXT(".scn"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CSceneManager::GetInst()->GetScene()->SaveFullPath(ConvertFullPath);
	}
}

void CEditorMenu::LoadScene()
{
	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Scene (*.scn)\0*.scn");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// .scn�� �پ����� Ȯ��
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	scn[5] = TEXT("ncs.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != scn[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // scn Ȯ���ڰ� ���� �ʾ��� ��� �ٿ��ش�.
			lstrcat(FilePath, TEXT(".scn"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CSceneManager::GetInst()->GetScene()->LoadFullPath(ConvertFullPath);
	}
}

void CEditorMenu::GamePlay()
{
	if (!CEngine::GetInst()->IsPlay())
		CEngine::GetInst()->SetPlay(true);

	else
		CEngine::GetInst()->SetPlay(false);
}
