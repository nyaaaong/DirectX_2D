
#include "TileMapComponent.h"
#include "CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/CameraManager.h"
#include "../Animation/AnimationSequence2DInstance.h"
#include "../Render/RenderManager.h"
#include "../Resource/Shader/Standard2DConstantBuffer.h"
#include "../Resource/Shader/TileMapConstantBuffer.h"
#include "../Resource/Shader/StructuredBuffer.h"
#include "../Scene/NavigationManager.h"

CTileMapComponent::CTileMapComponent()	:
	m_CBuffer(nullptr),
	m_Count(0)
{
	SetTypeID<CTileMapComponent>();
	m_Render = true;

	m_CountX = 0;
	m_CountY = 0;
	m_RenderCount = 0;
	m_LayerName = "Back";
	m_TileInfoBuffer = nullptr;

	m_DeltaTime = 0.f;

	for (int i = 0; i < (int)Tile_Type::End; ++i)
	{
		m_TileColor[i] = Vector4(1.f, 1.f, 1.f, 1.f);
	}

	m_TileColor[(int)Tile_Type::Wall] = Vector4(1.f, 0.f, 0.f, 1.f);
	m_TileColor[(int)Tile_Type::Object] = Vector4(1.f, 0.f, 1.f, 1.f);

	m_EditMode = false;

	m_SortDisable = true;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& com) :
	CSceneComponent(com)
{
	SetTypeID<CTileMapComponent>();

	m_CountX = com.m_CountX;
	m_CountY = com.m_CountY;

	m_DeltaTime = 0.f;

	m_BackMesh = com.m_BackMesh;

	if (com.m_BackMaterial)
		m_BackMaterial = com.m_BackMaterial->Clone();

	if (com.m_TileMaterial)
		m_TileMaterial = com.m_TileMaterial->Clone();

	if (com.m_CBuffer)
		m_CBuffer = com.m_CBuffer->Clone();

	if (com.m_TileInfoBuffer)
		m_TileInfoBuffer = com.m_TileInfoBuffer->Clone();

	for (int i = 0; i < (int)Tile_Type::End; ++i)
	{
		m_TileColor[i] = com.m_TileColor[i];
	}

	m_EditMode = com.m_EditMode;

	m_SortDisable = true;
}

CTileMapComponent::~CTileMapComponent()
{
	SAFE_DELETE(m_TileInfoBuffer);
	SAFE_DELETE(m_CBuffer);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}

	m_vecTile.clear();
}

void CTileMapComponent::SetBackMaterial(CMaterial* Material)
{
	m_BackMaterial = Material->Clone();

	m_BackMaterial->SetScene(m_Scene);
}

void CTileMapComponent::SetTileMaterial(CMaterial* Material)
{
	m_TileMaterial = Material->Clone();

	m_TileMaterial->SetScene(m_Scene);

	if (!m_TileMaterial->EmptyTexture())
	m_CBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTextureWidth(), (float)m_TileMaterial->GetTextureHeight()));
}

void CTileMapComponent::SetBackBaseColor(const Vector4& Color)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetBaseColor(Color);
}

void CTileMapComponent::SetBackBaseColor(float r, float g, float b, float a)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetBaseColor(r, g, b, a);
}

void CTileMapComponent::SetBackRenderState(CRenderState* State)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetRenderState(State);
}

void CTileMapComponent::SetBackRenderState(const std::string& Name)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetRenderState(Name);
}

void CTileMapComponent::SetBackTransparency(bool Enable)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetTransparency(Enable);
}

void CTileMapComponent::SetBackOpacity(float Opacity)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetOpacity(Opacity);
}

void CTileMapComponent::AddBackOpacity(float Opacity)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->AddOpacity(Opacity);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->AddTexture(Register, ShaderType, Name, Texture);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->AddTexture(Register, ShaderType, Name, FileName, PathName);
}

void CTileMapComponent::AddBackTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->AddTextureFullPath(Register, ShaderType, Name, FullPath);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->AddTexture(Register, ShaderType, Name, vecFileName, PathName);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, Texture);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, FileName, PathName);
}

void CTileMapComponent::SetBackTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name,
	const TCHAR* FullPath)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetTextureFullPath(Index, Register, ShaderType, Name, FullPath);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	if (!m_BackMaterial)
		return;

	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, vecFileName, PathName);
}

