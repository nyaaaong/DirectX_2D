#pragma once

#include "../Ref.h"

class CSceneMode	:
	public CRef
{
	friend class CScene;

protected:
	CSceneMode();
	virtual ~CSceneMode();

protected:
	class CScene* m_Scene;
	CSharedPtr<class CGameObject> m_PlayerObject;
	bool		m_UseCamera;
	CharacterInfo		m_PlayerInfo;
	CharacterInfo		m_MonsterInfo[(int)Object_Type::Max];

public:
	void UseCamera(bool UseCamera = true)
	{
		m_UseCamera = UseCamera;
	}

public:
	const CharacterInfo& GetPlayerInfo()	const
	{
		return m_PlayerInfo;
	}

	const CharacterInfo& GetMonsterInfo(Object_Type MonsterType)	const
	{
		return m_MonsterInfo[(int)MonsterType];
	}

	bool IsUseCamera()	const
	{
		return m_UseCamera;
	}

	CSharedPtr<class CGameObject> GetPlayerObject()	const
	{
		return m_PlayerObject;
	}

public:
	void SetPlayerObject(class CGameObject* Obj);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
};

