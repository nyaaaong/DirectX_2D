#pragma once
#include "../Shader/GraphicShader.h"
class CMaterial :
    public CRef
{
	friend class CMaterialManager;

protected:
	CMaterial();
	virtual ~CMaterial();

protected:
	CSharedPtr<CGraphicShader>	m_pShader;

public:
	void SetShader(const std::string& strName);

public:
	void Render();
};

