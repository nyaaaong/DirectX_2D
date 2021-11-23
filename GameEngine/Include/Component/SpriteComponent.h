#pragma once

#include "SceneComponent.h"
#include "../Resource/Mesh/SpriteMesh.h"
#include "../Resource/Material/Material.h"

class CSpriteComponent :
    public CSceneComponent
{
    friend class CGameObject;

protected:
    CSpriteComponent();
    CSpriteComponent(const CSpriteComponent& com);
    virtual ~CSpriteComponent();

protected:
    CSharedPtr<CSpriteMesh> m_Mesh;
    CSharedPtr<CMaterial> m_Material;

public:
    void SetMaterial(CMaterial* Material)
    {
        m_Material = Material;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CSpriteComponent* Clone();
};

