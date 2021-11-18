
#include "MaterialManager.h"

CMaterialManager::CMaterialManager()
{
}

CMaterialManager::~CMaterialManager()
{
}

CMaterial* CMaterialManager::FindMaterial(const std::string& strName)
{
	auto	iter = m_mapMaterial.find(strName);

	if (iter == m_mapMaterial.end())
		return nullptr;

	return iter->second;
}

void CMaterialManager::ReleaseMaterial(const std::string& strName)
{
	auto	iter = m_mapMaterial.find(strName);

	if (iter != m_mapMaterial.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMaterial.erase(iter);
	}
}

bool CMaterialManager::Init()
{
	CreateMaterial<CMaterial>("Color");

	CSharedPtr<CMaterial>	pMtrl = FindMaterial("Color");
	pMtrl->SetShader("ColorMeshShader");

	return true;
}
