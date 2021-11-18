
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

void CMeshManager::ReleaseMesh(const std::string& strName)
{
	auto	iter = m_mapMesh.find(strName);

	if (iter != m_mapMesh.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}

CMesh* CMeshManager::FindMash(const std::string& strName)
{
	auto	iter = m_mapMesh.find(strName);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

bool CMeshManager::Init()
{
	CMesh* pSpriteMesh = new CSpriteMesh;

	if (!pSpriteMesh->Init())
	{
		SAFE_RELEASE(pSpriteMesh)
		return false;
	}

	m_mapMesh.insert(std::make_pair("SpriteMesh", pSpriteMesh));

	return true;
}
