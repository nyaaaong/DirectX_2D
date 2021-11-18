#pragma once

#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Shader.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"

class CSceneResource
{
	friend class CScene;

private:
	CSceneResource();
	~CSceneResource();

private:
	std::unordered_map<std::string, CSharedPtr<CMesh>>	m_mapMesh;
	std::unordered_map<std::string, CSharedPtr<CShader>>	m_mapShader;
	std::unordered_map<std::string, CSharedPtr<CMaterial>>	m_mapMaterial;
	class CScene* m_pScene;

public:
	CMesh* FindMesh(const std::string& strName);
	CShader* FindShader(const std::string& strName);
	CMaterial* FindMaterial(const std::string& strName);

public:
	template <typename T>
	bool CreateMaterial(const std::string& strName)
	{
		if (FindMaterial(strName))
			return false;

		CResourceManager::GetInst()->CreateMaterial<CMaterial>(strName);

		m_mapMaterial.insert(std::make_pair(strName, CResourceManager::GetInst()->FindMaterial(strName)));

		return true;
	}

	template <typename T>
	bool CreateShader(const std::string& strName)
	{
		if (FindShader(strName))
			return false;

		CResourceManager::GetInst()->CreateShader<CShader>(strName);

		m_mapShader.insert(std::make_pair(strName, CResourceManager::GetInst()->FindShader(strName)));

		return true;
	}
};

