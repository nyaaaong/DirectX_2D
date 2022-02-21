
#include "TileMapSprite.h"
#include "Component/SpriteComponent.h"

CTileMapSprite::CTileMapSprite()
{
}

CTileMapSprite::CTileMapSprite(const CTileMapSprite& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("TileMapSprite");
}

CTileMapSprite::~CTileMapSprite()
{
}

bool CTileMapSprite::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("TileMapSprite");

	SetRootComponent(m_Sprite);
	
	return true;
}

void CTileMapSprite::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTileMapSprite::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTileMapSprite* CTileMapSprite::Clone()
{
	return DBG_NEW CTileMapSprite(*this);
}
