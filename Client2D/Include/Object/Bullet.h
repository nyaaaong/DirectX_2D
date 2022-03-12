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
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_ImpactSprite;
	float								m_StartDistance;
	float								m_Distance;
	CSharedPtr<class CColliderBox2D>	m_Body;
	Character_Type	m_CharacterType;
	Vector3			m_BulletDir;
	bool			m_First;
	float			m_BulletSpeed;
	Weapon_Slot		m_WeaponSlot;
	std::string		m_SoundName;
	bool			m_StartAnim;

public:
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
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone();

public:
	void OnCollisionBegin(const CollisionResult& result);
	void OnCollisionEnd(const CollisionResult& result);

private:
	bool IsNormalTile(const Vector3& NextWorldPos);
	void CreateBulletImpact();
};

