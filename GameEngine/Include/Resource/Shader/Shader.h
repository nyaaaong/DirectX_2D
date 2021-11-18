#pragma once

#include "../../Ref.h"

class CShader :
	public CRef
{
	friend class CShaderManager;

protected:
	CShader();
	virtual ~CShader() = 0;

protected:
	Shader_Type	m_eType;

public:
	Shader_Type GetShaderType()	const
	{
		return m_eType;
	}

public:
	virtual void SetShader() = 0;

public:
	virtual bool Init() = 0;
};

