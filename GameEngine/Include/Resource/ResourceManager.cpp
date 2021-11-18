
#include "ResourceManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()	:
	m_pMeshManager(nullptr),
	m_pShaderManager(nullptr),
	m_pMaterialManager(nullptr)
{
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_pMaterialManager);
	SAFE_DELETE(m_pShaderManager);
	SAFE_DELETE(m_pMeshManager);
}

void CResourceManager::ReleaseMesh(const std::string& strName)
{
	m_pMeshManager->ReleaseMesh(strName);
}

void CResourceManager::ReleaseShader(const std::string& strName)
{
	m_pShaderManager->ReleaseShader(strName);
}

void CResourceManager::ReleaseMaterial(const std::string& strName)
{
	m_pMaterialManager->ReleaseMaterial(strName);
}

CMesh* CResourceManager::FindMesh(const std::string& strName)
{
	return m_pMeshManager->FindMash(strName);
}

CShader* CResourceManager::FindShader(const std::string& strName)
{
	return m_pShaderManager->FindShader(strName);
}

CMaterial* CResourceManager::FindMaterial(const std::string& strName)
{
	return m_pMaterialManager->FindMaterial(strName);
}

bool CResourceManager::Init()
{
	m_pMeshManager = new CMeshManager;

	if (!m_pMeshManager->Init())
		return false;

	m_pShaderManager = new CShaderManager;

	if (!m_pShaderManager->Init())
		return false;

	m_pMaterialManager = new CMaterialManager;

	if (!m_pMaterialManager->Init())
		return false;

	return true;
}
