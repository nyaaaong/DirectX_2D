
#include "SceneResource.h"

CSceneResource::CSceneResource()	:
	m_pScene(nullptr)
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapMesh.begin();
		auto	iterEnd = m_mapMesh.end();

		for (; iter != iterEnd;)
		{
			std::string	strName = iter->first;

			iter = m_mapMesh.erase(iter);

			CResourceManager::GetInst()->ReleaseMesh(strName);
		}
	}

	{
		auto	iter = m_mapShader.begin();
		auto	iterEnd = m_mapShader.end();

		for (; iter != iterEnd;)
		{
			std::string	strName = iter->first;

			iter = m_mapShader.erase(iter);

			CResourceManager::GetInst()->ReleaseShader(strName);
		}
	}

	{
		auto	iter = m_mapMaterial.begin();
		auto	iterEnd = m_mapMaterial.end();

		for (; iter != iterEnd;)
		{
			std::string	strName = iter->first;

			iter = m_mapMaterial.erase(iter);

			CResourceManager::GetInst()->ReleaseMaterial(strName);
		}
	}
}

CMesh* CSceneResource::FindMesh(const std::string& strName)
{
	auto	iter = m_mapMesh.find(strName);

	if (iter == m_mapMesh.end())
		return nullptr;

    return iter->second;
}

CShader* CSceneResource::FindShader(const std::string& strName)
{
	auto	iter = m_mapShader.find(strName);

	if (iter == m_mapShader.end())
		return nullptr;

	return iter->second;
}

CMaterial* CSceneResource::FindMaterial(const std::string& strName)
{
	auto	iter = m_mapMaterial.find(strName);

	if (iter == m_mapMaterial.end())
		return nullptr;

	return iter->second;
}
