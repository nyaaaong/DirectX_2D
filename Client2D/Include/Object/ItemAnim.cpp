
#include "ItemAnim.h"

CItemAnim::CItemAnim()	:
	m_PlayEnd(false)
{
	SetTypeID<CItemAnim>();
}

CItemAnim::CItemAnim(const CItemAnim& Anim)	:
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CItemAnim>();

	m_PlayEnd = false;
}

CItemAnim::~CItemAnim()
{
}

void CItemAnim::Start()
{
	CAnimationSequence2DInstance::Start();
}

bool CItemAnim::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation(TEXT("Item/Item_Pickup.sqc"), "Item_Pickup", ANIMATION_PATH);

	SetCurrentAnimation("Item_Pickup");

	return true;
}

void CItemAnim::Update(float DeltaTime)
{
	CAnimationSequence2DInstance::Update(DeltaTime);
}

CItemAnim* CItemAnim::Clone()
{
	return DBG_NEW CItemAnim(*this);
}
