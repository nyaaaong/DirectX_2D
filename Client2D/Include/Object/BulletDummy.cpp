
#include "BulletDummy.h"
#include "BulletAnim.h"
#include "Component/SpriteComponent.h"

CBulletDummy::CBulletDummy()	:
	m_HitObject(false)
{
}

CBulletDummy::CBulletDummy(const CBulletDummy& obj)	:
	CGameObject(obj)
{
	m_HitObject = obj.m_HitObject;
}

CBulletDummy::~CBulletDummy()
{
}

bool CBulletDummy::IsAnimEnd() const
{
	return m_Sprite->GetAnimationInstance()->IsEnd();
}

bool CBulletDummy::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("BulletImpactSprite");
	m_Sprite->CreateAnimationInstance<CBulletAnim>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	SetRootComponent(m_Sprite);

	return true;
}

void CBulletDummy::First()
{
	CGameObject::First();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();
	CBulletAnim* Convert = dynamic_cast<CBulletAnim*>(Anim);

	if (!Convert)
		ASSERT("if (!Convert)");

	Convert->HitObject(m_HitObject);
}

void CBulletDummy::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBulletDummy::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBulletDummy* CBulletDummy::Clone()
{
	return DBG_NEW CBulletDummy(*this);
}