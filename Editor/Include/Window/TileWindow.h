#pragma once

#include "IMGUIWindow.h"

class CTileWindow :
    public CIMGUIWindow
{
public:
	CTileWindow();
	virtual ~CTileWindow();

private:
	std::vector<class CIMGUIImage*>		m_vecTile;
	CSharedPtr<class CTileMapSprite>	m_TileMapSprite;
	bool	m_Start;
	Vector2	m_TileSize;
	class CIMGUIImage* m_HoveredTile;
	class CIMGUIImage* m_SelectTile;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetTileSize(float SizeX, float SizeY)
	{
		m_TileSize.x = SizeX;
		m_TileSize.y = SizeY;
	}

	void SetTileMapSprite(class CTileMapSprite* Sprite)
	{
		m_TileMapSprite = Sprite;

		m_Start = false;
	}

private:
	void TileRegister();
	void TileMapSpriteUpdater();
};