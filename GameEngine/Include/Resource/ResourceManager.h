#pragma once

#include "Mesh/MeshManager.h"
#include "Shader/ShaderManager.h"
#include "Material/MaterialManager.h"
#include "Texture/TextureManager.h"

class CResourceManager
{
private:
	CMeshManager* m_MeshManager;
	CShaderManager* m_ShaderManager;
	CMaterialManager* m_MaterialManager;
	CTextureManager* m_TextureManager;

public:
	bool Init();

public:	// =================== Mesh =====================


	class CMesh* FindMesh(const std::string& Name);

	void ReleaseMesh(const std::string& Name);

	
public:	// =================== Shader =====================
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		return m_ShaderManager->CreateShader<T>(Name);
	}
	class CShader* FindShader(const std::string& Name);

	void ReleaseShader(const std::string& Name);

	bool CreateConstantBuffer(const std::string& Name, int Size, int Register,
		int ConstantBufferShaderType = (int)ConstantBuffer_Shader_Type::All);

	class CConstantBuffer* FindConstantBuffer(const std::string& Name);


public:	// =================== Material =====================
	CMaterial* FindMaterial(const std::string& Name);

	void ReleaseMaterial(const std::string& Name);

public:	// =================== Texture =====================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);

public:
	template <typename T>
	bool CreateMaterial(const std::string& Name)
	{
		return m_MaterialManager->CreateMaterial<T>(Name);
	}

	DECLARE_SINGLE(CResourceManager)
};
