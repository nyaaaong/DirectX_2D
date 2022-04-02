#pragma once

#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"

class CBullet :
	public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& obj);
	virtual ~CBullet();

private:
	float			m_StartDistance;
	float			m_Distance;
	float			m_BulletSpeed;
	float			m_Damage;
	bool			m_Hit;
	bool			m_Pierce;
	bool			m_ImpactDestroyed;
	bool			m_ImpactCreated;
	bool			m_Check;
	bool			m_NeedDestroyCollider;
	bool			m_SetBulletSpeed;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CCharacter> m_Owner;
	class CBulletDummy* m_Impact;
	Character_Type	m_CharacterType;
	Weapon_Slot		m_WeaponSlot;
	Bullet_Type		m_BulletType;
	Vector3			m_BulletDir;

public:
	void SetBulletSpeed(float Speed)
	{
		m_SetBulletSpeed = true;

		m_BulletSpeed = Speed;
	}

	void SetBulletType(Bullet_Type Type)
	{
		m_BulletType = Type;
	}

	void Pierce(bool IsPierce)
	{
		m_Pierce = IsPierce;
	}

	void SetOwner(CSharedPtr<class CCharacter> Owner)
	{
		m_Owner = Owner;
	}

	void SetBulletDamage(float Damage)
	{
		m_Damage = Damage;
	}

	void SetWeaponSlot(Weapon_Slot Slot)
	{
		m_WeaponSlot = Slot;
	}

	void SetBulletDir(const Vector3& Dir)
	{
		m_BulletDir = Dir;
	}

	void SetCharacterType(Character_Type Type)
	{
		m_CharacterType = Type;
	}

public:
	void SetCollisionProfile(const std::string& Name);

public:
	virtual void Start();
	virtual void First();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone();
	virtual void Destroy();

public:
	void OnCollisionBegin(const CollisionResult& result);
	void OnCollisionEnd(const CollisionResult& result);

private:
	bool IsWallTile(const Vector3& NextPos);
	void CreateHitEffect();

private:
	void CheckFirstBullet(float Dist);
	void BulletUpdater(float Dist);
};