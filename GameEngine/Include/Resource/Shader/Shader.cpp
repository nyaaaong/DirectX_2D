
#include "Shader.h"

CShader::CShader()	:
	m_Type(Shader_Type::Compute)
{
}

CShader::CShader(const CShader& shader)
{
	*this = shader;
	m_RefCount = 0;
}

CShader::~CShader()
{
}
