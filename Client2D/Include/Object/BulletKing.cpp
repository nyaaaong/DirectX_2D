
#include "BulletKing.h"
#include "Bullet.h"
#include "BulletKingAnim.h"
#include "BulletKingChairAnim.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "../Scene/MainScene.h"

CBulletKing::CBulletKing()	:
	m_MainScene(nullptr),
	m_ChairAnimInst(nullptr),
	m_ChairInvisible(false),
	m_ChairAlpha(1.f),
	m_arrAngle{},
	m_BulletAngle(5.f),
	m_BulletCount(72),
	m_BulletType1(false),
	m_BulletType2(false),
	m_BurstCoolDownTimer(0.f),
	m_BurstCooldown(false),
	m_BurstTimer(0.f),
	m_BurstCoolDownTimerMax(0.f),
	m_BurstTimerMax(0.f)
{
	SetTypeID<CBulletKing>();
}

CBulletKing::CBulletKing(const CBulletKing& obj)	:
	CMonster(obj)
{
	SetTypeID<CBulletKing>();

	m_MainScene = nullptr;
	m_ChairAnimInst = nullptr;
	m_ChairInvisible = false;
	m_ChairAlpha = 1.f;

	memcpy_s(m_PatternTimeMax, sizeof(float) * (size_t)BulletKing_State::Max, obj.m_PatternTimeMax, sizeof(float) * (size_t)BulletKing_State::Max);

	memset(m_arrAngle, 0, sizeof(float) * 72);

	m_BulletAngle = obj.m_BulletAngle;

	m_BulletType1 = false;
	m_BulletType2 = false;

	m_BulletCount = obj.m_BulletCount;

	m_BurstCoolDownTimer = 0.f;
	m_BurstCoolDownTimerMax = obj.m_BurstCoolDownTimerMax;
	m_BurstCooldown = false;
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

	m_Sprite->CreateAnimationInstance<CBulletKingAnim>();

	m_Chair = CreateComponent<CSpriteComponent>("BulletKingChair");
	m_Chair->CreateAnimationInstance<CBulletKingChairAnim>();
	m_Chair->SetRelativePos(-2.f, 15.f, 0.f);
	m_Chair->SetPivot(0.5f, 0.5f, 0.f);
	m_Chair->SetLayerName("PrevDefault");
	m_Sprite->AddChild(m_Chair);

	m_ChairAnimInst = m_Chair->GetAnimationInstance();

	m_Body->SetPivot(0.5f, 0.5f, 0.f);
	m_Body->SetExtent(105.f, 117.f);

	m_UseDropItem = false;
	m_UseGun = false;
	m_UsePattern = true;

	m_UpdateSight = 3000.f;

	AddPattern(this, &CBulletKing::Pattern1);
	AddPattern(this, &CBulletKing::Pattern2);
	AddPattern(this, &CBulletKing::Pattern3_Start);
	AddPattern(this, &CBulletKing::Pattern4);

	AddConnectPattern(BulletKing_State::Pattern3_Start, this, &CBulletKing::Pattern3_Progress);
	AddConnectPattern(BulletKing_State::Pattern3_Progress, this, &CBulletKing::Pattern3_End);

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();
	CAnimationSequence2DInstance* ChairAnim = m_Chair->GetAnimationInstance();

	m_PatternTimeMax[(int)BulletKing_State::Idle] = 2.f;
	m_PatternTimeMax[(int)BulletKing_State::Die] = 2.f;
	m_PatternTimeMax[(int)BulletKing_State::Die_End] = 0.5f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern1] = 0.4f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern2] = 0.4f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern3_Start] = 0.4f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern3_Progress] = 3.f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern3_End] = 1.5f;
	m_PatternTimeMax[(int)BulletKing_State::Pattern4] = 1.5f;

	m_BurstTimerMax = 0.5f;
	m_BurstCoolDownTimerMax = 0.5f;

	m_IsBulletKing = true;

	return true;
}

