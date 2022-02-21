#pragma once

#include "IMGUIWindow.h"

class CTileWindow :
    public CIMGUIWindow
{
public:
	CTileWindow();
	virtual ~CTileWindow();

private:
	std::vector<class CIMGUIImage*> m_vecTile;
	CSharedPtr<CTileMapSprite>	m_TileMapSprite;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};