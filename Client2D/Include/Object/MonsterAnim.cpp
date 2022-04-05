
#include "MonsterAnim.h"
#include "Component/SpriteComponent.h"
#include "Monster.h"

CMonsterAnim::CMonsterAnim()	:
	m_OwnerObject(nullptr),
	m_PlayDieAnim(false)
{
	SetTypeID<CMonsterAnim>();
}

CMonsterAnim::CMonsterAnim(const CMonsterAnim& Anim) :
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CMonsterAnim>();

	m_OwnerObject = nullptr;
	m_PlayDieAnim = false;
}

CMonsterAnim::~CMonsterAnim()
{
	m_OwnerObject = nullptr;
}

void CMonsterAnim::Start()
{
	CAnimationSequence2DInstance::Start();

	Play();

	CGameObject* Owner = m_Owner->GetGameObject();

	m_OwnerObject = dynamic_cast<CMonster*>(Owner);

	if (!m_OwnerObject)
		ASSERT("if (!m_OwnerObject)");
}

bool CMonsterAnim::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	return true;
}

void CMonsterAnim::Update(float DeltaTime)
{
	CAnimationSequence2DInstance::Update(DeltaTime);

	ChangeAnimDir();
}

void CMonsterAnim::ChangeAnimDir()
{
	// 죽는 애니메이션이 실행됐었다면 방향을 바꾸지 않게 한다.
	if (m_PlayDieAnim)
		return;

	if (m_OwnerObject->GetPlayerDir().x < 0.f)
		ChangeAnimLeft();

	else
		ChangeAnimRight();
}

void CMonsterAnim::ChangeAnimLeft()
{
	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		break;
	case Monster_State::Walk:
		break;
	case Monster_State::Die:
		m_PlayDieAnim = true;
		break;
	}
}

void CMonsterAnim::ChangeAnimRight()
{
	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		break;
	case Monster_State::Walk:
		break;
	case Monster_State::Die:
		m_PlayDieAnim = true;
		break;
	}
}