void CBulletKing::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_ChairAnimInst)
	{
		CAnimationSequence2DData* Anim = m_ChairAnimInst->GetCurrentAnimation();

		int Index = Anim->GetCurrentFrame();

		m_ChairAnimSize = Anim->GetAnimationSequence()->GetFrameData(Index).Size;

		m_Chair->SetRelativeScale(m_ChairAnimSize.x, m_ChairAnimSize.y, 1.f);

		if (GetBulletKingState() != GetBulletKingPrevState())
		{
			if (GetBulletKingState() == BulletKing_State::Die)
				m_ChairInvisible = true;
		}
	}

	if (m_Chair && m_ChairInvisible)
	{
		m_ChairAlpha -= (DeltaTime * 0.5f);

		if (m_ChairAlpha <= 0.f)
		{
			m_ChairAlpha = 0.f;
			m_ChairInvisible = false;
		}

		m_Chair->SetOpacity(m_ChairAlpha);
	}

	UpdateStatus();
}

CBulletKing* CBulletKing::Clone()
{
	return DBG_NEW CBulletKing(*this);
}

void CBulletKing::Calc(float DeltaTime)
{
	CMonster::Calc(DeltaTime);

	m_MainScene = dynamic_cast<CMainScene*>(*(m_Scene->GetSceneMode()));
}

void CBulletKing::Destroy()
{
	CMonster::Destroy();

	m_MainScene->FadeOut();
}

void CBulletKing::Enable(bool Enable)
{
	CMonster::Enable(Enable);

	m_Body->Enable(Enable);
}

void CBulletKing::Hit(float DeltaTime)
{
	if (m_Type == Character_Type::Monster)
	{
		if (m_Hit)
		{
			m_HitEffectTime += DeltaTime;

			m_Sprite->SetBaseColor(Vector4::Red);
			m_Chair->SetBaseColor(Vector4::Red);

			// 히트 사운드 출력
			if (!m_IsPlayedHitSound)
			{
				m_IsPlayedHitSound = true;

				m_Scene->GetResource()->SoundPlay("Monster_Hit");
			}

			if (m_HitEffectTime >= m_HitEffectTimeMax)
			{
				m_Sprite->SetBaseColor(Vector4::White);
				m_Chair->SetBaseColor(Vector4::White);

				m_HitEffectTime = 0.f;
				m_Hit = false;
				m_IsPlayedHitSound = false;
			}
		}
	}
}

void CBulletKing::DestroyBefore()
{
	CMonster::DestroyBefore();
}

void CBulletKing::PlaySoundDie()
{
	CMonster::PlaySoundDie();
}

void CBulletKing::Pattern1(float DeltaTime)
{
	if (!m_AttackOncePattern1)
	{
		m_AttackOncePattern1 = true;
		m_Scene->GetResource()->SoundPlay("BulletKing_Pattern1");
		Pattern1Attack();
	}

	m_BulletKingPrevState = m_BulletKingState;

	m_BulletKingState = BulletKing_State::Pattern1;

	m_PatternTime[(int)BulletKing_State::Pattern1] += DeltaTime;

	if (m_Sprite->GetCurrentAnimation()->GetName() == "BulletKing_Pattern1")
	{
		if (m_Sprite->IsEnd())
		{
			m_NeedPatternChangeIdle = true;
			m_CurBossAnimComplete = true;
		}
	}

	if (m_PatternTime[(int)BulletKing_State::Pattern1] >= m_PatternTimeMax[(int)BulletKing_State::Pattern1])
	{
		m_PatternTime[(int)BulletKing_State::Pattern1] = 0.f;

		m_CurBossChairAnimComplete = true;
	}
}

void CBulletKing::Pattern2(float DeltaTime)
{
	if (!m_AttackOncePattern2)
	{
		m_AttackOncePattern2 = true;
		m_Scene->GetResource()->SoundPlay("BulletKing_Pattern2");
		Pattern2Attack();
	}

	m_BulletKingPrevState = m_BulletKingState;

	m_BulletKingState = BulletKing_State::Pattern2;

	m_PatternTime[(int)BulletKing_State::Pattern2] += DeltaTime;

	if (m_Sprite->GetCurrentAnimation()->GetName() == "BulletKing_Pattern2")
	{
		if (m_Sprite->IsEnd())
		{
			m_NeedPatternChangeIdle = true;
			m_CurBossAnimComplete = true;
		}
	}

	if (m_PatternTime[(int)BulletKing_State::Pattern2] >= m_PatternTimeMax[(int)BulletKing_State::Pattern2])
	{
		m_PatternTime[(int)BulletKing_State::Pattern2] = 0.f;

		m_CurBossChairAnimComplete = true;
	}
}

