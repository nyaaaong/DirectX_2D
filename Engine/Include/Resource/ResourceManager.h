#pragma once

#include "Mesh/MeshManager.h"
#include "Shader/ShaderManager.h"
#include "Material/MaterialManager.h"

class CResourceManager
{
private:
	CMeshManager* m_pMeshManager;
	CShaderManager* m_pShaderManager;
	CMaterialManager* m_pMaterialManager;

public:
	void ReleaseMesh(const std::string& strName);
	void ReleaseShader(const std::string& strName);
	void ReleaseMaterial(const std::string& strName);

public:
	class CMesh* FindMesh(const std::string& strName);
	class CShader* FindShader(const std::string& strName);
	class CMaterial* FindMaterial(const std::string& strName);

public:
	bool Init();

	DECLARE_SINGLE(CResourceManager)

public:
	template <typename T>
	bool CreateMaterial(const std::string& strName)
	{
		return m_pMaterialManager->CreateMaterial<T>(strName);
	}

	template <typename T>
	bool CreateShader(const std::string& strName)
	{
		return m_pShaderManager->CreateShader<T>(strName);
	}
};

