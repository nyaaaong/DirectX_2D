#pragma once

#include "GameObject/GameObject.h"
#include "Component/TileMapComponent.h"

class CTileMap :
    public CGameObject
{
    friend class CScene;

protected:
    CTileMap();
    CTileMap(const CTileMap& obj);
    virtual ~CTileMap();

private:
    CSharedPtr<CTileMapComponent>    m_TileMap;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CTileMap* Clone();
};

