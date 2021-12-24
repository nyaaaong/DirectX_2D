#pragma once

#include "Mesh/MeshManager.h"
#include "Shader/ShaderManager.h"
#include "Material/MaterialManager.h"
#include "Texture/TextureManager.h"
#include "Animation/AnimationManager.h"

class CResourceManager
{
private:
	CMeshManager* m_MeshManager;
	CShaderManager* m_ShaderManager;
	CMaterialManager* m_MaterialManager;
	CTextureManager* m_TextureManager;
	CAnimationManager* m_AnimationManager;

public:
	bool Init();

public:	// =================== Mesh =====================


	class CMesh* FindMesh(const std::string& Name);

	void ReleaseMesh(const std::string& Name);

	
public:// =================== Shader =====================
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
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);

public:	// =================== Sequence2D =====================
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	// Count는 이미지(애니메이션)의 프레임 가로, 세로 개수를 뜻하고, Inter는 이미지 간격 가로, 세로 크기를 말한다.
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const Vector2& Start, const Vector2& Size,
		int CountX, int InterX = 0, int CountY = 0, int InterY = 0, const std::string& PathName = TEXTURE_PATH);
	// Count는 이미지(애니메이션)의 프레임 가로, 세로 개수를 뜻하고, Inter는 이미지 간격 가로, 세로 크기를 말한다.
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, float StartX, float StartY, float Width, float Height,
		int CountX, int InterX = 0, int CountY = 0, int InterY = 0, const std::string& PathName = TEXTURE_PATH);
	void AddAnimationSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& Size);
	void AddAnimationSequence2DFrame(const std::string& Name, float StartX, float StartY, float Width, float Height);
	CAnimationSequence2D* FindAnimationSequence2D(const std::string& Name);
	void ReleaseAnimationSequence2D(const std::string& Name);
	class CAnimation2DConstantBuffer* GetAnimation2DCBuffer()	const;
	bool CreateAnimationSequence2D(const std::string& Name, class CTexture* Texture);
	bool SaveSequence2DFullPath(const std::string& Name, const char* FullPath);
	bool LoadSequence2DFullPath(std::string& resultName, const char* FullPath, class CScene* Scene = nullptr);
	bool LoadSequence2DFullPath(const char* FullPath, class CScene* Scene = nullptr);
	bool SaveSequence2D(const std::string& Name, const char* FileName, const std::string& PathName = ANIMATION_PATH);
	bool LoadSequence2D(const char* FileName, const std::string& PathName = ANIMATION_PATH, class CScene* Scene = nullptr);
	bool LoadSequence2D(std::string& resultName, const char* FileName, const std::string& PathName = ANIMATION_PATH, class CScene* Scene = nullptr);

public:
	DECLARE_SINGLE(CResourceManager)

	template <typename T>
	bool CreateMaterial(const std::string& Name)
	{
		return m_MaterialManager->CreateMaterial<T>(Name);
	}

public:
	template <typename T>
	T* CreateMaterialEmpty()
	{
		return m_MaterialManager->CreateMaterialEmpty<T>();
	}

public:
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		return m_ShaderManager->CreateShader<T>(Name);
	}
};
