#pragma once

#include "../GameInfo.h"

struct CollisionSectionInfo
{
	std::vector<class CCollisionSection*>	vecSection;
	Vector3	SectionSize;		// 영역 1칸의 크기
	Vector3	Center;				// 전체 영역에서의 중심
	Vector3	SectionTotalSize;	// 전체 영역 크기
	Vector3	Min;				// 전체 영역에서의 최소값
	Vector3	Max;				// 전체 영역에서의 최대값
	int		CountX;
	int		CountY;
	int		CountZ;

	CollisionSectionInfo() :
		CountX(1),
		CountY(1),
		CountZ(1)
	{
	}
};


class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_Scene;

private:
	CollisionSectionInfo* m_Section;

public:
	void Start();
	bool Init();
};

