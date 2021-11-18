#pragma once

#include "../Component/SceneComponent.h"
#include "../Component/ObjectComponent.h"

class CGameObject :
    public CRef
{
	friend class CScene;

protected:
	CGameObject();
	CGameObject(const CGameObject& obj);
	virtual ~CGameObject();

protected:
	class CScene* m_pScene;
	CSharedPtr<CSceneComponent>	m_pRootComponent;
	std::vector<CSharedPtr<CObjectComponent>>	m_vecObjectComponent;

public:
	void SetRootComponent(CSceneComponent* pSceneComponent)
	{
		m_pRootComponent = pSceneComponent;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

public:
	class CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CGameObject* Clone();

public:
	template <typename T>
	T* CreateComponent(const std::string& strName)
	{
		T* pComponent = new T;

		pComponent->SetName(strName);
		pComponent->SetScene(m_pScene);
		pComponent->SetGameObject(this);

		if (!pComponent->Init())
		{
			SAFE_RELEASE(pComponent);
			return nullptr;
		}

		if (pComponent->GetComponentType() == Component_Type::ObjectComponent)
			m_vecObjectComponent.push_back(pComponent);

		return pComponent;
	}
};

