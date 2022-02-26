
#include "TileWindow.h"
#include "TileMapWindow.h"
#include "IMGUISameLine.h"
#include "IMGUIImage.h"
#include "../Object/TileMapSprite.h"
#include "Component/SpriteComponent.h"
#include "../EditorManager.h"

CTileWindow::CTileWindow()	:
	m_Start(false),
	m_HoveredTile(nullptr),
	m_SelectTile(nullptr)
{
}

CTileWindow::~CTileWindow()
{
}

bool CTileWindow::Init()
{
	if (!CIMGUIWindow::Init())
		return false;

	return true;
}

void CTileWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	TileMapSpriteUpdater();
}

void CTileWindow::TileRegister()
{
	if (!m_Start)
	{
		if (m_TileSize.x == 0.f || m_TileSize.y == 0.f)
			ASSERT("if (m_TileSize.x == 0.f || m_TileSize.y == 0.f)");

		m_Start = true;

		m_vecTile.clear();

		CMaterial* SpriteMaterial = m_TileMapSprite->GetSpriteComponent()->GetMaterial();
		unsigned int Width = SpriteMaterial->GetTextureWidth();
		unsigned int Height = SpriteMaterial->GetTextureHeight();

		Width /= (unsigned int)m_TileSize.x;
		Height /= (unsigned int)m_TileSize.y;

		char    TileIndex[32] = {};

		m_vecTile.resize((size_t)Width * Height);

		for (unsigned int i = 0; i < Height; ++i)
		{
			for (unsigned int j = 0; j < Width; ++j)
			{
				memset(TileIndex, 0, sizeof(char) * 32);

				sprintf_s(TileIndex, "TileX%d TileY%d", j, i);

				CIMGUIImage* TileImage = AddWidget<CIMGUIImage>(TileIndex, m_TileSize.x, m_TileSize.y);
				TileImage->SetTexture(m_TileMapSprite->GetSpriteComponent()->GetMaterial()->GetTexture());
				TileImage->MouseCheck(true);
				TileImage->SetImageStart(j * m_TileSize.x, i * m_TileSize.y);
				TileImage->SetImageEnd((j + 1) * m_TileSize.x, (i + 1) * m_TileSize.y);

				m_vecTile[i * Width + j] = TileImage;

				if (j != Width - 1)
				{
					CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");
					Line->SetSpacing(0.f);
				}
			}
		}
	}
}

void CTileWindow::TileMapSpriteUpdater()
{
	if (m_TileMapSprite)
	{
		TileRegister();

		CTileMapWindow* TileMapWindow = CEditorManager::GetInst()->GetTileMapWindow();

		size_t	Size = m_vecTile.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecTile[i])
			{
				if (m_vecTile[i]->IsClicked())
				{
					if (m_SelectTile && (m_vecTile[i] != m_SelectTile))
						m_SelectTile->DefaultBorderColor();

					if (m_vecTile[i] != m_HoveredTile)
						m_HoveredTile->DefaultBorderColor();

					m_SelectTile = m_vecTile[i];
					m_SelectTile->SetBorderColor(0, 255, 0);

					TileMapWindow->SetTileStart(m_SelectTile->GetImageStart());
					TileMapWindow->SetTileEnd(m_SelectTile->GetImageEnd());
				}

				else if (m_vecTile[i]->IsHovered())
				{
					if (m_HoveredTile && (m_vecTile[i] != m_HoveredTile))
						m_HoveredTile->DefaultBorderColor();

					m_HoveredTile = m_vecTile[i];
					m_HoveredTile->SetBorderColor(0, 162, 232);
				}

				else if (m_SelectTile)
					m_SelectTile->SetBorderColor(0, 255, 0);
			}
		}
	}
}
