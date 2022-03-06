#pragma once

#include "GameObject/GameObject.h"
#include "Component/TileMapComponent.h"

class CTileMap :
	public CGameObject
{
	friend class CScene;

protected:
	CTileMap();
	CTileMap(const CTileMap& obj);
	virtual ~CTileMap();

private:
	CSharedPtr<CTileMapComponent>    m_TileMap;

public:
	bool HasTileMap()	const
	{
		return m_TileMap != nullptr;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTileMap* Clone();

public:
	int GetTileCountX()	const;
	int GetTileCountY()	const;
	Vector3 GetTileSize()	const;
	CTile* GetTile(const Vector3& Pos)	const;
	CTile* GetTile(int x, int y)	const;
	CTile* GetTile(int Index)	const;
};

