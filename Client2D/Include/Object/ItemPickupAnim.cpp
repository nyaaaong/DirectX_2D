
#include "ItemPickupAnim.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CItemPickupAnim::CItemPickupAnim()
{
	SetTypeID<CItemPickupAnim>();
}

CItemPickupAnim::CItemPickupAnim(const CItemPickupAnim& Anim)	:
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CItemPickupAnim>();
}

CItemPickupAnim::~CItemPickupAnim()
{
}

bool CItemPickupAnim::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation(TEXT("Item/Item_Pickup.sqc"), "Item_Pickup", ANIMATION_PATH, false, 0.3f);

	SetCurrentAnimation("Item_Pickup");

	Play();

	return true;
}

CItemPickupAnim* CItemPickupAnim::Clone()
{
	return DBG_NEW CItemPickupAnim(*this);
}
