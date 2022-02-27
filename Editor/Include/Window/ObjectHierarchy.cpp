
#include "ObjectHierarchy.h"
#include "IMGUIListBox.h"
#include "IMGUIManager.h"
#include "IMGUITree.h"
#include "IMGUISameLine.h"
#include "TileMapWindow.h"
#include "Scene/SceneManager.h"

CObjectHierarchy::CObjectHierarchy()	:
	m_ObjectListWidget(nullptr),
	m_ComponentTree(nullptr)
{
}

CObjectHierarchy::~CObjectHierarchy()
{
}

void CObjectHierarchy::AddObjectList(const char* Name)
{
	m_ObjectListWidget->AddItem(Name);
}

bool CObjectHierarchy::Init()
{
	CIMGUIWindow::Init();

	m_ObjectListWidget = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 200.f);
	m_ObjectListWidget->SetHideName(true);
	m_ObjectListWidget->SetPageItemCount(15);
	m_ObjectListWidget->SetSelectCallback(this, &CObjectHierarchy::SelectObject);

	m_ComponentTree = AddWidget<CIMGUITree>("Component");
	m_ComponentTree->Disable();
	m_ComponentTree->SetOpenCallback<CObjectHierarchy>(this, &CObjectHierarchy::ComponentTreeOpen);
	m_ComponentTree->SetCloseCallback<CObjectHierarchy>(this, &CObjectHierarchy::ComponentTreeClose);

	m_vecComponentTree.resize((size_t)SceneComponent_Type::Max);
	m_vecComponentListBox.resize((size_t)SceneComponent_Type::Max);

	char	Name[32] = {};
	std::string	ComponentName[(int)SceneComponent_Type::Max];

	ComponentName[(int)SceneComponent_Type::Sprite] = "SpriteComponent";
	ComponentName[(int)SceneComponent_Type::StaticMesh] = "StaticMeshComponent";
	ComponentName[(int)SceneComponent_Type::Box2D] = "Box2DComponent";
	ComponentName[(int)SceneComponent_Type::Circle] = "CircleComponent";
	ComponentName[(int)SceneComponent_Type::Pixel] = "PixelComponent";
	ComponentName[(int)SceneComponent_Type::Camera] = "CameraComponent";
	ComponentName[(int)SceneComponent_Type::Widget] = "WidgetComponent";
	ComponentName[(int)SceneComponent_Type::Particle] = "ParticleComponent";
	ComponentName[(int)SceneComponent_Type::TileMap] = "TileMapComponent";

	for (int i = 0; i < (int)SceneComponent_Type::Max; ++i)
	{
		CIMGUITree* NewTree = AddWidget<CIMGUITree>(ComponentName[i]);
		NewTree->SetOpenCallback<CObjectHierarchy>(this, &CObjectHierarchy::ComponentListBoxTreeOpen);
		NewTree->SetCloseCallback<CObjectHierarchy>(this, &CObjectHierarchy::ComponentListBoxTreeClose);
		NewTree->Disable();

		m_vecComponentTree[i] = NewTree;

		memset(Name, 0, sizeof(char) * 20);

		sprintf_s(Name, "Component ListBox Index : %d", i);

		CIMGUIListBox* NewListBox = AddWidget<CIMGUIListBox>(Name);
		NewListBox->Disable();
		NewListBox->SetHideName(true);
		NewListBox->SetPageItemCount(3);
		NewListBox->SetSelectCallback(this, &CObjectHierarchy::SelectComponent);

		m_vecComponentListBox[i] = NewListBox;
	}

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
		return;

	m_SelectObject = Object;

	m_ComponentTree->Enable();
}

