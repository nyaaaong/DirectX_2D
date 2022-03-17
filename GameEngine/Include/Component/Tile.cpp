
#include "Tile.h"
#include "TileMapComponent.h"
#include "../Resource/Animation/AnimationSequence2D.h"

CTile::CTile() :
	m_TileType(Tile_Type::Normal),
	m_ObjectType(Object_Type::Max),
	m_Owner(nullptr),
	m_IndexX(-1),
	m_IndexY(-1),
	m_Index(-1),
	m_Opacity(1.f)
{
}

CTile::CTile(const CTile& tile)
{
	*this = tile;
}

CTile::~CTile()
{
}

void CTile::Start()
{
	m_Center = m_Pos + m_Size / 2.f;
}

void CTile::Update(float DeltaTime, bool SortDiable)
{
	Vector3	OwnerPos = m_Owner->GetWorldPos();

	Vector3	Pos = OwnerPos + m_Pos;

	m_WorldPos = Pos;

	if (CEngine::GetInst()->GetEngineSpace() == Engine_Space::Space2D)
	{
		if (SortDiable)
			m_WorldPos.z = 999.9999f;

		else
			m_WorldPos.z = m_WorldPos.y / 30000.f * 1000.f;;
	}

	Matrix	matScale, matTranslate;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matTranslate.Translation(m_WorldPos);

	m_matWorld = matScale * matTranslate;
}

void CTile::Save(FILE* File)
{
	fwrite(&m_TileType, sizeof(Tile_Type), 1, File);
	fwrite(&m_ObjectType, sizeof(Tile_Type), 1, File);

	fwrite(&m_Pos, sizeof(Vector3), 1, File);
	fwrite(&m_Size, sizeof(Vector3), 1, File);
	fwrite(&m_Center, sizeof(Vector3), 1, File);

	fwrite(&m_IndexX, sizeof(int), 1, File);
	fwrite(&m_IndexY, sizeof(int), 1, File);
	fwrite(&m_Index, sizeof(int), 1, File);

	fwrite(&m_FrameStart, sizeof(Vector2), 1, File);
	fwrite(&m_FrameEnd, sizeof(Vector2), 1, File);

	fwrite(&m_Opacity, sizeof(float), 1, File);
}

void CTile::Load(FILE* File)
{
	fread(&m_TileType, sizeof(Tile_Type), 1, File);
	fread(&m_ObjectType, sizeof(Tile_Type), 1, File);

	fread(&m_Pos, sizeof(Vector3), 1, File);
	fread(&m_Size, sizeof(Vector3), 1, File);
	fread(&m_Center, sizeof(Vector3), 1, File);

	fread(&m_IndexX, sizeof(int), 1, File);
	fread(&m_IndexY, sizeof(int), 1, File);
	fread(&m_Index, sizeof(int), 1, File);

	fread(&m_FrameStart, sizeof(Vector2), 1, File);
	fread(&m_FrameEnd, sizeof(Vector2), 1, File);

	fread(&m_Opacity, sizeof(float), 1, File);
}
