
#include "TileMapWindow.h"
#include "Input.h"
#include "PathManager.h"
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
	m_TileMapCreateButton(nullptr),
	m_DefaultFrameButton(nullptr),
	m_LoadTileMapButton(nullptr),
	m_TileMapSaveButton(nullptr),
	m_TileMapLoadButton(nullptr),
	m_TileMapSpriteView(nullptr),
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

	if (!m_TileMapSprite)
		m_TileMapSprite = CSceneManager::GetInst()->GetScene()->CreateGameObject<CTileMapSprite>("TileMapInfo");

	return true;
}

bool CTileMapWindow::Init()
{
	if (!CIMGUIWindow::Init())
		return false;

	m_LoadTileMapButton = AddWidget<CIMGUIButton>("LoadTileMapButton", 324.f, 40.f);
	m_LoadTileMapButton->SetClickCallback(this, &CTileMapWindow::LoadTileMapButton);

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
	m_CountX->SetCallback(this, &CTileMapWindow::CountXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("CountY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_CountY = AddWidget<CIMGUITextInput>("CountY", 80.f, 20.f);
	m_CountY->SetHideName(true);
	m_CountY->SetTextType(ImGuiText_Type::Int);
	m_CountY->SetCallback(this, &CTileMapWindow::CountYCallback);

	Label = AddWidget<CIMGUILabel>("SizeX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_SizeX = AddWidget<CIMGUITextInput>("SizeX", 80.f, 20.f);
	m_SizeX->SetHideName(true);
	m_SizeX->SetTextType(ImGuiText_Type::Float);
	m_SizeX->SetCallback(this, &CTileMapWindow::SizeXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("SizeY", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_SizeY = AddWidget<CIMGUITextInput>("SizeY", 80.f, 20.f);
	m_SizeY->SetHideName(true);
	m_SizeY->SetTextType(ImGuiText_Type::Float);
	m_SizeY->SetCallback(this, &CTileMapWindow::SizeYCallback);

	m_TileMapCreateButton = AddWidget<CIMGUIButton>("TileMapCreateButton", 324.f, 20.f);
	m_TileMapCreateButton->SetClickCallback(this, &CTileMapWindow::TileMapCreateButton);

	CreateTileEditControl();


	m_TileMapSaveButton = AddWidget<CIMGUIButton>("TileMapSaveButton", 160.f, 20.f);
	m_TileMapSaveButton->SetClickCallback(this, &CTileMapWindow::TileMapSaveButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TileMapLoadButton = AddWidget<CIMGUIButton>("TileMapLoadButton", 156.f, 20.f);
	m_TileMapLoadButton->SetClickCallback(this, &CTileMapWindow::TileMapLoadButton);

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

void CTileMapWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	// 마우스 Drag처리
	if (CEditorManager::GetInst()->GetEditMode() == EditMode::TileMap && m_TileMap)
	{
		m_TileMap->EnableEditMode(true);

		if (CEditorManager::GetInst()->GetLButtonPush())
		{
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

					Tile->SetTileType(Type);
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

void CTileMapWindow::CountXCallback()
{
}

void CTileMapWindow::CountYCallback()
{
}

void CTileMapWindow::SizeXCallback()
{
}

void CTileMapWindow::SizeYCallback()
{
}

void CTileMapWindow::TileMapCreateButton()
{
	if (!m_TileMap || !m_TileMapFullPath)
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

void CTileMapWindow::LoadTileMapButton()
{
	if (!m_TileMap)
		return;

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

		if (!m_TileMapSpriteView)
		{
			m_TileMapSpriteView = AddWidget<CIMGUIImage>("TileMapSpriteView", 200.f, 200.f);

			CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");
		}

		m_TileMapSpriteView->SetTextureFullPath(ConvertFileName, m_TileMapFullPath);

		m_TileMapSprite->GetSpriteComponent()->SetTextureFullPath(0, 0, (int)Buffer_Shader_Type::Pixel, ConvertFileName, m_TileMapFullPath);
	}
}

void CTileMapWindow::DefaultFrameButton()
{
	if (!m_TileMap || !m_TileMapFullPath)
		return;

	float	StartX, StartY, EndX, EndY;

	StartX = m_FrameStartX->GetValueFloat();
	StartY = m_FrameStartY->GetValueFloat();
	EndX = m_FrameEndX->GetValueFloat();
	EndY = m_FrameEndY->GetValueFloat();

	m_TileMap->SetTileDefaultFrame(StartX, StartY, EndX, EndY);
}

void CTileMapWindow::TileMapSaveButton()
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

		TileMapObj->Save(ConvertFullPath);
	}
}

void CTileMapWindow::TileMapLoadButton()
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

		CGameObject* TileMapObj = m_TileMap->GetGameObject();

		TileMapObj->Load(ConvertFullPath);
	}
}
