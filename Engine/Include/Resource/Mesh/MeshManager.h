#pragma once

#include "../../GameInfo.h"

class CMeshManager
{
	friend class CResourceManager;

private:
	CMeshManager();
	~CMeshManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CMesh>>	m_mapMesh;

public:
	void ReleaseMesh(const std::string& strName);

public:
	class CMesh* FindMash(const std::string& strName);

public:
	bool Init();
};

