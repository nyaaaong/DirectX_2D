#pragma once

#include "Component.h"
#include "Transform.h"

class CSceneComponent :
    public CComponent
{
    friend class CGameObject;

protected:
    CSceneComponent();
    CSceneComponent(const CSceneComponent& com);
    virtual ~CSceneComponent();

protected:
    CTransform* m_Transform;
    CSceneComponent* m_Parent;
    std::vector<CSharedPtr<CSceneComponent>>    m_vecChild;
    bool    m_Render;

public:
    virtual void SetScene(class CScene* Scene);
    virtual void SetGameObject(class CGameObject* Object);

public:
    void AddChild(CSceneComponent* Child);
    bool DeleteChild(CSceneComponent* Child);
    bool DeleteChild(const std::string& Name);
    CSceneComponent* FindComponent(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CSceneComponent* Clone();
};

