#pragma once

#include "GameObject/GameObject.h"

class CTileMapSprite :
	public CGameObject
{
	friend class CScene;

protected:
	CTileMapSprite();
	CTileMapSprite(const CTileMapSprite& obj);
	virtual ~CTileMapSprite();

private:
	CSharedPtr<class CSpriteComponent>    m_Sprite;

public:
	class CSpriteComponent* GetSpriteComponent()    const
	{
		return m_Sprite;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTileMapSprite* Clone();
};

