
#include "BulletKin.h"
#include "BulletKinAnim.h"
#include "Scene/Scene.h"

CBulletKin::CBulletKin()
{
	SetTypeID<CBulletKin>();
}

CBulletKin::CBulletKin(const CBulletKin& obj)	:
	CMonster(obj)
{
	SetTypeID<CBulletKin>();

	m_Sprite = (CSpriteComponent*)FindComponent("BulletKinSprite");
	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();
}

CBulletKin::~CBulletKin()
{
}

void CBulletKin::Start()
{
	CMonster::Start();
}

bool CBulletKin::Init()
{
	if (!CMonster::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("BulletKinSprite");

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTransparency(true);
	m_Sprite->AddChild(m_Body);

	m_Body->SetWorldPos(m_Sprite->GetWorldPos());
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBulletKin::OnCollisionBegin);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());
	m_PaperBurn->SetFinishCallback<CBulletKin>(this, &CBulletKin::PaperBurnEnd);

	SetRootComponent(m_Sprite);

	return true;
}

void CBulletKin::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CBulletKin* CBulletKin::Clone()
{
	return DBG_NEW CBulletKin(*this);
}

void CBulletKin::Destroy()
{
	CMonster::Destroy();
}

void CBulletKin::OnCollisionBegin(const CollisionResult& result)
{
	CMonster::OnCollisionBegin(result);
}

void CBulletKin::PaperBurnEnd()
{
	CMonster::PaperBurnEnd();
}

void CBulletKin::Dead()
{
	CMonster::Dead();
}

void CBulletKin::Hit(float DeltaTime)
{
	CMonster::Hit(DeltaTime);
}
