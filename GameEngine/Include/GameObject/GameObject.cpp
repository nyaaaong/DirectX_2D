
#include "GameObject.h"

CGameObject::CGameObject()	:
	m_pScene(nullptr)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& obj)
{
	*this = obj;

	m_iRefCount = 0;
}

CGameObject::~CGameObject()
{
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float fTime)
{
}

void CGameObject::PostUpdate(float fTime)
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
