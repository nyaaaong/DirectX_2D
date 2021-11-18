#pragma once

#include "../../GameInfo.h"
#include "Material.h"

class CMaterialManager
{
	friend class CResourceManager;

private:
	CMaterialManager();
	~CMaterialManager();

private:
	std::unordered_map<std::string, CSharedPtr<CMaterial>>	m_mapMaterial;

public:
	CMaterial* FindMaterial(const std::string& strName);
	void ReleaseMaterial(const std::string& strName);

public:
	bool Init();

public:
	template <typename T>
	bool CreateMaterial(const std::string& strName)
	{
		T* pMaterial = (T*)FindMaterial(strName);

		if (pMaterial)
			return false;

		pMaterial = new T;
		pMaterial->SetName(strName);

		m_mapMaterial.insert(std::make_pair(strName, pMaterial));

		return true;
	}
};

