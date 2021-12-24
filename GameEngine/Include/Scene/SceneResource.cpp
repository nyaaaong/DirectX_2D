
#include "SceneResource.h"

CSceneResource::CSceneResource()	:
	m_Scene(nullptr)
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapMesh.begin();
		auto	iterEnd = m_mapMesh.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapMesh.erase(iter);

			CResourceManager::GetInst()->ReleaseMesh(Name);
		}
	}

	{
		auto	iter = m_mapShader.begin();
		auto	iterEnd = m_mapShader.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapShader.erase(iter);

			CResourceManager::GetInst()->ReleaseShader(Name);
		}
	}

	{
		auto	iter = m_mapTexture.begin();
		auto	iterEnd = m_mapTexture.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapTexture.erase(iter);

			CResourceManager::GetInst()->ReleaseTexture(Name);
		}
	}

	{
		auto	iter = m_mapMaterial.begin();
		auto	iterEnd = m_mapMaterial.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapMaterial.erase(iter);

			CResourceManager::GetInst()->ReleaseMaterial(Name);
		}
	}

	{
		auto	iter = m_mapSequence2D.begin();
		auto	iterEnd = m_mapSequence2D.end();

		for (; iter != iterEnd;)
		{
			std::string	Name = iter->first;

			iter = m_mapSequence2D.erase(iter);

			CResourceManager::GetInst()->ReleaseAnimationSequence2D(Name);
		}
	}
}

CMesh* CSceneResource::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
	{
		CMesh* Mesh = CResourceManager::GetInst()->FindMesh(Name);

		if (!Mesh)
			return nullptr;

		m_mapMesh.insert(std::make_pair(Name, Mesh));

		return Mesh;
	}

	return iter->second;
}

CShader* CSceneResource::FindShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter == m_mapShader.end())
	{
		CShader* Shader = CResourceManager::GetInst()->FindShader(Name);

		if (!Shader)
			return nullptr;

		m_mapShader.insert(std::make_pair(Name, Shader));

		return Shader;
	}

	return iter->second;
}

CMaterial* CSceneResource::FindMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter == m_mapMaterial.end())
	{
		CMaterial* Material = CResourceManager::GetInst()->FindMaterial(Name);

		if (!Material)
			return nullptr;

		m_mapMaterial.insert(std::make_pair(Name, Material));

		return Material;
	}

	return iter->second;
}

bool CSceneResource::LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		return false;

	m_mapTexture.insert(std::make_pair(Name, CResourceManager::GetInst()->FindTexture(Name)));

	return true;
}

CTexture* CSceneResource::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
	{
		CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		m_mapTexture.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return iter->second;
}

bool CSceneResource::CreateAnimationSequence2D(const std::string& Name,
	const std::string& TextureName, const TCHAR* FileName, const std::string& PathName)
{
	if (FindAnimationSequence2D(Name))
		return true;

	if (!CResourceManager::GetInst()->CreateAnimationSequence2D(Name, TextureName, FileName, PathName))
		return false;

	m_mapSequence2D.insert(std::make_pair(Name, CResourceManager::GetInst()->FindAnimationSequence2D(Name)));

	return true;
}

bool CSceneResource::CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const Vector2& Start, const Vector2& Size,
	int CountX, int InterX, int CountY, int InterY, const std::string& PathName)
{
	return CreateAnimationSequence2D(Name, TextureName, FileName, Start.x, Start.y, Size.x, Size.y, CountX, InterX, CountY, InterY, PathName);
}

bool CSceneResource::CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, float StartX, float StartY, float Width, float Height,
	int CountX, int InterX, int CountY, int InterY, const std::string& PathName)
{
	if (!CreateAnimationSequence2D(Name, TextureName, FileName, PathName))
		return false;

	if (CountY <= 1)
	{
		for (int i = 0; i < CountX; ++i)
		{
			if (i > 0 && InterX)
				AddAnimationSequence2DFrame(Name, StartX + (Width * i + InterX * i), StartY, Width, Height);

			else
				AddAnimationSequence2DFrame(Name, StartX + (Width * i), StartY, Width, Height);
		}
	}

	else
	{
		for (int i = 0; i < CountY; ++i)
		{
			for (int j = 0; j < CountX; ++j)
			{
				if (j > 0 && (InterX || InterY))
					AddAnimationSequence2DFrame(Name, StartX + (Width * j + InterX * j), StartY + (Height * i + InterY * i), Width, Height);

				else
					AddAnimationSequence2DFrame(Name, StartX + (Width * j), StartY + (Height * i), Width, Height);
			}
		}
	}

	return true;
}

