
#include "SpriteEditObject.h"
#include "Component/SpriteComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

CSpriteEditObject::CSpriteEditObject()
{
	int a = 0;
}

CSpriteEditObject::CSpriteEditObject(const CSpriteEditObject& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("SpriteEdit");
}

CSpriteEditObject::~CSpriteEditObject()
{
}

bool CSpriteEditObject::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("SpriteEdit");

	SetRootComponent(m_Sprite);

	//m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	//m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	//m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	//m_Sprite->GetAnimationInstance()->Stop();

	return true;
}

void CSpriteEditObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSpriteEditObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSpriteEditObject* CSpriteEditObject::Clone()
{
	return DBG_NEW CSpriteEditObject(*this);
}