void CObjectHierarchy::SelectComponent(int Index, const char* Item)
{
	if (!m_SelectObject)
		return;

	// 선택된 컴포넌트를 저장해둔다.
	m_SelectComponent = (CSceneComponent*)m_SelectObject->FindComponent(Item);

	CTileMapWindow* TileMapWindow = (CTileMapWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapWindow");

	if (TileMapWindow)
	{
		if (m_SelectComponent->CheckTypeID<CTileMapComponent>())
			TileMapWindow->SetTileMap((CTileMapComponent*)m_SelectComponent.Get());

		else
			TileMapWindow->SetTileMap(nullptr);
	}
}

void CObjectHierarchy::ComponentTreeOpen()
{
	size_t Size = m_vecComponentTree.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecComponentTree[i]->Disable();
	}

	int Flag = m_SelectObject->GetAllComponentFlag();

	if (Flag & (int)Component_Flag::Sprite)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Sprite]->Enable();
		Flag &= ~(int)Component_Flag::Sprite;
	}

	if (Flag & (int)Component_Flag::StaticMesh)
	{
		m_vecComponentTree[(int)SceneComponent_Type::StaticMesh]->Enable();
		Flag &= ~(int)Component_Flag::StaticMesh;
	}

	if (Flag & (int)Component_Flag::Box2D)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Box2D]->Enable();
		Flag &= ~(int)Component_Flag::Box2D;
	}

	if (Flag & (int)Component_Flag::Circle)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Circle]->Enable();
		Flag &= ~(int)Component_Flag::Circle;
	}

	if (Flag & (int)Component_Flag::Pixel)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Pixel]->Enable();
		Flag &= ~(int)Component_Flag::Pixel;
	}

	if (Flag & (int)Component_Flag::Camera)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Camera]->Enable();
		Flag &= ~(int)Component_Flag::Camera;
	}

	if (Flag & (int)Component_Flag::Widget)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Widget]->Enable();
		Flag &= ~(int)Component_Flag::Widget;
	}

	if (Flag & (int)Component_Flag::Particle)
	{
		m_vecComponentTree[(int)SceneComponent_Type::Particle]->Enable();
		Flag &= ~(int)Component_Flag::Particle;
	}

	if (Flag & (int)Component_Flag::TileMap)
	{
		m_vecComponentTree[(int)SceneComponent_Type::TileMap]->Enable();
		Flag &= ~(int)Component_Flag::TileMap;
	}
}

void CObjectHierarchy::ComponentTreeClose()
{
	int Size = (int)SceneComponent_Type::Max;

	for (int i = 0; i < Size; ++i)
	{
		m_vecComponentTree[i]->Disable();
		m_vecComponentListBox[i]->Disable();
	}
}

void CObjectHierarchy::ComponentListBoxTreeOpen()
{
	int Flag = m_SelectObject->GetAllComponentFlag();

	if (Flag & (int)Component_Flag::Sprite)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Sprite]->Enable();
		Flag &= ~(int)Component_Flag::Sprite;
	}

	if (Flag & (int)Component_Flag::StaticMesh)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::StaticMesh]->Enable();
		Flag &= ~(int)Component_Flag::StaticMesh;
	}

	if (Flag & (int)Component_Flag::Box2D)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Box2D]->Enable();
		Flag &= ~(int)Component_Flag::Box2D;
	}

	if (Flag & (int)Component_Flag::Circle)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Circle]->Enable();
		Flag &= ~(int)Component_Flag::Circle;
	}

	if (Flag & (int)Component_Flag::Pixel)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Pixel]->Enable();
		Flag &= ~(int)Component_Flag::Pixel;
	}

	if (Flag & (int)Component_Flag::Camera)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Camera]->Enable();
		Flag &= ~(int)Component_Flag::Camera;
	}

	if (Flag & (int)Component_Flag::Widget)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Widget]->Enable();
		Flag &= ~(int)Component_Flag::Widget;
	}

	if (Flag & (int)Component_Flag::Particle)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::Particle]->Enable();
		Flag &= ~(int)Component_Flag::Particle;
	}

	if (Flag & (int)Component_Flag::TileMap)
	{
		m_vecComponentListBox[(int)SceneComponent_Type::TileMap]->Enable();
		Flag &= ~(int)Component_Flag::TileMap;
	}

	std::vector<FindComponentName>	vecNames;

	m_SelectObject->GetAllSceneComponentsName(vecNames);

	size_t	Size = vecNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		switch (vecNames[i].ComponentFlag)
		{
		case Component_Flag::Sprite:
			m_vecComponentListBox[(int)SceneComponent_Type::Sprite]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Sprite]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::StaticMesh:
			m_vecComponentListBox[(int)SceneComponent_Type::StaticMesh]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::StaticMesh]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Box2D:
			m_vecComponentListBox[(int)SceneComponent_Type::Box2D]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Box2D]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Circle:
			m_vecComponentListBox[(int)SceneComponent_Type::Circle]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Circle]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Pixel:
			m_vecComponentListBox[(int)SceneComponent_Type::Pixel]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Pixel]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Camera:
			m_vecComponentListBox[(int)SceneComponent_Type::Camera]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Camera]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Widget:
			m_vecComponentListBox[(int)SceneComponent_Type::Widget]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Widget]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::Particle:
			m_vecComponentListBox[(int)SceneComponent_Type::Particle]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::Particle]->AddItem(vecNames[i].Name);
			break;
		case Component_Flag::TileMap:
			m_vecComponentListBox[(int)SceneComponent_Type::TileMap]->Clear();
			m_vecComponentListBox[(int)SceneComponent_Type::TileMap]->AddItem(vecNames[i].Name);
			break;
		}
	}
}

void CObjectHierarchy::ComponentListBoxTreeClose()
{
	int Size = (int)SceneComponent_Type::Max;

	for (int i = 0; i < Size; ++i)
	{
		m_vecComponentListBox[i]->Disable();
	}
}
