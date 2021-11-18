#pragma once

#include "Mesh/MeshManager.h"
#include "Shader/ShaderManager.h"

class CResourceManager
{
private:
	CMeshManager* m_pMeshManager;
	CShaderManager* m_pShaderManager;

public:
	bool Init();

public:
	class CMesh* FindMesh(const std::string& strName);
	class CShader* FindShader(const std::string& strName);

	DECLARE_SINGLE(CResourceManager)

public:
	template <typename T>
	bool CreateShader(const std::string& strName)
	{
		return m_pShaderManager->CreateShader<T>(strName);
	}
};

