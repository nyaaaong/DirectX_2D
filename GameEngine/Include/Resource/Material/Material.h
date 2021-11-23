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
    CSharedPtr<CGraphicShader>  m_Shader;

public:
    void SetShader(const std::string& Name);
    void Render();
};

