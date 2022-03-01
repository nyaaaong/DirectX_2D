
#include "EditorMenu.h"
#include "Engine.h"
#include "PathManager.h"
#include "ObjectHierarchy.h"
#include "SpriteWindow.h"
#include "TileMapWindow.h"
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
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "Component/ParticleComponent.h"
#include "Component/TileMapComponent.h"
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
	m_ComponentCombo->AddItem("Box2DComponent");
	m_ComponentCombo->AddItem("CircleComponent");
	m_ComponentCombo->AddItem("PixelComponent");
	m_ComponentCombo->AddItem("CameraComponent");
	m_ComponentCombo->AddItem("WidgetComponent");
	m_ComponentCombo->AddItem("ParticleComponent");
	m_ComponentCombo->AddItem("TileMapComponent");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentNameInput = AddWidget<CIMGUITextInput>("ComponentName", 200.f, 20.f);
	m_ComponentNameInput->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentCreateButton = AddWidget<CIMGUIButton>("CreateComponent", 200.f, 20.f);

	m_ComponentCreateButton->SetClickCallback(this, &CEditorMenu::ComponentCreateButton);

	CIMGUIButton* SaveSceneButton = AddWidget<CIMGUIButton>("SaveScene", 100.f, 20.f);

	SaveSceneButton->SetClickCallback(this, &CEditorMenu::SaveScene);

	CIMGUIButton* LoadSceneButton = AddWidget<CIMGUIButton>("LoadScene", 100.f, 20.f);

	LoadSceneButton->SetClickCallback(this, &CEditorMenu::LoadScene);

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
		Hierarchy->AddObjectList(m_ObjectNameInput->GetTextMultibyte());
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

	CSceneComponent* Root = Obj->GetRootComponent();

	const char*	Text = m_ComponentNameInput->GetTextMultibyte();

	switch ((SceneComponent_Type)SelectIndex)
	{
	case SceneComponent_Type::Sprite:
	{
		CSpriteComponent* Component = Obj->CreateComponent<CSpriteComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Sprite);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::StaticMesh:
	{
		CStaticMeshComponent* Component = Obj->CreateComponent<CStaticMeshComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::StaticMesh);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Box2D:
	{
		CColliderBox2D* Component = Obj->CreateComponent<CColliderBox2D>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Box2D);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Circle:
	{
		CColliderCircle* Component = Obj->CreateComponent<CColliderCircle>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Circle);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Pixel:
	{
		CColliderPixel* Component = Obj->CreateComponent<CColliderPixel>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Pixel);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Camera:
	{
		CCameraComponent* Component = Obj->CreateComponent<CCameraComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Camera);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Widget:
	{
		CWidgetComponent* Component = Obj->CreateComponent<CWidgetComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Widget);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::Particle:
	{
		CParticleComponent* Component = Obj->CreateComponent<CParticleComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::Particle);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}
	}
		break;
	case SceneComponent_Type::TileMap:
	{
		CTileMapComponent* Component = Obj->CreateComponent<CTileMapComponent>(Text);

		if (Root)
			Root->AddChild(Component);

		if (Hierarchy)
		{
			CIMGUIListBox* ComponentList = Hierarchy->GetComponentList((int)SceneComponent_Type::TileMap);

			ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
		}

		CMaterial* Material = CSceneManager::GetInst()->GetScene()->GetResource()->FindMaterial("TileMap");

		Component->SetTileMaterial(Material);

		CEditorManager::GetInst()->SetEditMode(EditMode::TileMap);
	}
	break;
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
		// .scn이 붙었는지 확인
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

		if (!Find) // scn 확장자가 붙지 않았을 경우 붙여준다.
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
		// .scn이 붙었는지 확인
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

		if (!Find) // scn 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(FilePath, TEXT(".scn"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CSceneManager::GetInst()->GetScene()->LoadFullPath(ConvertFullPath);

		LoadSceneObject();
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
		std::vector<std::string>	vecObjectName;

		CSceneManager::GetInst()->GetScene()->GetObjectName(vecObjectName);

		size_t Size = vecObjectName.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (vecObjectName[i] == "SpriteEditObject" || vecObjectName[i] == "TileMapInfo")
				continue;

			Hierarchy->AddObjectList(vecObjectName[i].c_str());
		}
	}
}
