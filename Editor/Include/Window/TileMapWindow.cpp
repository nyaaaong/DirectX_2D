
#include "TileMapWindow.h"
#include "Input.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Texture/Texture.h"
#include "Component/Tile.h"
#include "../EditorManager.h"

CTileMapWindow::CTileMapWindow()
{
}

CTileMapWindow::~CTileMapWindow()
{
}

bool CTileMapWindow::Init()
{
	CIMGUIWindow::Init();

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("TileMapInfo", 324.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(31, 81, 183);

	Label = AddWidget<CIMGUILabel>("TileShape", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ShapeCombo = AddWidget<CIMGUIComboBox>("Shape", 80.f, 20.f);

	m_ShapeCombo->SetHideName(true);
	m_ShapeCombo->AddItem("Rect");
	m_ShapeCombo->AddItem("Rhombus");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TileMapCreateButton = AddWidget<CIMGUIButton>("TileMapCreateButton", 158.f, 20.f);
	m_TileMapCreateButton->SetClickCallback(this, &CTileMapWindow::TileMapCreateButton);

	Label = AddWidget<CIMGUILabel>("CountX", 70.f, 20.f);
	Label->SetAlign(0.5f, 0.f);
	Label->SetColor(15, 15, 15);

	Line = AddWidget<CIMGUISameLine>("Line");

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


	CreateTileEditControl();


	m_CountX->SetInt(100);
	m_CountY->SetInt(100);
	m_SizeX->SetFloat(160.f);
	m_SizeY->SetFloat(80.f);

	m_FrameStartX->SetFloat(160.f);
	m_FrameStartY->SetFloat(80.f);
	m_FrameEndX->SetFloat(320.f);
	m_FrameEndY->SetFloat(160.f);

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
	if (!m_TileMap)
		return;

	int	ShapeIndex = m_ShapeCombo->GetSelectIndex();

	if (ShapeIndex >= (int)Tile_Shape::End || ShapeIndex < 0)
		return;

	int	CountX, CountY;

	CountX = m_CountX->GetValueInt();
	CountY = m_CountY->GetValueInt();

	Vector3	Size;
	Size.x = m_SizeX->GetValueFloat();
	Size.y = m_SizeY->GetValueFloat();

	m_TileMap->CreateTile((Tile_Shape)ShapeIndex, CountX, CountY, Size);

	CMaterial* Material = m_TileMap->GetTileMaterial();
	CTexture* Texture = nullptr;

	if ((Tile_Shape)ShapeIndex == Tile_Shape::Rect)
	{
		CSceneManager::GetInst()->GetScene()->GetResource()->LoadTexture("DefaultRectTile",
			TEXT("Map/TileMap.png"));

		Texture = CSceneManager::GetInst()->GetScene()->GetResource()->FindTexture("DefaultRectTile");
	}

	else
	{
		CSceneManager::GetInst()->GetScene()->GetResource()->LoadTexture("DefaultRhombusTile",
			TEXT("Diablos_Lair_Floor_TRS/Diablos_Lair_Floor.png"));

		Texture = CSceneManager::GetInst()->GetScene()->GetResource()->FindTexture("DefaultRhombusTile");
	}

	if (Material->EmptyTexture())
		Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "TileTexture", Texture);

	else
		Material->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "TileTexture", Texture);
}

void CTileMapWindow::DefaultFrameButton()
{
	if (!m_TileMap)
		return;

	float	StartX, StartY, EndX, EndY;

	StartX = m_FrameStartX->GetValueFloat();
	StartY = m_FrameStartY->GetValueFloat();
	EndX = m_FrameEndX->GetValueFloat();
	EndY = m_FrameEndY->GetValueFloat();

	m_TileMap->SetTileDefaultFrame(StartX, StartY, EndX, EndY);
}
