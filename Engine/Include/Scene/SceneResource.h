#pragma once

#include "../GameInfo.h"
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
	class CScene* m_Scene;

private:
	std::unordered_map<std::string, CSharedPtr<CMesh>>		m_mapMesh;
	std::unordered_map<std::string, CSharedPtr<CShader>>	m_mapShader;
	std::unordered_map<std::string, CSharedPtr<CMaterial>>	m_mapMaterial;

public:	// =================== Mesh =====================


	CMesh* FindMesh(const std::string& Name);


public:	// =================== Shader =====================
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		if (FindShader(Name))
			return false;

		CResourceManager::GetInst()->CreateShader<T>(Name);

		m_mapShader.insert(std::make_pair(Name, CResourceManager::GetInst()->FindShader(Name)));

		return true;
	}
	CShader* FindShader(const std::string& Name);


public:	// =================== Material =====================
	CMaterial* FindMaterial(const std::string& Name);

public:
	template <typename T>
	bool CreateMaterial(const std::string& Name)
	{
		if (FindMaterial(Name))
			return false;

		CResourceManager::GetInst()->CreateMaterial<T>(Name);

		m_mapMaterial.insert(std::make_pair(Name, CResourceManager::GetInst()->FindMaterial(Name)));

		return true;
	}
};

