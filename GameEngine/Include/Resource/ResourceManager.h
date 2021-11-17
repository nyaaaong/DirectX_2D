#pragma once

#include "../GameInfo.h"

class CResourceManager
{
private:
	std::unordered_map<std::string, CSharedPtr<class CMesh>>	m_mapMesh;

public:
	bool Init();

public:
	class CMesh* FindMesh(const std::string& strName);

	DECLARE_SINGLE(CResourceManager)
};