void CBulletKing::Pattern3_Start(float DeltaTime)
{
	m_BulletKingPrevState = m_BulletKingState;

	m_BulletKingState = BulletKing_State::Pattern3_Start;

	m_PatternTime[(int)BulletKing_State::Pattern3_Start] += DeltaTime;

	if (m_PatternTime[(int)BulletKing_State::Pattern3_Start] >= m_PatternTimeMax[(int)BulletKing_State::Pattern3_Start])
	{
		m_PatternTime[(int)BulletKing_State::Pattern3_Start] = 0.f;

		m_NeedConnectPatternChange = true;

		m_Scene->GetResource()->SoundPlay("BulletKing_Pattern3");
	}
}

void CBulletKing::Pattern3_Progress(float DeltaTime)
{
	m_BulletKingPrevState = m_BulletKingState;

	if (!m_AttackOncePattern3)
	{
		m_AttackOncePattern3 = true;
		Pattern3Attack();
	}

	m_BulletKingState = BulletKing_State::Pattern3_Progress;

	m_PatternTime[(int)BulletKing_State::Pattern3_Progress] += DeltaTime;

	m_BurstTimer += DeltaTime;

	m_BurstTimerMax = 0.5f;
	
	if (m_BurstTimer >= m_BurstTimerMax)
	{
		m_BurstTimer = 0.f;

		m_AttackOncePattern3 = false;
	}

	if (m_PatternTime[(int)BulletKing_State::Pattern3_Progress] >= m_PatternTimeMax[(int)BulletKing_State::Pattern3_Progress])
	{
		m_PatternTime[(int)BulletKing_State::Pattern3_Progress] = 0.f;

		m_NeedConnectPatternChange = true;
	}
}

void CBulletKing::Pattern3_End(float DeltaTime)
{
	m_BulletKingPrevState = m_BulletKingState;

	m_BulletKingState = BulletKing_State::Pattern3_End;

	m_PatternTime[(int)BulletKing_State::Pattern3_End] += DeltaTime;

	if (m_Sprite->GetCurrentAnimation()->GetName() == "BulletKing_Pattern3_End")
	{
		if (m_Sprite->IsEnd())
		{
			m_NeedPatternChangeIdle = true;
			m_CurBossAnimComplete = true;
		}
	}

	if (m_PatternTime[(int)BulletKing_State::Pattern3_End] >= m_PatternTimeMax[(int)BulletKing_State::Pattern3_End])
	{
		m_PatternTime[(int)BulletKing_State::Pattern3_End] = 0.f;

		m_CurBossChairAnimComplete = true;
	}
}

void CBulletKing::Pattern4(float DeltaTime)
{
	if (!m_AttackOncePattern4)
	{
		m_AttackOncePattern4 = true;
		m_Scene->GetResource()->SoundPlay("BulletKing_Pattern4");
		Pattern4Attack();
	}

	m_BulletKingPrevState = m_BulletKingState;

	m_BulletKingState = BulletKing_State::Pattern4;

	m_PatternTime[(int)BulletKing_State::Pattern4] += DeltaTime;

	if (m_Sprite->GetCurrentAnimation()->GetName() == "BulletKing_Pattern1")
	{
		if (m_Sprite->IsEnd())
		{
			m_NeedPatternChangeIdle = true;
			m_CurBossAnimComplete = true;
		}
	}

	if (m_PatternTime[(int)BulletKing_State::Pattern4] >= m_PatternTimeMax[(int)BulletKing_State::Pattern4])
	{
		m_PatternTime[(int)BulletKing_State::Pattern4] = 0.f;

		m_CurBossChairAnimComplete = true;
	}
}

void CBulletKing::Pattern1Attack()
{
	if (m_IsDied)
		return;

	m_BulletAngle = 5.f;
	m_BulletCount = 72;

	float	Angle[2] = {};

	for (int i = 0; i <= m_BulletCount; ++i)
	{
		if (Angle[0] < 180.f)
		{
			m_arrAngle[i] = Angle[0];
			Angle[0] += m_BulletAngle;
		}

		else if (Angle[1] > -180.f)
		{
			m_arrAngle[i] = Angle[1];
			Angle[1] -= m_BulletAngle;
		}

		m_arrDir[i] = Vector3::ConvertDir(m_arrAngle[i]);

		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);

		if (i != m_BulletCount)
			Bullet->SetBulletDir(m_arrDir[i]);

		else
			Bullet->SetBulletDir(Vector3(-1.f, 0.f, 0.f));

		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern1);
	}
}

