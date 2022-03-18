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
	CSharedPtr<CTileMapComponent>    m_TileMapComponent;

public:
	bool HasTileMapComponent()	const
	{
		return m_TileMapComponent != nullptr;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTileMap* Clone();
	virtual void Load(FILE* File);
	virtual void Load(const char* FullPath);
	virtual void Load(const char* FileName, const std::string& PathName);

public:
	int GetTileCountX()	const;
	int GetTileCountY()	const;
	Vector3 GetTileSize()	const;
	CTile* GetTile(const Vector3& Pos)	const;
	CTile* GetTile(int x, int y)	const;
	CTile* GetTile(int Index)	const;
	Tile_Type GetTileType(const Vector3& Pos)	const;
	Tile_Type GetTileType(int x, int y)	const;
	Tile_Type GetTileType(int Index)	const;
};

