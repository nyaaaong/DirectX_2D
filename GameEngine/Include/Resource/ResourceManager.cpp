
#include "ResourceManager.h"
#include "SpriteMesh.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

bool CResourceManager::Init()
{
	CMesh* pSpriteMesh = new CSpriteMesh;

	if (!pSpriteMesh->Init())
	{
		SAFE_RELEASE(pSpriteMesh);
		return false;
	}

	m_mapMesh.insert(std::make_pair("SpriteMesh", pSpriteMesh));

	return true;
}

CMesh* CResourceManager::FindMesh(const std::string& strName)
{
	auto	iter = m_mapMesh.find(strName);

	if (iter == m_mapMesh.end())
		return nullptr;

    return iter->second;
}