void CBulletKing::Pattern2Attack()
{
	if (m_IsDied)
		return;

	m_arrAngle[0] = m_PlayerAngle + m_BulletAngle;
	m_arrAngle[1] = m_arrAngle[0] + m_BulletAngle;

	m_arrAngle[2] = m_PlayerAngle - m_BulletAngle;
	m_arrAngle[3] = m_arrAngle[2] - m_BulletAngle;

	for (int i = 0; i < 4; ++i)
	{
		m_arrDir[i] = Vector3::ConvertDir(m_arrAngle[i]);
	}

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);
	Bullet->SetBulletDir(m_PlayerDir);
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("MonsterAttack");
	Bullet->SetCharacterType(Character_Type::Monster);
	Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern2);

	for (int i = 0; i < 4; ++i)
	{
		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);
		Bullet->SetBulletDir(m_arrDir[i]);
		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern2);
	}
}

void CBulletKing::Pattern3Attack()
{
	if (m_IsDied)
		return;

	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	m_BurstCoolDownTimer += DeltaTime;

	if (m_BurstCoolDownTimer >= m_BurstCoolDownTimerMax)
	{
		m_BurstCoolDownTimer = 0.f;
		m_BurstCooldown = false;
	}

	if (m_BurstCooldown)
		return;

	m_BulletAngle = 15.f;
	m_BulletCount = 24;

	if (!m_BulletType1)
	{
		m_BulletType1 = true;
		m_BulletType2 = false;
	}

	else
	{
		m_BulletType1 = false;
		m_BulletType2 = true;
	}

	float	Angle[4] = {};

	for (int i = 0; i <= m_BulletCount; ++i)
	{
		if (m_BulletType1)
		{
			if (Angle[0] < 180.f)
			{
				m_arrAngle[i] = Angle[0];
				Angle[0] += m_BulletAngle;
			}

			else if (Angle[1] > -180.f)
			{
				m_arrAngle[i] = Angle[1];
				Angle[1] -= m_BulletAngle;
			}
		}

		else if (m_BulletType2)
		{
			if (Angle[2] < 180.f)
			{
				m_arrAngle[i] = Angle[2];
				Angle[2] += (m_BulletAngle + 2.f);
			}

			else if (Angle[3] > -180.f)
			{
				m_arrAngle[i] = Angle[3];
				Angle[3] -= (m_BulletAngle - 2.f);
			}
		}

		m_arrDir[i] = Vector3::ConvertDir(m_arrAngle[i]);

		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);

		if (i != m_BulletCount * 0.5f)
			Bullet->SetBulletDir(m_arrDir[i]);

		else
		{
			Bullet->SetBulletDir(Vector3(-1.f, 0.f, 0.f));
		}

		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern3);
	}
}

void CBulletKing::Pattern4Attack()
{
	if (m_IsDied)
		return;

	m_arrAngle[0] = m_PlayerAngle + m_BulletAngle;
	m_arrAngle[1] = m_arrAngle[0] + m_BulletAngle;
	m_arrAngle[2] = m_arrAngle[1] + m_BulletAngle;
	m_arrAngle[3] = m_arrAngle[2] + m_BulletAngle;

	m_arrAngle[4] = m_PlayerAngle - m_BulletAngle;
	m_arrAngle[5] = m_arrAngle[4] - m_BulletAngle;
	m_arrAngle[6] = m_arrAngle[5] - m_BulletAngle;
	m_arrAngle[7] = m_arrAngle[6] - m_BulletAngle;

	for (int i = 0; i < 8; ++i)
	{
		m_arrDir[i] = Vector3::ConvertDir(m_arrAngle[i]);
	}

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);
	Bullet->SetBulletDir(m_PlayerDir);
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("MonsterAttack");
	Bullet->SetCharacterType(Character_Type::Monster);
	Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern4);

	for (int i = 0; i < 8; ++i)
	{
		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);
		Bullet->SetBulletDir(m_arrDir[i]);
		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::BulletKing_Pattern4);
	}
}

void CBulletKing::UpdateStatus()
{
	if (m_HP != m_PrevHP)
		m_MainScene->SetPercent(m_HP / m_HPMax);
}
