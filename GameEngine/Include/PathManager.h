#pragma once

#include "GameInfo.h"

struct PathInfo
{
	// TCHAR : 유니코드 문자열을 저장하기 위한 타입이다.
	// 단, 프로젝트가 Multibyte 문자열을 사용한다면 char 타입으로 정의된다.
	// 유니코드일 경우 wchar_t 로 정의된다.
	TCHAR	Path[MAX_PATH];
	char	PathMultibyte[MAX_PATH];

	PathInfo()	:
		Path{},
		PathMultibyte{}
	{
	}
};

class CPathManager
{
private:
	std::unordered_map<std::string, PathInfo*>	m_mapPath;

public:
	bool Init();
	bool AddPath(const std::string& Name, const TCHAR* Path,
		const std::string& BaseName = ROOT_PATH);
	const PathInfo* FindPath(const std::string& Name);

	DECLARE_SINGLE(CPathManager)
};

