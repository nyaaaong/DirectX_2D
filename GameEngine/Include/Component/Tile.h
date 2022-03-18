#pragma once

#include "../Engine.h"
#include "../Animation/AnimationSequence2DInstance.h"

class CTile
{
	friend class CTileMapComponent;

private:
	CTile();
	CTile(const CTile& tile);
	~CTile();

private:
	class CTileMapComponent* m_Owner;
	Tile_Type	m_TileType;
	Object_Type	m_ObjectType;
	Vector3		m_Pos;			// ¡¬ «œ¥‹ ±‚¡ÿ.
	Vector3		m_WorldPos;			// ¡¬ «œ¥‹ ±‚¡ÿ.
	Vector3		m_Size;
	Vector3		m_Center;
	Matrix		m_matWorld;
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;
	Vector2		m_FrameStart;
	Vector2		m_FrameEnd;
	float		m_Opacity;

public:
	Object_Type GetObjectType()	const
	{
		if (m_ObjectType == Object_Type::BulletKin)
			int a = 0;

		return m_ObjectType;
	}

	float GetOpacity()	const
	{
		return m_Opacity;
	}

	Tile_Type GetTileType()	const
	{
		return m_TileType;
	}

	const Vector3& GetSize()	const
	{
		return m_Size;
	}

	const Vector3& GetCenter()	const
	{
		return m_Center;
	}

	const Vector3& GetWorldPos()	const
	{
		return m_WorldPos;
	}

	const Vector3& GetPos()	const
	{
		return m_Pos;
	}

	const Matrix& GetWorldMatrix()	const
	{
		return m_matWorld;
	}

	int GetIndexX()	const
	{
		return m_IndexX;
	}

	int GetIndexY()	const
	{
		return m_IndexY;
	}

	int GetIndex()	const
	{
		return m_Index;
	}

	Vector2 GetFrameStart()	const
	{
		return m_FrameStart;
	}

	Vector2 GetFrameEnd()	const
	{
		return m_FrameEnd;
	}

	bool GetRender()	const
	{
		return m_FrameStart.x != 0.f || m_FrameStart.y != 0.f || m_FrameEnd.x != 0.f || m_FrameEnd.y != 0.f;
	}

public:
	void SetObjectType(Object_Type Type)
	{
		if (m_ObjectType == Object_Type::BulletKin)
			int a = 0;

		m_ObjectType = Type;
	}

	void SetOpacity(float Opacity)
	{
		m_Opacity = Opacity;
	}

	void SetFrameStart(const Vector2& Frame)
	{
		m_FrameStart = Frame;
	}

	void SetFrameStart(float x, float y)
	{
		m_FrameStart = Vector2(x, y);
	}

	void SetFrameEnd(const Vector2& Frame)
	{
		m_FrameEnd = Frame;
	}

	void SetFrameEnd(float x, float y)
	{
		m_FrameEnd = Vector2(x, y);
	}

	void SetIndex(int IndexX, int IndexY, int Index)
	{
		m_IndexX = IndexX;
		m_IndexY = IndexY;
		m_Index = Index;
	}

	void SetTileType(Tile_Type Type)
	{
		m_TileType = Type;
	}

	void SetPos(const Vector3& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y, float z)
	{
		m_Pos = Vector3(x, y, z);
	}

	void SetSize(const Vector3& Size)
	{
		m_Size = Size;
	}

	void SetSize(float x, float y, float z)
	{
		m_Size = Vector3(x, y, z);
	}

public:
	void Start();
	void Update(float DeltaTime, bool SortDiable);
	void Save(FILE* File);
	void Load(FILE* File);
};