void CTileMapComponent::CreateTile(int CountX, int CountY, const Vector3& Size)
{
	m_CountX = CountX;
	m_CountY = CountY;
	m_TileSize = Size;

	size_t	TileSize = m_vecTile.size();

	for (size_t i = 0; i < TileSize; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}

	m_vecTile.resize(m_CountX * m_CountY);

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			CTile* Tile = DBG_NEW CTile;

			Tile->m_Owner = this;

			int	Index = i * m_CountX + j;

			Tile->SetIndex(j, i, Index);
			Tile->SetSize(m_TileSize);

			m_vecTile[Index] = Tile;
		}
	}

	Vector3	Pos;

	for (int i = 0; i < m_CountY; ++i)
	{
		Pos.x = 0.f;
		Pos.y = i * m_TileSize.y;

		for (int j = 0; j < m_CountX; ++j)
		{
			Pos.x = j * m_TileSize.x;

			int	Index = i * m_CountX + j;

			m_vecTile[Index]->SetPos(Pos);
		}
	}

	m_CBuffer->SetTileSize(Vector2(m_TileSize.x, m_TileSize.y));

	m_Count = m_CountX * m_CountY;

	SetWorldInfo();

	m_Scene->GetNavigationManager()->SetNavData(this);
}

void CTileMapComponent::SetTileDefaultFrame(const Vector2& Start, const Vector2& End)
{
	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTile[i]->SetFrameStart(Start);
		m_vecTile[i]->SetFrameEnd(End);
	}
}

void CTileMapComponent::SetTileDefaultFrame(float StartX, float StartY, float EndX, float EndY)
{
	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTile[i]->SetFrameStart(StartX, StartY);
		m_vecTile[i]->SetFrameEnd(EndX, EndY);
	}
}

void CTileMapComponent::SetTileFrame(int IndexX, int IndexY, float StartX, float StartY, float EndX, float EndY)
{
	m_vecTile[IndexY * m_CountX + IndexX]->SetFrameStart(StartX, StartY);
	m_vecTile[IndexY * m_CountX + IndexX]->SetFrameEnd(EndX, EndY);
}

void CTileMapComponent::SetTileFrame(int Index, float StartX, float StartY, float EndX, float EndY)
{
	m_vecTile[Index]->SetFrameStart(StartX, StartY);
	m_vecTile[Index]->SetFrameEnd(EndX, EndY);
}

void CTileMapComponent::SetTileFrame(const Vector3& Pos, float StartX, float StartY, float EndX, float EndY)
{
}

void CTileMapComponent::SetTileOpacity(int IndexX, int IndexY, float Opacity)
{
	m_vecTile[IndexY * m_CountX + IndexX]->SetOpacity(Opacity);
}

void CTileMapComponent::SetTileOpacity(int Index, float Opacity)
{
	m_vecTile[Index]->SetOpacity(Opacity);
}

void CTileMapComponent::SetTileOpacity(const Vector3& Pos, float Opacity)
{
}

void CTileMapComponent::SetTileColor(Tile_Type Type, float r, float g, float b, float a)
{
	m_TileColor[(int)Type] = Vector4(r, g, b, a);
}

void CTileMapComponent::SetTileColor(Tile_Type Type, const Vector4& Color)
{
	m_TileColor[(int)Type] = Color;
}

int CTileMapComponent::GetTileIndexX(const Vector3& Pos)
{
	float	ConvertX = Pos.x - GetWorldPos().x;

	if (ConvertX < 0.f)
		return -1;

	int	IndexX = (int)(ConvertX / m_TileSize.x);

	if (IndexX < 0 || IndexX >= m_CountX)
		return -1;

	return IndexX;
}

int CTileMapComponent::GetTileIndexY(const Vector3& Pos)
{
	float	ConvertY = Pos.y - GetWorldPos().y;

	if (ConvertY < 0.f)
		return -1;

	int	IndexY = (int)(ConvertY / m_TileSize.y);

	if (IndexY < 0 || IndexY >= m_CountY)
		return -1;

	return IndexY;
}

