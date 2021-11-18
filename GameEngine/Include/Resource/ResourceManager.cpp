
#include "ResourceManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()	:
	m_pMeshManager(nullptr),
	m_pShaderManager(nullptr)
{
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_pShaderManager);
	SAFE_DELETE(m_pMeshManager);
}

bool CResourceManager::Init()
{
	m_pMeshManager = new CMeshManager;

	if (!m_pMeshManager->Init())
		return false;

	m_pShaderManager = new CShaderManager;

	if (!m_pShaderManager->Init())
		return false;

	return true;
}

CMesh* CResourceManager::FindMesh(const std::string& strName)
{
	return m_pMeshManager->FindMash(strName);
}

CShader* CResourceManager::FindShader(const std::string& strName)
{
	return m_pShaderManager->FindShader(strName);
}
