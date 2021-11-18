#pragma once

#include "../Ref.h"

class CComponent :
    public CRef
{
	friend class CGameObject;

protected:
	CComponent();
	CComponent(const CComponent& com);
	virtual ~CComponent() = 0;

protected:
	class CScene* m_pScene;
	class CGameObject* m_pObject;
	Component_Type	m_eComponentType;

public:
	Component_Type GetComponentType()	const
	{
		return m_eComponentType;
	}

	class CGameObject* GetGameObject()	const
	{
		return m_pObject;
	}

	class CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetGameObject(class CGameObject* pObject)
	{
		m_pObject = pObject;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime) = 0;
	virtual void PostUpdate(float fTime) = 0;
	virtual void PrevRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual CComponent* Clone() = 0;
};

