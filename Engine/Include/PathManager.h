#pragma once

#include "GameInfo.h"

struct PathInfo
{
	// TCHAR : �����ڵ� ���ڿ��� �����ϱ� ���� Ÿ���̴�.
	// ��, ������Ʈ�� Multibyte ���ڿ��� ����Ѵٸ� char Ÿ������ ���ǵȴ�.
	// �����ڵ��� ��� wchar_t �� ���ǵȴ�.
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

