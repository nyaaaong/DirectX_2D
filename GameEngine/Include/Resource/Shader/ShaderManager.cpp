
#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "ConstantBuffer.h"

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}

bool CShaderManager::Init()
{
	if (!CreateShader<CColorMeshShader>("ColorMeshShader"))
		return false;




	// =================== ������� ===================
	CreateConstantBuffer("TransformCBuffer", sizeof(TransformCBuffer), 0,
		(int)ConstantBuffer_Shader_Type::Graphic);

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter == m_mapShader.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto	iter = m_mapShader.find(Name);

	if (iter != m_mapShader.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapShader.erase(iter);
	}
}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, 
	int ConstantBufferShaderType)
{
	CConstantBuffer* Buffer = FindConstantBuffer(Name);

	if (Buffer)
		return true;

	Buffer = new CConstantBuffer;

	Buffer->SetName(Name);

	if (!Buffer->Init(Size, Register, ConstantBufferShaderType))
	{
		SAFE_RELEASE(Buffer);
		return false;
	}

	m_mapConstantBuffer.insert(std::make_pair(Name, Buffer));

	return true;
}

CConstantBuffer* CShaderManager::FindConstantBuffer(const std::string& Name)
{
	auto	iter = m_mapConstantBuffer.find(Name);

	if (iter == m_mapConstantBuffer.end())
		return nullptr;

	return iter->second;
}
