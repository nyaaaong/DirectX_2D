
#include "Item.h"
#include "Player2D.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneMode.h"

CItem::CItem()
{
	SetTypeID<CItem>();
}

CItem::CItem(const CItem& obj)	:
	CGameObject(obj)
{
	SetTypeID<CItem>();

	m_Body = (CColliderBox2D*)FindComponent("Body");
}

CItem::~CItem()
{
}

void CItem::Start()
{
	CGameObject::Start();

	CGameObject* Obj = CSceneManager::GetInst()->GetSceneMode()->GetPlayerObject();

	if (!Obj)
		ASSERT("if (!Obj)");

	m_Player = dynamic_cast<CPlayer2D*>(Obj);

	if (!m_Player)
		ASSERT("if (!m_Player)");
}

bool CItem::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->UseMouseCollision(false);

	return true;
}

CItem* CItem::Clone()
{
	return DBG_NEW CItem(*this);
}

void CItem::Destroy()
{
	CGameObject::Destroy();
}

void CItem::OnCollisionBegin(const CollisionResult& result)
{
	CGameObject::Destroy();
}
