
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	CMesh* SpriteMesh = new CSpriteMesh;

	if (!SpriteMesh->Init())
	{
		SpriteMesh->Release();
		return false;
	}

	m_mapMesh.insert(std::make_pair("SpriteMesh", SpriteMesh));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

void CMeshManager::ReleaseMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter != m_mapMesh.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}
