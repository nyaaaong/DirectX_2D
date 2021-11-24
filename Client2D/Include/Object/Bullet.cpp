
#include "Bullet.h"
#include "Component/SpriteComponent.h"

CBullet::CBullet()
{
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddRelativePos(GetWorldAxis(AXIS_Y) * 500.f * DeltaTime);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}