void CSceneResource::AddAnimationSequence2DFrame(const std::string& Name, const Vector2& Start,
	const Vector2& Size)
{
	CAnimationSequence2D* Anim = FindAnimationSequence2D(Name);

	if (!Anim)
		return;

	Anim->AddFrame(Start, Size);
}

void CSceneResource::AddAnimationSequence2DFrame(const std::string& Name, float StartX,
	float StartY, float Width, float Height)
{
	CAnimationSequence2D* Anim = FindAnimationSequence2D(Name);

	if (!Anim)
		return;

	Anim->AddFrame(StartX, StartY, Width, Height);
}

CAnimationSequence2D* CSceneResource::FindAnimationSequence2D(const std::string& Name)
{
	auto	iter = m_mapSequence2D.find(Name);

	if (iter == m_mapSequence2D.end())
	{
		CAnimationSequence2D* Anim = CResourceManager::GetInst()->FindAnimationSequence2D(Name);

		if (!Anim)
			return nullptr;

		m_mapSequence2D.insert(std::make_pair(Name, Anim));

		return Anim;
	}

	return iter->second;
}

CAnimation2DConstantBuffer* CSceneResource::GetAnimation2DCBuffer() const
{
	return CResourceManager::GetInst()->GetAnimation2DCBuffer();
}

bool CSceneResource::CreateAnimationSequence2D(const std::string& Name,
	CTexture* Texture)
{
	if (FindAnimationSequence2D(Name))
		return true;

	if (!CResourceManager::GetInst()->CreateAnimationSequence2D(Name, Texture))
		return false;

	m_mapSequence2D.insert(std::make_pair(Name, CResourceManager::GetInst()->FindAnimationSequence2D(Name)));

	return true;
}

bool CSceneResource::SaveSequence2DFullPath(const std::string& Name, const char* FullPath)
{
	return CResourceManager::GetInst()->SaveSequence2DFullPath(Name, FullPath);
}

bool CSceneResource::LoadSequence2DFullPath(const char* FullPath)
{
	std::string	SequenceName;

	if (!CResourceManager::GetInst()->LoadSequence2DFullPath(SequenceName, FullPath, m_Scene))
		return false;

	if (FindAnimationSequence2D(SequenceName))
		return true;

	CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);

	m_mapSequence2D.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CSceneResource::LoadSequence2DFullPath(std::string& resultName, const char* FullPath)
{
	if (!CResourceManager::GetInst()->LoadSequence2DFullPath(resultName, FullPath, m_Scene))
		return false;

	if (FindAnimationSequence2D(resultName))
		return true;

	CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(resultName);

	m_mapSequence2D.insert(std::make_pair(resultName, Sequence));

	return true;
}

bool CSceneResource::SaveSequence2D(const std::string& Name, const char* FileName,
	const std::string& PathName)
{
	return CResourceManager::GetInst()->SaveSequence2D(Name, FileName, PathName);
}

bool CSceneResource::LoadSequence2D(const char* FileName, const std::string& PathName)
{
	std::string	SequenceName;

	if (!CResourceManager::GetInst()->LoadSequence2D(SequenceName, FileName, PathName, m_Scene))
		return false;

	if (FindAnimationSequence2D(SequenceName))
		return true;

	CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);

	m_mapSequence2D.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CSceneResource::LoadSequence2D(std::string& resultName, const char* FileName,
	const std::string& PathName)
{
	if (!CResourceManager::GetInst()->LoadSequence2D(resultName, FileName, PathName, m_Scene))
		return false;

	if (FindAnimationSequence2D(resultName))
		return true;

	CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(resultName);

	m_mapSequence2D.insert(std::make_pair(resultName, Sequence));

	return true;
}

void CSceneResource::ReleaseAnimationSequence2D(const std::string& Name)
{
	CResourceManager::GetInst()->ReleaseAnimationSequence2D(Name);

	auto	iter = m_mapSequence2D.find(Name);

	if (iter != m_mapSequence2D.end())
		m_mapSequence2D.erase(iter);
}
