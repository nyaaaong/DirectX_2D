
#include "Material.h"
#include "../ResourceManager.h"

CMaterial::CMaterial() :
	m_BaseColor(Vector4::White)
{
	SetTypeID<CMaterial>();
}

CMaterial::CMaterial(const CMaterial& Material)
{
	*this = Material;

	m_RefCount = 0;
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetBaseColor(const Vector4& Color)
{
	m_BaseColor = Color;
}

void CMaterial::SetBaseColor(float r, float g, float b, float a)
{
	m_BaseColor = Vector4(r, g, b, a);
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::SetShader(const std::string& Name)
{
	m_Shader = (CGraphicShader*)CResourceManager::GetInst()->FindShader(Name);
}

void CMaterial::Render()
{
	if (m_Shader)
		m_Shader->SetShader();

	size_t	Size = m_TextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_TextureInfo[i].Texture->SetShader(m_TextureInfo[i].Register, m_TextureInfo[i].ShaderType, 0);
	}
}

void CMaterial::Reset()
{
	size_t	Size = m_TextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_TextureInfo[i].Texture->ResetShader(m_TextureInfo[i].Register, m_TextureInfo[i].ShaderType, 0);
	}
}

CMaterial* CMaterial::Clone()
{
	return new CMaterial(*this);
}
