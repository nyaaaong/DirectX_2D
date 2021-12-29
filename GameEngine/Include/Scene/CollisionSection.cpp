
#include "CollisionSection.h"
#include "../Component/ColliderComponent.h"
#include "../Input.h"

CCollisionSection::CCollisionSection()	:
	m_IndexX(0),
	m_IndexY(0),
	m_IndexZ(0),
	m_Index(0)
{
}

CCollisionSection::~CCollisionSection()
{
}

void CCollisionSection::Init(int IndexX, int IndexY, int IndexZ, int Index,
	const Vector3& Min, const Vector3& Max,
	const Vector3& SectionSize, const Vector3& SectionTotalSize)
{
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_IndexZ = IndexZ;
	m_Index = Index;
	m_Min = Min;
	m_Max = Max;
	m_SectionSize = SectionSize;
	m_SectionTotalSize = SectionTotalSize;

	m_vecCollider.reserve(100);
}

void CCollisionSection::Clear()
{
	m_vecCollider.clear();
}

void CCollisionSection::AddCollider(CColliderComponent* Collider)
{
	m_vecCollider.push_back(Collider);

	Collider->AddSectionIndex(m_Index);
}

void CCollisionSection::Collision(float DeltaTime)
{
}

CColliderComponent* CCollisionSection::CollisionMouse(bool Is2D, float DeltaTime)
{
	if (Is2D)
	{
		Vector2	MousePos = CInput::GetInst()->GetMouseWorld2DPos();

		size_t	Size = m_vecCollider.size();

		if (Size > 1)
			qsort(&m_vecCollider[0], Size, (size_t)sizeof(CColliderComponent*), CCollisionSection::SortY);

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecCollider[i]->CollisionMouse(MousePos))
				return m_vecCollider[i];
		}
	}

	else
	{
	}

	return nullptr;
}

int CCollisionSection::SortY(const void* Src, const void* Dest)
{
	CColliderComponent* SrcCollider = *((CColliderComponent**)Src);
	CColliderComponent* DestCollider = *((CColliderComponent**)Dest);

	if (SrcCollider->GetMin().y < DestCollider->GetMin().y)
		return -1;

	else if (SrcCollider->GetMin().y > DestCollider->GetMin().y)
		return 1;

	return 0;
}
