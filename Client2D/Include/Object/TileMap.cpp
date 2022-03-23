
#include "TileMap.h"
#include "Engine.h"
#include "Public.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"

CTileMap::CTileMap()
{
	SetTypeID<CTileMap>();
}

CTileMap::CTileMap(const CTileMap& obj) :
	CGameObject(obj)
{
	m_TileMapComponent = (CTileMapComponent*)FindComponent("TileMapComponent");
}

CTileMap::~CTileMap()
{
}

void CTileMap::Start()
{
	CGameObject::Start();

	if (!m_TileMapComponent)
	{
		CSceneComponent* Root = m_RootComponent;
		CTileMapComponent* TileMapComponent = dynamic_cast<CTileMapComponent*>(Root);

		if (!TileMapComponent)
			ASSERT("if (!TileMapComponent)");

		m_TileMapComponent = TileMapComponent;
	}
}

bool CTileMap::Init()
{
	if (!CGameObject::Init())
		return false;

	m_TileMapComponent = CreateComponent<CTileMapComponent>("TileMapComponent");

	SetRootComponent(m_TileMapComponent);

	m_TileMapComponent->CreateTile(100, 100, Vector3(54.f, 54.f, 0.f));

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	m_TileMapComponent->SetTileMaterial(Material);

	m_TileMapComponent->SetTileDefaultFrame(0.f, 0.f, 54.f, 54.f);

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

void CTileMap::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CTileMap::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	Load(File);
	CPublic::GetInst()->Load(File);

	fclose(File);
}

void CTileMap::Load(const char* FileName, const std::string& PathName)
{
	CGameObject::Load(FileName, PathName);

	m_TileMapComponent = (CTileMapComponent*)GetRootComponent();
}

int CTileMap::GetTileCountX() const
{
	if (!m_TileMapComponent)
		return -1;

	return m_TileMapComponent->GetTileCountX();
}

int CTileMap::GetTileCountY() const
{
	if (!m_TileMapComponent)
		return -1;

	return m_TileMapComponent->GetTileCountY();
}

Vector3 CTileMap::GetTileSize() const
{
	if (!m_TileMapComponent)
		return Vector3();

	return m_TileMapComponent->GetTileSize();
}

CTile* CTileMap::GetTile(const Vector3& Pos) const
{
	if (!m_TileMapComponent)
		return nullptr;

	return m_TileMapComponent->GetTile(Pos);
}

CTile* CTileMap::GetTile(int x, int y) const
{
	if (!m_TileMapComponent)
		return nullptr;

	return m_TileMapComponent->GetTile(x, y);
}

CTile* CTileMap::GetTile(int Index) const
{
	if (!m_TileMapComponent)
		return nullptr;

	return m_TileMapComponent->GetTile(Index);
}

Tile_Type CTileMap::GetTileType(const Vector3& Pos) const
{
	if (!m_TileMapComponent)
		return Tile_Type::End;

	CTile* Tile = m_TileMapComponent->GetTile(Pos);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}

Tile_Type CTileMap::GetTileType(const Vector2& Pos) const
{
    return GetTileType((int)Pos.x, (int)Pos.y);
}

Tile_Type CTileMap::GetTileType(int x, int y) const
{
	if (!m_TileMapComponent)
		return Tile_Type::End;

	CTile* Tile = m_TileMapComponent->GetTile(x, y);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}

Tile_Type CTileMap::GetTileType(int Index) const
{
	if (!m_TileMapComponent)
		return Tile_Type::End;

	CTile* Tile = m_TileMapComponent->GetTile(Index);

	if (!Tile)
		return Tile_Type::End;

	return Tile->GetTileType();
}