int CTileMapComponent::GetTileIndex(const Vector3& Pos)
{
	int	IndexX = GetTileIndexX(Pos);
	int	IndexY = GetTileIndexY(Pos);

	if (IndexX == -1 || IndexY == -1)
		return -1;

	return IndexY * m_CountX + IndexX;
}

CTile* CTileMapComponent::GetTile(const Vector3& Pos)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return nullptr;

	return m_vecTile[Index];
}

CTile* CTileMapComponent::GetTile(int x, int y)
{
	if (x < 0 || x >= m_CountX || y < 0 || y >= m_CountY)
		return nullptr;

	return m_vecTile[y * m_CountX + x];
}

CTile* CTileMapComponent::GetTile(int Index)
{
	if (Index < 0 || Index >= m_CountX * m_CountY)
		return nullptr;

	return m_vecTile[Index];
}

int CTileMapComponent::GetTileRenderIndexX(const Vector3& Pos)
{
	float	ConvertX = Pos.x - GetWorldPos().x;

	int	IndexX = (int)(ConvertX / m_TileSize.x);

	if (IndexX < 0)
		return 0;

	else if (IndexX >= m_CountX)
		return m_CountX - 1;

	return IndexX;
}

int CTileMapComponent::GetTileRenderIndexY(const Vector3& Pos)
{
	float	ConvertY = Pos.y - GetWorldPos().y;

	int	IndexY = (int)(ConvertY / m_TileSize.y);

	if (IndexY < 0)
		return 0;

	else if (IndexY >= m_CountY)
		return m_CountY - 1;

	return IndexY;
}

void CTileMapComponent::Start()
{
	CSceneComponent::Start();
}

bool CTileMapComponent::Init()
{
	m_BackMesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	//SetMaterial(m_Scene->GetResource()->FindMaterial("BaseTexture"));

	SetMeshSize(1.f, 1.f, 0.f);
	//SetWorldScale((float)m_BackMaterial->GetTextureWidth(),
	//	(float)m_BackMaterial->GetTextureHeight(), 1.f);

	m_CBuffer = DBG_NEW CTileMapConstantBuffer;

	m_CBuffer->Init();

	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	/*if (!m_First)
	{
		m_First = true;

		m_Scene->TileMap(true);
	}*/

	if (m_TileMaterial)
	{
		if (!m_TileMaterial->EmptyTexture())
			m_CBuffer->SetImageSize(Vector2((float)m_TileMaterial->GetTextureWidth(), (float)m_TileMaterial->GetTextureHeight()));
	}
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	m_DeltaTime = DeltaTime;
}

void CTileMapComponent::PrevRender()
{
	CSceneComponent::PrevRender();

	if (!m_vecTile.empty())
	{
		CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

		Resolution	RS = Camera->GetResolution();

		Vector3	LB = Camera->GetWorldPos();
		Vector3	RT = LB + Vector3((float)RS.Width, (float)RS.Height, 0.f);

		int	StartX, StartY, EndX, EndY;

		StartX = GetTileRenderIndexX(LB);
		StartY = GetTileRenderIndexY(LB);

		EndX = GetTileRenderIndexX(RT);
		EndY = GetTileRenderIndexY(RT);

		Matrix	matView, matProj;
		matView = Camera->GetViewMatrix();
		matProj = Camera->GetProjMatrix();

		m_RenderCount = 0;

		for (int i = StartY; i <= EndY; ++i)
		{
			for (int j = StartX; j <= EndX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->Update(m_DeltaTime, m_SortDisable);

				if (m_vecTile[Index]->GetRender())
				{
					if (m_EditMode)
					{
						m_vecTileInfo[m_RenderCount].TileColor = m_TileColor[(int)m_vecTile[Index]->GetTileType()];
					}

					m_vecTileInfo[m_RenderCount].TileStart = m_vecTile[Index]->GetFrameStart();
					m_vecTileInfo[m_RenderCount].TileEnd = m_vecTile[Index]->GetFrameEnd();
					m_vecTileInfo[m_RenderCount].Opacity = m_vecTile[Index]->GetOpacity();
					m_vecTileInfo[m_RenderCount].matWVP = m_vecTile[Index]->GetWorldMatrix() * matView * matProj;
					m_vecTileInfo[m_RenderCount].matWVP.Transpose();
					++m_RenderCount;
				}
			}
		}

		m_TileInfoBuffer->UpdateBuffer(&m_vecTileInfo[0], m_RenderCount);
	}
}

