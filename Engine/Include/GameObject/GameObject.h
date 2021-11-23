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
    class CScene* m_Scene;

public:
    class CScene* GetScene()    const
    {
        return m_Scene;
    }

public:
    void SetScene(class CScene* Scene);

protected:
    CSharedPtr<CSceneComponent> m_RootComponent;
    std::vector<CSharedPtr<CObjectComponent>>   m_vecObjectComponent;

public:
    void SetRootComponent(CSceneComponent* Component)
    {
        m_RootComponent = Component;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CGameObject* Clone();

public:
    template <typename T>
    T* CreateComponent(const std::string& Name)
    {
        T* Component = new T;

        Component->SetName(Name);
        Component->SetScene(m_Scene);
        Component->SetGameObject(this);

        if (!Component->Init())
        {
            SAFE_RELEASE(Component);
            return nullptr;
        }

        if (Component->GetComponentType() == Component_Type::ObjectComponent)
            m_vecObjectComponent.push_back(Component);

        return Component;
    }
};

