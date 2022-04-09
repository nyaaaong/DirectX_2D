
#include "Dummy.h"

CDummy::CDummy()
{
}

CDummy::CDummy(const CDummy& obj)	:
	CGameObject(obj)
{
}

CDummy::~CDummy()
{
}

void CDummy::Start()
{
	CGameObject::Start();
}

bool CDummy::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Body = CreateComponent<CColliderBox2D>(GetName());

	SetRootComponent(m_Body);

	return true;
}

void CDummy::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CDummy* CDummy::Clone()
{
	return DBG_NEW CDummy(*this);
}
