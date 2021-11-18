#pragma once

#include "../../GameInfo.h"

class CShaderManager
{
	friend class CResourceManager;

private:
	CShaderManager();
	~CShaderManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CShader>>	m_mapShader;

public:
	class CShader* FindShader(const std::string& strName);

public:
	bool Init();

public:
	template <typename T>
	bool CreateShader(const std::string& strName)
	{
		T* pShader = (T*)FindShader(strName);

		if (pShader)
			return false;

		pShader = new T;

		if (!pShader->Init())
		{
			SAFE_RELEASE(pShader);
			return false;
		}

		m_mapShader.insert(std::make_pair(strName, pShader));

		return true;
	}
};

