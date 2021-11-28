
#include "Texture.h"
#include "../../PathManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	size_t	Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTextureInfo[i]);
	}
}

bool CTexture::LoadTexture(const std::string& Name, const TCHAR* FileName, 
	const std::string& PathName)
{
	TextureResourceInfo* Info = new TextureResourceInfo;

	SetName(Name);

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR*	FullPath = new TCHAR[MAX_PATH];
	memset(FullPath, 0, sizeof(TCHAR) * MAX_PATH);

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	Info->FullPath = FullPath;



	m_vecTextureInfo.push_back(Info);

	return true;
}
