#pragma once

#include "AnimationSequence2DData.h"

class CAnimationSequence2DInstance
{
public:
	CAnimationSequence2DInstance();
	CAnimationSequence2DInstance(const CAnimationSequence2DInstance& Anim);
	virtual ~CAnimationSequence2DInstance();

protected:
	size_t		m_TypeID;
	class CSpriteComponent* m_Owner;
	class CScene* m_Scene;
	std::unordered_map<std::string, CAnimationSequence2DData*>	m_mapAnimation;
	CAnimationSequence2DData* m_CurrentAnimation;
	class CAnimation2DConstantBuffer* m_CBuffer;
	bool		m_PlayAnimation;
	bool		m_AnimEnd;
	bool		m_First;

public:
	bool IsEnd()	const
	{
		return m_AnimEnd;
	}

	size_t GetTypeID()	const
	{
		return m_TypeID;
	}

	void SetScene(class CScene* Scene)
	{
		m_Scene = Scene;
	}

	void SetOwner(class CSpriteComponent* Owner)
	{
		m_Owner = Owner;
	}

	int GetAnimationCount()	const
	{
		return (int)m_mapAnimation.size();
	}

	void Play()
	{
		m_PlayAnimation = true;
	}

	void Stop()
	{
		m_PlayAnimation = false;
	}

	bool IsPlay()	const
	{
		return m_PlayAnimation;
	}

	CAnimationSequence2DData* GetCurrentAnimation()	const
	{
		return m_CurrentAnimation;
	}

public:
	void Save(FILE* File);
	void Load(FILE* File);
	void Save(const char* FullPath);
	void Load(const char* FullPath);

public:
	void AddAnimation(const std::string& SequenceName, const std::string& Name, bool Loop = true, float PlayTime = 1.f, float PlayScale = 1.f, bool Reverse = false);
	void AddAnimation(const TCHAR* FileName, const std::string& Name, const std::string& PathName = ANIMATION_PATH, bool Loop = true, float PlayTime = 1.f, float PlayScale = 1.f, bool Reverse = false);
	void DeleteAnimation(const std::string& Name);
	void ClearAnimation();
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetReverse(const std::string& Name, bool Reverse);
	void SetLoop(const std::string& Name, bool Loop);
	bool SetCurrentAnimation(const std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);

public:
	virtual void Start();
	virtual bool Init();
	virtual void First();
	virtual void Update(float DeltaTime);
	void SetShader();
	void ResetShader();
	virtual CAnimationSequence2DInstance* Clone();

private:
	CAnimationSequence2DData* FindAnimation(const std::string& Name);

public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void (T::* Func)())
	{
		CAnimationSequence2DData* Data = FindAnimation(Name);

		if (!Data)
			return;

		Data->SetEndFunction<T>(Obj, Func);
	}

public:
	template <typename T>
	void AddNotify(const std::string& Name, const std::string& NotifyName, int Frame,
		T* Obj, void (T::* Func)())
	{
		CAnimationSequence2DData* Data = FindAnimation(Name);

		if (!Data)
			return;

		Data->AddNotify<T>(NotifyName, Frame, Obj, Func);
	}

public:
	template <typename T>
	void SetTypeID()
	{
		m_TypeID = typeid(T).hash_code();
	}
};

