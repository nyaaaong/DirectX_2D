
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
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
