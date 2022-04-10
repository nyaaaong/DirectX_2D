#pragma once

#include "SceneComponent.h"
#include "../Resource/Mesh/SpriteMesh.h"
#include "../Resource/Material/Material.h"
#include "Tile.h"

class CTileMapComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CPublic;

protected:
	CTileMapComponent();
	CTileMapComponent(const CTileMapComponent& com);
	virtual ~CTileMapComponent();

protected:
	CSharedPtr<CSpriteMesh> m_BackMesh;
	CSharedPtr<CMaterial> m_BackMaterial;
	CSharedPtr<CMaterial> m_TileMaterial;
	std::vector<CTile*> m_vecTile;
	std::vector<TileInfo>   m_vecTileInfo;
	class CTileMapConstantBuffer* m_CBuffer;
	class CStructuredBuffer* m_TileInfoBuffer;
	int     m_CountX;
	int     m_CountY;
	int     m_Count;
	int     m_RenderCount;
	Vector3 m_TileSize;
	Vector4 m_TileColor[(int)Tile_Type::Max];
	bool    m_EditMode;
	float   m_DeltaTime;
	bool    m_SortDisable;

public:
	void SetTileColorWhite()
	{
		for (int i = 0; i < (int)Tile_Type::Max; ++i)
		{
			m_TileColor[i] = Vector4(1.f, 1.f, 1.f, 1.f);
		}
	}

	void EnableEditMode(bool Mode)
	{
		m_EditMode = Mode;
	}

	void SetSortDisable(bool SortDisable)
	{
		m_SortDisable = SortDisable;
	}

public:
	void GetSameTypeTile(Tile_Type Type, std::vector<CTile*>& vecTile)
	{
		int Size = (int)m_vecTile.size();

		for (int i = 0; i < Size; ++i)
		{
			if (m_vecTile[i]->GetTileType() == Type)
				vecTile.push_back(m_vecTile[i]);
		}
	}

	void GetSameObjectTypeTile(Object_Type Type, const std::vector<CTile*>& vecInput, std::vector<CTile*>& vecOutput)
	{
		int Size = (int)vecInput.size();

		for (int i = 0; i < Size; ++i)
		{
			if (vecInput[i]->GetObjectType() == Type)
				vecOutput.push_back(vecInput[i]);
		}
	}

	CMaterial* GetBackMaterial()    const
	{
		return m_BackMaterial;
	}

	CMaterial* GetTileMaterial()    const
	{
		return m_TileMaterial;
	}

	int GetTileCount()	const
	{
		return m_Count;
	}

	int GetTileCountX() const
	{
		return m_CountX;
	}

	int GetTileCountY() const
	{
		return m_CountY;
	}

	const Vector3& GetTileSize()    const
	{
		return m_TileSize;
	}

public:
	void SetBackMaterial(CMaterial* Material);
	void SetTileMaterial(CMaterial* Material);

public:
	void SetBackBaseColor(const Vector4& Color);
	void SetBackBaseColor(float r, float g, float b, float a);
	void SetBackRenderState(class CRenderState* State);
	void SetBackRenderState(const std::string& Name);
	void SetBackTransparency(bool Enable);
	void SetBackOpacity(float Opacity);
	void AddBackOpacity(float Opacity);

public:
	void AddBackTexture(int Register, int ShaderType, const std::string& Name, class CTexture* Texture);
	void AddBackTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void AddBackTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath);
	void AddBackTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);


	void SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, class CTexture* Texture);
	void SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	void SetBackTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath);
	void SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);

public:
	void CreateTile(int CountX, int CountY, const Vector3& Size);
	void SetTileDefaultFrame(const Vector2& Start, const Vector2& End);
	void SetTileDefaultFrame(float StartX, float StartY, float EndX, float EndY);
	void SetTileFrame(int IndexX, int IndexY, float StartX, float StartY, float EndX, float EndY);
	void SetTileFrame(int Index, float StartX, float StartY, float EndX, float EndY);
	void SetTileFrame(const Vector3& Pos, float StartX, float StartY, float EndX, float EndY);
	void SetTileOpacity(int IndexX, int IndexY, float Opacity);
	void SetTileOpacity(int Index, float Opacity);
	void SetTileOpacity(const Vector3& Pos, float Opacity);
	void SetTileColor(Tile_Type Type, float r, float g, float b, float a);
	void SetTileColor(Tile_Type Type, const Vector4& Color);


public:
	int GetTileIndexX(const Vector3& Pos);
	int GetTileIndexY(const Vector3& Pos);
	int GetTileIndex(const Vector3& Pos);
	CTile* GetTile(const Vector3& Pos);
	CTile* GetTile(int x, int y);
	CTile* GetTile(int Index);


private:
	int GetTileRenderIndexX(const Vector3& Pos);
	int GetTileRenderIndexY(const Vector3& Pos);

public:
	void DeleteTile(Object_Type Type);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CTileMapComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void SetWorldInfo();
};

