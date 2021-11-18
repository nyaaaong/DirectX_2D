#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
	auto	iter = m_mapPath.begin();
	auto	iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CPathManager::Init()
{
	TCHAR	cPath[MAX_PATH] = {};

	// 현재 경로 + 실행파일.exe
	GetModuleFileName(0, cPath, MAX_PATH);

	unsigned int iLength = lstrlen(cPath);

	for (unsigned int i = iLength - 1; i > 0; --i)
	{
		if (cPath[i] == '\\')
		{
			memset(&cPath[i + 1], 0, sizeof(TCHAR) * (iLength - i - 1));
			break;
		}
	}

	PathInfo* pInfo = new PathInfo;

	lstrcpy(pInfo->cPath, cPath);

#ifdef UNICODE	
	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, cPath, -1, nullptr, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);
#else
	strcpy_s(pInfo->cPathMultibyte, cPath);
#endif // UNICODE

	m_mapPath.insert(std::make_pair(ROOT_PATH, pInfo));
	
	AddPath(SHADER_PATH, TEXT("Shader\\"));

    return true;
}

bool CPathManager::AddPath(const std::string& strName, const TCHAR* cPath, const std::string& strBaseName)
{
	if (FindPath(strName))
		return false;

	const PathInfo* pBaseInfo = FindPath(strBaseName);

	if (!pBaseInfo)
		return false;

	PathInfo* pInfo = new PathInfo;

	lstrcpy(pInfo->cPath, pBaseInfo->cPath);
	lstrcat(pInfo->cPath, cPath);

#ifdef UNICODE	
	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, nullptr, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, pInfo->cPath, -1, pInfo->cPathMultibyte, iConvertLength, 0, 0);
#else
	strcpy_s(pInfo->cPathMultibyte, cPath);
#endif // UNICODE

	m_mapPath.insert(std::make_pair(strName, pInfo));

    return true;
}

const PathInfo* CPathManager::FindPath(const std::string& strName)
{
	auto	iter = m_mapPath.find(strName);

	if (iter == m_mapPath.end())
		return nullptr;

    return iter->second;
}
