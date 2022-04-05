
#include "ItemLife.h"
#include "Component/SpriteComponent.h"

CItemLife::CItemLife()
{
	SetTypeID<CItemLife>();
}

CItemLife::CItemLife(const CItemLife& obj) :
	CItem(obj)
{
	SetTypeID<CItemLife>();

	m_Sprite = (CSpriteComponent*)FindComponent("Life");
}

CItemLife::~CItemLife()
{
}

bool CItemLife::Init()
{
	if (!CItem::Init())
		return false;

	m_Type = Item_Type::Life;

	m_Sprite = CreateComponent<CSpriteComponent>("Life");
	m_Sprite->SetRelativeScale(39.f, 33.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Life", TEXT("Item/Life.png"));

	m_Body->SetExtent(19.5f, 16.5f);
	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->AddChild(m_Body);

	SetRootComponent(m_Sprite);

	return true;
}

CItemLife* CItemLife::Clone()
{
	return DBG_NEW CItemLife(*this);
}
