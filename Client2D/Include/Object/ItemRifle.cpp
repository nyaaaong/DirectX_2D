
#include "ItemRifle.h"
#include "Component/SpriteComponent.h"

CItemRifle::CItemRifle()
{
	SetTypeID<CItemRifle>();
}

CItemRifle::CItemRifle(const CItemRifle& obj)	:
	CItem(obj)
{
	SetTypeID<CItemRifle>();

	m_Sprite = (CSpriteComponent*)FindComponent("Rifle");
}

CItemRifle::~CItemRifle()
{
}

bool CItemRifle::Init()
{
	if (!CItem::Init())
		return false;

	m_Type = Item_Type::Rifle;

	m_Sprite = CreateComponent<CSpriteComponent>("Rifle");
	m_Sprite->SetRelativeScale(81.f, 21.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Rifle", TEXT("Item/Rifle.png"));

	m_Body->SetExtent(40.5f, 10.5f);
	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->AddChild(m_Body);

	SetRootComponent(m_Sprite);

	return true;
}

CItemRifle* CItemRifle::Clone()
{
	return DBG_NEW CItemRifle(*this);
}
