#pragma once
#include "Shader.h"
class CComputeShader :
    public CShader
{
protected:
	CComputeShader();
	virtual ~CComputeShader() = 0;

public:
	virtual void SetShader();

public:
	virtual bool Init() = 0;
};

