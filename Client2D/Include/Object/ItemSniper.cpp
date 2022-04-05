
#include "ItemSniper.h"
#include "Component/SpriteComponent.h"

CItemSniper::CItemSniper()
{
	SetTypeID<CItemSniper>();
}

CItemSniper::CItemSniper(const CItemSniper& obj) :
	CItem(obj)
{
	SetTypeID<CItemSniper>();

	m_Sprite = (CSpriteComponent*)FindComponent("Sniper");
}

CItemSniper::~CItemSniper()
{
}

bool CItemSniper::Init()
{
	if (!CItem::Init())
		return false;

	m_Type = Item_Type::Sniper;

	m_Sprite = CreateComponent<CSpriteComponent>("Sniper");
	m_Sprite->SetRelativeScale(90.f, 27.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Sniper", TEXT("Item/Sniper.png"));

	m_Body->SetExtent(45.f, 13.5f);
	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->AddChild(m_Body);

	SetRootComponent(m_Sprite);

	return true;
}

CItemSniper* CItemSniper::Clone()
{
	return DBG_NEW CItemSniper(*this);
}