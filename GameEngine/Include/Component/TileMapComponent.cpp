
#include "TileMapComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Animation/AnimationSequence2DInstance.h"
#include "../Render/RenderManager.h"
#include "../Resource/Shader/Standard2DConstantBuffer.h"
#include "../Scene/SceneManager.h"

CTileMapComponent::CTileMapComponent()
{
	SetTypeID<CTileMapComponent>();
	m_Render = true;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& com) :
	CSceneComponent(com)
{
	m_BackMesh = com.m_BackMesh;

	if (com.m_BackMaterial)
		m_BackMaterial = com.m_BackMaterial->Clone();
}

CTileMapComponent::~CTileMapComponent()
{
}

void CTileMapComponent::SetMaterial(CMaterial* Material)
{
	m_BackMaterial = Material->Clone();

	m_BackMaterial->SetScene(m_Scene);
}

void CTileMapComponent::SetBackBaseColor(const Vector4& Color)
{
	m_BackMaterial->SetBaseColor(Color);
}

void CTileMapComponent::SetBackBaseColor(float r, float g, float b, float a)
{
	m_BackMaterial->SetBaseColor(r, g, b, a);
}

void CTileMapComponent::SetBackRenderState(CRenderState* State)
{
	m_BackMaterial->SetRenderState(State);
}

void CTileMapComponent::SetBackRenderState(const std::string& Name)
{
	m_BackMaterial->SetRenderState(Name);
}

void CTileMapComponent::SetBackTransparency(bool Enable)
{
	m_BackMaterial->SetTransparency(Enable);
}

void CTileMapComponent::SetBackOpacity(float Opacity)
{
	m_BackMaterial->SetOpacity(Opacity);
}

void CTileMapComponent::AddBackOpacity(float Opacity)
{
	m_BackMaterial->AddOpacity(Opacity);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_BackMaterial->AddTexture(Register, ShaderType, Name, Texture);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_BackMaterial->AddTexture(Register, ShaderType, Name, FileName, PathName);
}

void CTileMapComponent::AddBackTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_BackMaterial->AddTextureFullPath(Register, ShaderType, Name, FullPath);
}

void CTileMapComponent::AddBackTexture(int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_BackMaterial->AddTexture(Register, ShaderType, Name, vecFileName, PathName);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, Texture);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, FileName, PathName);
}

void CTileMapComponent::SetBackTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name,
	const TCHAR* FullPath)
{
	m_BackMaterial->SetTextureFullPath(Index, Register, ShaderType, Name, FullPath);
}

void CTileMapComponent::SetBackTexture(int Index, int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_BackMaterial->SetTexture(Index, Register, ShaderType, Name, vecFileName, PathName);
}

void CTileMapComponent::Start()
{
	CSceneComponent::Start();
}

bool CTileMapComponent::Init()
{
	m_BackMesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	SetMaterial(m_Scene->GetResource()->FindMaterial("BaseTexture"));

	SetMeshSize(1.f, 1.f, 0.f);
	SetWorldScale((float)m_BackMaterial->GetTextureWidth(),
		(float)m_BackMaterial->GetTextureHeight(), 1.f);

	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CTileMapComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CTileMapComponent::Render()
{
	CSceneComponent::Render();

	m_BackMaterial->Render();

	m_BackMesh->Render();

	m_BackMaterial->Reset();
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

	m_BackMaterial->Save(File);

	CSceneComponent::Save(File);
}

void CTileMapComponent::Load(FILE* File)
{
	char	MeshName[256] = {};

	int	Length = 0;

	fread(&Length, sizeof(int), 1, File);
	fread(MeshName, sizeof(char), Length, File);

	m_BackMesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh(MeshName);

	m_BackMaterial = m_Scene->GetResource()->CreateMaterialEmpty<CMaterial>();

	m_BackMaterial->Load(File);

	CSceneComponent::Load(File);
}
