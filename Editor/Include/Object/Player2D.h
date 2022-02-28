#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CPlayer2D :
    public CGameObject
{
    friend class CScene;

protected:
    CPlayer2D();
    CPlayer2D(const CPlayer2D& obj);
    virtual ~CPlayer2D();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
	CAnimationSequence2DInstance* m_AnimInstance;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CPlayer2D* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void RotationZInv(float DeltaTime);
    void RotationZ(float DeltaTime);
};

