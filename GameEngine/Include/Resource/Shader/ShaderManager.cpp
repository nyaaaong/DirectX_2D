#include "ShaderManager.h"
#include "ColorMeshShader.h"

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}

void CShaderManager::ReleaseShader(const std::string& strName)
{
	auto	iter = m_mapShader.find(strName);

	if (iter != m_mapShader.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapShader.erase(iter);
	}
}

CShader* CShaderManager::FindShader(const std::string& strName)
{
	auto	iter = m_mapShader.find(strName);

	if (iter == m_mapShader.end())
		return nullptr;

	return iter->second;
}

bool CShaderManager::Init()
{
	if (!CreateShader<CColorMeshShader>("ColorMeshShader"))
		return false;

	return true;
}
