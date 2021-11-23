
#include "GameObject.h"

CGameObject::CGameObject()	:
	m_Scene(nullptr)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& obj)
{
	*this = obj;

	m_RefCount = 0;
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
}

void CGameObject::PostUpdate(float DeltaTime)
{
}

void CGameObject::PrevRender()
{
}

void CGameObject::Render()
{
}

void CGameObject::PostRender()
{
}

CGameObject* CGameObject::Clone()
{
	return new CGameObject(*this);
}
