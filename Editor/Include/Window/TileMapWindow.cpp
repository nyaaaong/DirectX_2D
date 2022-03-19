
#include "TileMapWindow.h"
#include "TileWindow.h"
#include "Input.h"
#include "PathManager.h"
#include "Public.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Texture/Texture.h"
#include "Component/Tile.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "../EditorManager.h"

CTileMapWindow::CTileMapWindow()	:
	m_CountX(nullptr),
	m_CountY(nullptr),
	m_SizeX(nullptr),
	m_SizeY(nullptr),
	m_FrameStartX(nullptr),
	m_FrameStartY(nullptr),
	m_FrameEndX(nullptr),
	m_FrameEndY(nullptr),
	m_TypeCombo(nullptr),
	m_TileEditCombo(nullptr),
	m_CreateTileMapButton(nullptr),
	m_DefaultFrameButton(nullptr),
	m_LoadImageButton(nullptr),
	m_SaveTileMapButton(nullptr),
	m_LoadTileMapButton(nullptr),
	m_TileMapFullPath{}
{
}

CTileMapWindow::~CTileMapWindow()
{
}

bool CTileMapWindow::Start()
{
	if (!CIMGUIWindow::Start())
		return false;

	return true;
}

bool CTileMapWindow::Init()
{
	if (!CIMGUIWindow::Init())
		return false;

	m_LoadImageButton = AddWidget<CIMGUIButton>("LoadImageButton", 324.f, 40.f);
	m_LoadImageButton->SetClickCallback(this, &CTileMapWindow::LoadImageButton);

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("TileMapInfo", 324.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(31, 81, 183);

	Label = AddWidget<CIMGUILabel>("CountX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_CountX = AddWidget<CIMGUITextInput>("CountX", 80.f, 20.f);
	m_CountX->SetHideName(true);
	m_CountX->SetTextType(ImGuiText_Type::Int);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("CountY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_CountY = AddWidget<CIMGUITextInput>("CountY", 80.f, 20.f);
	m_CountY->SetHideName(true);
	m_CountY->SetTextType(ImGuiText_Type::Int);

	Label = AddWidget<CIMGUILabel>("SizeX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_SizeX = AddWidget<CIMGUITextInput>("SizeX", 80.f, 20.f);
	m_SizeX->SetHideName(true);
	m_SizeX->SetTextType(ImGuiText_Type::Float);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("SizeY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_SizeY = AddWidget<CIMGUITextInput>("SizeY", 80.f, 20.f);
	m_SizeY->SetHideName(true);
	m_SizeY->SetTextType(ImGuiText_Type::Float);

	m_CreateTileMapButton = AddWidget<CIMGUIButton>("CreateTileMapButton", 324.f, 20.f);
	m_CreateTileMapButton->SetClickCallback(this, &CTileMapWindow::CreateTileMapButton);

	CreateTileEditControl();


	m_SaveTileMapButton = AddWidget<CIMGUIButton>("SaveTileMapButton", 160.f, 20.f);
	m_SaveTileMapButton->SetClickCallback(this, &CTileMapWindow::SaveTileMapButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_LoadTileMapButton = AddWidget<CIMGUIButton>("LoadTileMapButton", 156.f, 20.f);
	m_LoadTileMapButton->SetClickCallback(this, &CTileMapWindow::LoadTileMapButton);

	m_CountX->SetInt(100);
	m_CountY->SetInt(100);
	m_SizeX->SetFloat(54.f);
	m_SizeY->SetFloat(54.f);

	m_FrameStartX->SetFloat(0.f);
	m_FrameStartY->SetFloat(0.f);
	m_FrameEndX->SetFloat(54.f);
	m_FrameEndY->SetFloat(54.f);

	return true;
}

void CTileMapWindow::CreateTileEditControl()
{
	CIMGUILabel* Label = AddWidget<CIMGUILabel>("TileEditInfo", 324.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(31, 81, 183);

	Label = AddWidget<CIMGUILabel>("TileType", 70.f, 20.f);
	Label->SetColor(15, 15, 15);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_TypeCombo = AddWidget<CIMGUIComboBox>("Type", 80.f, 20.f);

	m_TypeCombo->SetHideName(true);
	m_TypeCombo->AddItem("Normal");
	m_TypeCombo->AddItem("Wall");
	m_TypeCombo->AddItem("Object Monster");

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("TileEdit", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TileEditCombo = AddWidget<CIMGUIComboBox>("Edit", 80.f, 20.f);

	m_TileEditCombo->SetHideName(true);
	m_TileEditCombo->AddItem("Type");
	m_TileEditCombo->AddItem("Frame");

	Label = AddWidget<CIMGUILabel>("IMGStartX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_FrameStartX = AddWidget<CIMGUITextInput>("IMGStartX", 80.f, 20.f);
	m_FrameStartX->SetHideName(true);
	m_FrameStartX->SetTextType(ImGuiText_Type::Float);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("IMGStartY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_FrameStartY = AddWidget<CIMGUITextInput>("IMGStartY", 80.f, 20.f);
	m_FrameStartY->SetHideName(true);
	m_FrameStartY->SetTextType(ImGuiText_Type::Float);

	Label = AddWidget<CIMGUILabel>("IMGEndX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_FrameEndX = AddWidget<CIMGUITextInput>("IMGEndX", 80.f, 20.f);
	m_FrameEndX->SetHideName(true);
	m_FrameEndX->SetTextType(ImGuiText_Type::Float);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("IMGEndY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_FrameEndY = AddWidget<CIMGUITextInput>("IMGEndY", 80.f, 20.f);
	m_FrameEndY->SetHideName(true);
	m_FrameEndY->SetTextType(ImGuiText_Type::Float);

	m_DefaultFrameButton = AddWidget<CIMGUIButton>("DefaultFrameButton", 324.f, 20.f);

	m_DefaultFrameButton->SetClickCallback(this, &CTileMapWindow::DefaultFrameButton);
}

void CTileMapWindow::CreateTileMap()
{
	if (!m_TileMap)
	{
		CGameObject* TileMapObj = CSceneManager::GetInst()->GetScene()->CreateGameObject<CGameObject>("TileMap");

		CSceneComponent* Root = TileMapObj->GetRootComponent();

		m_TileMap = TileMapObj->CreateComponent<CTileMapComponent>("TileMap");

		if (Root)
			Root->AddChild(m_TileMap);

		CMaterial* Material = CSceneManager::GetInst()->GetScene()->GetResource()->FindMaterial("TileMap");

		m_TileMap->SetTileMaterial(Material);

		CEditorManager::GetInst()->SetEditMode(EditMode::TileMap);
		CEditorManager::GetInst()->TileMap(true);
	}
}

void CTileMapWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	// 마우스 Drag처리
	if (CEditorManager::GetInst()->GetEditMode() == EditMode::TileMap && m_TileMap)
	{
		m_TileMap->EnableEditMode(true);

		if (CEditorManager::GetInst()->GetLButtonPush())
		{
			if (CEngine::GetInst()->IsMouseWindowOut() || !CEngine::GetInst()->IsFocusClient())
				return;

			// 마우스 위치를 얻어와서 어떤 타일인지를 구한다.
			Vector2 MouseWorldPos = CInput::GetInst()->GetMouseWorld2DPos();

			CTile* Tile = m_TileMap->GetTile(Vector3(MouseWorldPos.x, MouseWorldPos.y, 0.f));

			if (Tile)
			{
				int	TileEditMode = m_TileEditCombo->GetSelectIndex();

				switch ((TileEdit_Mode)TileEditMode)
				{
				case TileEdit_Mode::Type:
				{
					int	TileType = m_TypeCombo->GetSelectIndex();

					if (TileType == -1)
						return;

					Tile_Type	Type = (Tile_Type)TileType;

					switch (Type)
					{
					case Tile_Type::Object:
					{
						if (Tile->GetTileType() == Tile_Type::Object)
							return;

						Object_Type ObjectType = CEditorManager::GetInst()->GetSelectObjectType();

						if (ObjectType == Object_Type::Max)
							return;

						Tile->SetTileType(Type);

						CPublic::GetInst()->AddObjectWorldPos(ObjectType, Tile->GetWorldPos());
						Tile->SetObjectType(ObjectType);
						break;
					}
					default:
						Tile->SetTileType(Type);
						break;
					}
				}
				break;
				case TileEdit_Mode::Frame:
				{
					float	StartX, StartY, EndX, EndY;

					StartX = m_FrameStartX->GetValueFloat();
					StartY = m_FrameStartY->GetValueFloat();
					EndX = m_FrameEndX->GetValueFloat();
					EndY = m_FrameEndY->GetValueFloat();

					Tile->SetFrameStart(StartX, StartY);
					Tile->SetFrameEnd(EndX, EndY);
				}
				break;
				}
			}
		}
	}
}

void CTileMapWindow::SetTileStart(float StartX, float StartY)
{
	m_FrameStartX->SetValueFloat(StartX);
	m_FrameStartY->SetValueFloat(StartY);

	m_FrameStartX->SetText(StartX);
	m_FrameStartY->SetText(StartY);
}

void CTileMapWindow::SetTileStart(const Vector2& Start)
{
	m_FrameStartX->SetValueFloat(Start.x);
	m_FrameStartY->SetValueFloat(Start.y);

	m_FrameStartX->SetText(Start.x);
	m_FrameStartY->SetText(Start.y);
}

void CTileMapWindow::SetTileEnd(float EndX, float EndY)
{
	m_FrameEndX->SetValueFloat(EndX);
	m_FrameEndY->SetValueFloat(EndY);

	m_FrameEndX->SetText(EndX);
	m_FrameEndY->SetText(EndY);
}

void CTileMapWindow::SetTileEnd(const Vector2& End)
{
	m_FrameEndX->SetValueFloat(End.x);
	m_FrameEndY->SetValueFloat(End.y);

	m_FrameEndX->SetText(End.x);
	m_FrameEndY->SetText(End.y);
}

void CTileMapWindow::CreateTileMapButton()
{
	if (!m_TileMap || !lstrlen(m_TileMapFullPath))
		return;

	int	CountX, CountY;

	CountX = m_CountX->GetValueInt();
	CountY = m_CountY->GetValueInt();

	Vector3	Size;
	Size.x = m_SizeX->GetValueFloat();
	Size.y = m_SizeY->GetValueFloat();

	m_TileMap->CreateTile(CountX, CountY, Size);

	CMaterial* Material = m_TileMap->GetTileMaterial();
	CTexture* Texture = nullptr;

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadTextureFullPath("DefaultTile", m_TileMapFullPath);

	Texture = CSceneManager::GetInst()->GetScene()->GetResource()->FindTexture("DefaultTile");

	if (Material->EmptyTexture())
		Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "TileTexture", Texture);

	else
		Material->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "TileTexture", Texture);
}

void CTileMapWindow::LoadImageButton()
{
	CreateTileMap();

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("그림파일 (*.dds, *.tga, *.png, *.jpg, *.jpeg, *.bmp)\0*.dds;*.tga;*.png;*.jpg;*.jpeg;*.bmp\0DDS (*.dds)\0*.dds\0TGA (*.tga)\0*.tga\0PNG (*.png)\0*.png\0JPG (*.jpg)\0*.jpg\0JPEG (*.jpeg)\0*.jpeg\0BMP (*.bmp)\0*.bmp");
	OpenFile.lpstrFile = m_TileMapFullPath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR   FileName[MAX_PATH] = {};

		_wsplitpath_s(m_TileMapFullPath, 0, 0, 0, 0, FileName, MAX_PATH, 0, 0);

		char    ConvertFileName[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FileName, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FileName, -1, ConvertFileName, Length, 0, 0);

		if (!m_TileMapSprite)
			m_TileMapSprite = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTileMapSprite>("TileMapInfo");

		m_TileMapSprite->GetSpriteComponent()->SetTextureFullPath(0, 0, (int)Buffer_Shader_Type::Pixel, ConvertFileName, m_TileMapFullPath);

		CTileWindow* TileWindow = CEditorManager::GetInst()->GetTileWindow();
		TileWindow->SetTileMapSprite(m_TileMapSprite);
		TileWindow->SetTileSize(m_SizeX->GetValueFloat(), m_SizeY->GetValueFloat());
	}
}

void CTileMapWindow::DefaultFrameButton()
{
	if (!m_TileMap || !lstrlen(m_TileMapFullPath))
		return;

	float	StartX, StartY, EndX, EndY;

	StartX = m_FrameStartX->GetValueFloat();
	StartY = m_FrameStartY->GetValueFloat();
	EndX = m_FrameEndX->GetValueFloat();
	EndY = m_FrameEndY->GetValueFloat();

	m_TileMap->SetTileDefaultFrame(StartX, StartY, EndX, EndY);
}

void CTileMapWindow::SaveTileMapButton()
{
	if (!m_TileMap)
		return;

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("GameObject Data (*.dat)\0*.dat");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		// .dat이 붙었는지 확인
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	dat[5] = TEXT("tad.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != dat[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // dat 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(FilePath, TEXT(".dat"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CGameObject* TileMapObj = m_TileMap->GetGameObject();

		FILE* File = nullptr;

		fopen_s(&File, ConvertFullPath, "wb");

		if (!File)
			return;

		TileMapObj->Save(File);
		CPublic::GetInst()->Save(File);

		fclose(File);

		//TileMapObj->Save(ConvertFullPath);
	}
}

void CTileMapWindow::LoadTileMapButton()
{
	CreateTileMap();

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("GameObject Data (*.dat)\0*.dat");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// .dat이 붙었는지 확인
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	dat[5] = TEXT("tad.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != dat[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // dat 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(FilePath, TEXT(".dat"));

		char    ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		if (!m_TileMapSprite)
			m_TileMapSprite = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTileMapSprite>("TileMapInfo");

		CGameObject* TileMapObj = m_TileMap->GetGameObject();

		FILE* File = nullptr;

		fopen_s(&File, ConvertFullPath, "rb");

		if (!File)
			return;

		TileMapObj->Load(File);
		CPublic::GetInst()->Load(File);
		CPublic::GetInst()->LoadObjPos(TileMapObj);

		fclose(File);

		CEditorManager::GetInst()->LoadSceneObject();
		CEditorManager::GetInst()->SetEditMode(EditMode::TileMap);
	}
}