void CTileMapComponent::Render()
{
	CSceneComponent::Render();

	if (m_BackMaterial)
	{
		m_BackMaterial->Render();

		m_BackMesh->Render();

		m_BackMaterial->Reset();
	}

	if (m_TileMaterial && !m_vecTile.empty())
	{
		m_TileInfoBuffer->SetShader();

		m_CBuffer->UpdateCBuffer();

		m_TileMaterial->Render();

		m_BackMesh->RenderInstancing(m_RenderCount);

		m_TileMaterial->Reset();

		m_TileInfoBuffer->ResetShader();
	}
}

void CTileMapComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CTileMapComponent* CTileMapComponent::Clone()
{
	return DBG_NEW CTileMapComponent(*this);
}

void CTileMapComponent::Save(FILE* File)
{
	std::string	MeshName = m_BackMesh->GetName();

	int	Length = (int)MeshName.length();

	fwrite(&Length, sizeof(int), 1, File);
	fwrite(MeshName.c_str(), sizeof(char), Length, File);

	bool	MaterialEnable = false;

	if (m_BackMaterial)
		MaterialEnable = true;

	fwrite(&MaterialEnable, sizeof(bool), 1, File);

	if (m_BackMaterial)
		m_BackMaterial->Save(File);

	MaterialEnable = false;

	if (m_TileMaterial)
		MaterialEnable = true;

	fwrite(&MaterialEnable, sizeof(bool), 1, File);

	if (m_TileMaterial)
		m_TileMaterial->Save(File);

	fwrite(&m_CountX, sizeof(int), 1, File);
	fwrite(&m_CountY, sizeof(int), 1, File);
	fwrite(&m_Count, sizeof(int), 1, File);
	fwrite(&m_TileSize, sizeof(Vector3), 1, File);
	fwrite(m_TileColor, sizeof(Vector4), (int)Tile_Type::End, File);

	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTile[i]->Save(File);
	}

	CSceneComponent::Save(File);
}

void CTileMapComponent::Load(FILE* File)
{
	char	MeshName[256] = {};

	int	Length = 0;

	fread(&Length, sizeof(int), 1, File);
	fread(MeshName, sizeof(char), Length, File);

	m_BackMesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh(MeshName);

	bool	MaterialEnable = false;

	fread(&MaterialEnable, sizeof(bool), 1, File);

	if (MaterialEnable)
	{
		m_BackMaterial = m_Scene->GetResource()->CreateMaterialEmpty<CMaterial>();

		m_BackMaterial->Load(File);

	}

	MaterialEnable = false;

	fread(&MaterialEnable, sizeof(bool), 1, File);

	if (MaterialEnable)
	{
		m_TileMaterial = m_Scene->GetResource()->CreateMaterialEmpty<CMaterial>();

		m_TileMaterial->Load(File);
	}

	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountY, sizeof(int), 1, File);
	fread(&m_Count, sizeof(int), 1, File);
	fread(&m_TileSize, sizeof(Vector3), 1, File);
	fread(m_TileColor, sizeof(Vector4), (int)Tile_Type::End, File);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}

	m_vecTile.clear();

	m_vecTile.resize(m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		CTile* Tile = DBG_NEW CTile;

		Tile->m_Owner = this;

		Tile->Load(File);

		m_vecTile[i] = Tile;
	}

	SAFE_DELETE(m_CBuffer);

	m_CBuffer = DBG_NEW CTileMapConstantBuffer;

	m_CBuffer->Init();

	SetWorldInfo();
	
	m_Scene->GetNavigationManager()->SetNavData(this);

	CSceneComponent::Load(File);
}

void CTileMapComponent::SetWorldInfo()
{
	SAFE_DELETE(m_TileInfoBuffer);

	m_TileInfoBuffer = DBG_NEW CStructuredBuffer;

	m_TileInfoBuffer->Init("TileInfo", sizeof(TileInfo), m_CountX * m_CountY, 40, true, (int)Buffer_Shader_Type::Vertex);

	m_vecTileInfo.resize(m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTileInfo[i].TileColor = Vector4(1.f, 1.f, 1.f, 1.f);
		m_vecTileInfo[i].Opacity = 1.f;
	}
}
