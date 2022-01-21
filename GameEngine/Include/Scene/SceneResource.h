#pragma once

#include "../GameInfo.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Shader.h"
#include "../Resource/Material/Material.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence2D.h"
#include "../Resource/Sound/Sound.h"

class CSceneResource
{
	friend class CScene;

private:
	CSceneResource();
	~CSceneResource();

private:
	class CScene* m_Scene;

private:
	std::unordered_map<std::string, CSharedPtr<CMesh>>		m_mapMesh;
	std::unordered_map<std::string, CSharedPtr<CShader>>	m_mapShader;
	std::unordered_map<std::string, CSharedPtr<CMaterial>>	m_mapMaterial;
	std::unordered_map<std::string, CSharedPtr<CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence2D>>	m_mapSequence2D;
	std::unordered_map<std::string, CSharedPtr<CSound>>		m_mapSound;

public:
	int GetSequence2DSize()	const
	{
		return (int)m_mapSequence2D.size();
	}

public:	// =================== Mesh =====================
	CMesh* FindMesh(const std::string& Name);
	CShader* FindShader(const std::string& Name);

public:	// =================== Material =====================
	CMaterial* FindMaterial(const std::string& Name);

public:	// =================== Sequence2D =====================
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	// Count는 이미지(애니메이션)의 프레임 가로, 세로 개수를 뜻하고, Inter는 이미지 간격 가로, 세로 크기를 말한다.
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const Vector2& Start, const Vector2& Size, int CountX, int InterX = 0, int CountY = 0, int InterY = 0, 
		const std::string& PathName = TEXTURE_PATH);
	// Count는 이미지(애니메이션)의 프레임 가로, 세로 개수를 뜻하고, Inter는 이미지 간격 가로, 세로 크기를 말한다.
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, float StartX, float StartY, float Width, float Height, int CountX, int InterX = 0, int CountY = 0, int InterY = 0, 
		const std::string& PathName = TEXTURE_PATH);
	void AddAnimationSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& Size);
	void AddAnimationSequence2DFrame(const std::string& Name, float StartX, float StartY, float Width, float Height);
	CAnimationSequence2D* FindAnimationSequence2D(const std::string& Name);
	class CAnimation2DConstantBuffer* GetAnimation2DCBuffer()	const;
	bool CreateAnimationSequence2D(const std::string& Name, class CTexture* Texture);
	bool SaveSequence2D(const std::string& Name, const char* FileName, const std::string& PathName = ANIMATION_PATH);
	bool SaveSequence2DFullPath(const std::string& Name, const char* FullPath);
	bool LoadSequence2D(const char* FileName, const std::string& PathName = ANIMATION_PATH);
	bool LoadSequence2D(std::string& resultName, const char* FileName, const std::string& PathName = ANIMATION_PATH);
	bool LoadSequence2DFullPath(const char* FullPath);
	bool LoadSequence2DFullPath(std::string& resultName, const char* FullPath);
	bool LoadSequence2DFullPath(std::string& resultName, TCHAR* resultSpritePath, const char* FullPath);
	void ReleaseAnimationSequence2D(const std::string& Name);

public:	// =================== Texture =====================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool LoadTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath);
	class CTexture* FindTexture(const std::string& Name);

public:	// =================== Sound =====================
	bool LoadSound(const std::string& ChannelGroupName, bool Loop, const std::string& Name, const char* FileName, const std::string& PathName = SOUND_PATH);
	bool CreateSoundChannelGroup(const std::string& Name);
	bool SetVolume(int Volume);
	bool SetVolume(const std::string& ChannelGroupName, int Volume);
	bool SoundPlay(const std::string& Name);
	bool SoundStop(const std::string& Name);
	bool SoundPause(const std::string& Name);
	bool SoundResume(const std::string& Name);
	class CSound* FindSound(const std::string& Name);
	FMOD::ChannelGroup* FindChannelGroup(const std::string& Name);

public:
	template <typename T>
	bool CreateMaterial(const std::string& Name)
	{
		if (FindMaterial(Name))
			return true;

		if (!CResourceManager::GetInst()->CreateMaterial<T>(Name))
			return false;

		m_mapMaterial.insert(std::make_pair(Name, CResourceManager::GetInst()->FindMaterial(Name)));

		return true;
	}

public:
	template <typename T>
	T* CreateMaterialEmpty()
	{
		return CResourceManager::GetInst()->CreateMaterialEmpty<T>();
	}

public:	// =================== Shader =====================
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		if (FindShader(Name))
			return true;

		if (!CResourceManager::GetInst()->CreateShader<T>(Name))
			return false;

		m_mapShader.insert(std::make_pair(Name, CResourceManager::GetInst()->FindShader(Name)));

		return true;
	}
};

