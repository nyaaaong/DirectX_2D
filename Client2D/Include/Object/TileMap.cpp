
#include "TileMap.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"

CTileMap::CTileMap()
{
	SetTypeID<CTileMap>();
}

CTileMap::CTileMap(const CTileMap& obj) :
	CGameObject(obj)
{
	m_TileMap = (CTileMapComponent*)FindComponent("TileMap");
}

CTileMap::~CTileMap()
{
}

void CTileMap::Start()
{
	CGameObject::Start();

	if (!m_TileMap)
	{
		CSceneComponent* Root = m_RootComponent;
		CTileMapComponent* TileMap = dynamic_cast<CTileMapComponent*>(Root);

		if (!TileMap)
			ASSERT("if (!TileMap)");

		m_TileMap = TileMap;
	}
}

bool CTileMap::Init()
{
	if (!CGameObject::Init())
		return false;

	m_TileMap = CreateComponent<CTileMapComponent>("TileMap");

	SetRootComponent(m_TileMap);

	m_TileMap->CreateTile(100, 100, Vector3(54.f, 54.f, 0.f));

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	m_TileMap->SetTileMaterial(Material);

	m_TileMap->SetTileDefaultFrame(0.f, 0.f, 54.f, 54.f);

	return true;
}

void CTileMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTileMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTileMap* CTileMap::Clone()
{
	return DBG_NEW CTileMap(*this);
}

int CTileMap::GetTileCountX() const
{
	if (!m_TileMap)
		return -1;

	return m_TileMap->GetTileCountX();
}

int CTileMap::GetTileCountY() const
{
	if (!m_TileMap)
		return -1;

	return m_TileMap->GetTileCountY();
}

Vector3 CTileMap::GetTileSize() const
{
	if (!m_TileMap)
		return Vector3();

	return m_TileMap->GetTileSize();
}

CTile* CTileMap::GetTile(const Vector3& Pos) const
{
	if (!m_TileMap)
		return nullptr;

	return m_TileMap->GetTile(Pos);
}

CTile* CTileMap::GetTile(int x, int y) const
{
	if (!m_TileMap)
		return nullptr;

	return m_TileMap->GetTile(x, y);
}

CTile* CTileMap::GetTile(int Index) const
{
	if (!m_TileMap)
		return nullptr;

	return m_TileMap->GetTile(Index);
}

Tile_Type CTileMap::GetTileType(const Vector3& Pos) const
{
	if (!m_TileMap)
		return Tile_Type::End;

	CTile* Tile = m_TileMap->GetTile(Pos);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}

Tile_Type CTileMap::GetTileType(int x, int y) const
{
	if (!m_TileMap)
		return Tile_Type::End;

	CTile* Tile = m_TileMap->GetTile(x, y);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}

Tile_Type CTileMap::GetTileType(int Index) const
{
	if (!m_TileMap)
		return Tile_Type::End;

	CTile* Tile = m_TileMap->GetTile(Index);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}
