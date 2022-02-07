#pragma once

#include "ObjectComponent.h"
#include "../Resource/Shader/PaperBurnConstantBuffer.h"

class CPaperBurnComponent :
    public CObjectComponent
{
    friend class CGameObject;

protected:
    CPaperBurnComponent();
    CPaperBurnComponent(const CPaperBurnComponent& com);
    virtual ~CPaperBurnComponent();

private:
    CPaperBurnConstantBuffer* m_CBuffer;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CPaperBurnComponent* Clone();
};

