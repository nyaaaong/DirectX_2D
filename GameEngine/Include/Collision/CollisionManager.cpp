
#include "CollisionManager.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("Object", Collision_Channel::Object, true);
	CreateProfile("Player", Collision_Channel::Player, true);
	CreateProfile("Monster", Collision_Channel::Monster, true);
	CreateProfile("AttackCheck", Collision_Channel::AttackCheck, true);
	CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack, true);
	CreateProfile("MonsterAttack", Collision_Channel::MonsterAttack, true);
	CreateProfile("Item", Collision_Channel::Item, true);
	CreateProfile("BossRoomStart", Collision_Channel::BossRoomStart, true);
	CreateProfile("BossRoomEnd", Collision_Channel::BossRoomEnd, true);

	SetCollisionState("Object", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("Object", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Object", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("Object", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("Object", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("Object", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("Player", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("Monster", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("AttackCheck", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("AttackCheck", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("PlayerAttack", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("MonsterAttack", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("Item", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("Item", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("BossRoomStart", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomStart", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	SetCollisionState("BossRoomEnd", Collision_Channel::Object, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::AttackCheck, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::Item, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::BossRoomStart, Collision_Interaction::Ignore);
	SetCollisionState("BossRoomEnd", Collision_Channel::BossRoomEnd, Collision_Interaction::Ignore);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, Collision_Channel Channel, bool Enable, Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	Profile = DBG_NEW CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->CollisionEnable = Enable;
	Profile->vecInteraction.resize((int)Collision_Channel::Max);

	for (int i = 0; i < (int)Collision_Channel::Max; ++i)
	{
		Profile->vecInteraction[i] = State;
	}
	
	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionState(const std::string& Name, Collision_Channel Channel, Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->vecInteraction[(int)Channel] = State;

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}
