#include "Collision.h"

bool CCollision::CollisionBox2DToPoint(CollisionResult& SrcResult,
	CollisionResult& DestResult, const Box2DInfo& BoxInfo, const Vector2& Point)
{
	// ������ x, y �࿡ ���� �����Ͽ� ������ ��ġ���� �Ǵ��Ѵ�.
	Vector2	CenterDir = BoxInfo.Center - Point;

	Vector2	Axis = BoxInfo.Axis[0];

	float	CenterProjDist = abs(CenterDir.Dot(Axis));

	if (CenterProjDist > BoxInfo.Length.x)
		return false;

	Axis = BoxInfo.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	if (CenterProjDist > BoxInfo.Length.y)
		return false;

	return true;
}
