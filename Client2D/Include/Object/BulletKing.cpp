
#include "BulletKing.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "../Widget/BossWidget.h"

CBulletKing::CBulletKing()	:
	m_BossUI(nullptr)
{
}

CBulletKing::CBulletKing(const CBulletKing& obj)	:
	CMonster(obj)
{
	m_BossWidget = (CWidgetComponent*)FindComponent("BossWidget");
	m_BossUI = nullptr;
}

CBulletKing::~CBulletKing()
{
}

void CBulletKing::Start()
{
	CMonster::Start();

	CSharedPtr<CSceneMode> SceneMode = CSceneManager::GetInst()->GetSceneMode();

	BossInfo	Info = SceneMode->GetBulletKingInfo();
	m_PrevHP = Info.HP;
	m_HP = Info.HP;
	m_HPMax = Info.HP;
	m_MoveSpeed = Info.MoveSpeed;
	m_Damage = Info.Damage;
}

bool CBulletKing::Init()
{
	if (!CMonster::Init())
		return false;

	m_BossWidget = CreateComponent<CWidgetComponent>("BossWidget");
	m_BossUI = m_BossWidget->CreateWidgetWindow<CBossWidget>("BossUI");

	m_Sprite->AddChild(m_BossWidget);

	m_UseDropItem = false;
	m_UseGun = false;
	m_UsePattern = true;

	return true;
}

void CBulletKing::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CBulletKing* CBulletKing::Clone()
{
	return DBG_NEW CBulletKing(*this);
}

void CBulletKing::Calc(float DeltaTime)
{
	CMonster::Calc(DeltaTime);
}

void CBulletKing::Destroy()
{
	CMonster::Destroy();
}

void CBulletKing::DestroyBefore()
{
	CMonster::DestroyBefore();
}

void CBulletKing::PlaySoundDie()
{
	CMonster::PlaySoundDie();
}

void CBulletKing::Attack(float DeltaTime)
{
	CMonster::Attack(DeltaTime);
}

void CBulletKing::UpdateStatus()
{
	if (m_HP != m_PrevHP)
		m_BossUI->SetPercent(m_HP / m_HPMax);
}
