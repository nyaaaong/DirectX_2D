
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
	m_ObjectNameInput(nullptr),
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

	m_ObjectCombo = AddWidget<CIMGUIComboBox>("Object", 200.f, 20.f);

	m_ObjectCombo->SetHideName(true);
	m_ObjectCombo->AddItem("Monster : BulletKin");

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectNameInput = AddWidget<CIMGUITextInput>("ObjectName", 200.f, 20.f);
	m_ObjectNameInput->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectCreateButton = AddWidget<CIMGUIButton>("CreateObject", 200.f, 20.f);

	m_ObjectCreateButton->SetClickCallback(this, &CEditorMenu::ObjectCreateButton);

	CIMGUIButton* SaveObjectButton = AddWidget<CIMGUIButton>("SaveObject", 100.f, 20.f);

	SaveObjectButton->SetClickCallback(this, &CEditorMenu::SaveObject);

	CIMGUIButton* LoadObjectButton = AddWidget<CIMGUIButton>("LoadObject", 100.f, 20.f);

	LoadObjectButton->SetClickCallback(this, &CEditorMenu::LoadObject);

	CIMGUIButton* PlayButton = AddWidget<CIMGUIButton>("Play", 50.f, 20.f);

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
		CPublic::GetInst()->CreateObjectInfo(m_ObjectNameInput->GetTextMultibyte(), Object_Type::BulletKin);
		break;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (Hierarchy)
		Hierarchy->AddObjectList(m_ObjectNameInput->GetTextMultibyte());
}

void CEditorMenu::SaveObject()
{
	if (!CPublic::GetInst()->GetObjectInfoSize())
		return;

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Object (*.obj)\0*.obj");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		// .obj이 붙었는지 확인
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	obj[5] = TEXT("jbo.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != obj[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // obj 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(FilePath, TEXT(".obj"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CPublic::GetInst()->SaveFullPath(ConvertFullPath);
	}
}

void CEditorMenu::LoadObject()
{
	if (!CEditorManager::GetInst()->HasTileMap())
		return;

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Object (*.obj)\0*.obj");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// .obj이 붙었는지 확인
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	obj[5] = TEXT("jbo.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != obj[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // obj 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(FilePath, TEXT(".obj"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CPublic::GetInst()->LoadFullPath(ConvertFullPath);

		LoadSceneObject();

		CEditorManager::GetInst()->SetEditMode(EditMode::TileMap);
	}
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
