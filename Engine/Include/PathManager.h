#pragma once

#include "GameInfo.h"

struct PathInfo
{
	TCHAR	cPath[MAX_PATH];
	char	cPathMultibyte[MAX_PATH];

	PathInfo()	:
		cPath{},
		cPathMultibyte{}
	{}
};

class CPathManager
{
private:
	std::unordered_map<std::string, PathInfo*>	m_mapPath;

public:
	bool Init();
	bool AddPath(const std::string& strName, const TCHAR* cPath, const std::string& strBaseName = ROOT_PATH);
	const PathInfo* FindPath(const std::string& strName);

	DECLARE_SINGLE(CPathManager)
};

