#pragma once

#include "IMGUIWindow.h"
#include "Component/TileMapComponent.h"
#include "../EditorInfo.h"
#include "../Object/TileMapSprite.h"

class CTileMapWindow :
    public CIMGUIWindow
{
public:
	CTileMapWindow();
	virtual ~CTileMapWindow();

private:
	class CIMGUITextInput* m_CountX;
	class CIMGUITextInput* m_CountY;
	class CIMGUITextInput* m_SizeX;
	class CIMGUITextInput* m_SizeY;
	class CIMGUITextInput* m_FrameStartX;
	class CIMGUITextInput* m_FrameStartY;
	class CIMGUITextInput* m_FrameEndX;
	class CIMGUITextInput* m_FrameEndY;
	class CIMGUIComboBox* m_TypeCombo;
	class CIMGUIComboBox* m_TileEditCombo;
	class CIMGUIButton* m_TileMapCreateButton;
	class CIMGUIButton* m_DefaultFrameButton;
	class CIMGUIButton* m_LoadTileMapButton;
	class CIMGUIButton* m_TileMapSaveButton;
	class CIMGUIButton* m_TileMapLoadButton;
	CSharedPtr<CTileMapComponent>		m_TileMap;
	CSharedPtr<CTileMapSprite>	m_TileMapSprite;
	TCHAR	m_TileMapFullPath[MAX_PATH];

public:
	CSharedPtr<CTileMapSprite> GetTileMapSprite()	const
	{
		return m_TileMapSprite;
	}

public:
	void SetTileMap(CTileMapComponent* TileMap)
	{
		m_TileMap = TileMap;
	}

public:
	virtual bool Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetTileStart(float StartX, float StartY);
	void SetTileStart(const Vector2& Start);
	void SetTileEnd(float EndX, float EndY);
	void SetTileEnd(const Vector2& End);

private:
	void DefaultFrameButton();
	void TileMapCreateButton();
	void LoadTileMapButton();
	void TileMapSaveButton();
	void TileMapLoadButton();

private:
	void CreateTileEditControl();
	void CreateTileMap();

};

