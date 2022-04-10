
#include "SceneMode.h"
#include "../Excel/ExcelManager.h"
#include "../GameObject/GameObject.h"

CSceneMode::CSceneMode()	:
	m_Scene(nullptr),
	m_UseCamera(true)
{
	SetTypeID<CSceneMode>();
}

CSceneMode::~CSceneMode()
{
}

void CSceneMode::SetPlayerObject(CGameObject* Obj)
{
	m_PlayerObject = Obj;
}

void CSceneMode::Start()
{
}

bool CSceneMode::Init()
{
	m_PlayerInfo = CExcelManager::GetInst()->GetPlayerInfo();
	
	int Size = CExcelManager::GetInst()->GetMonsterSize();

	for (int i = 0; i < Size; ++i)
	{
		m_MonsterInfo[i] = CExcelManager::GetInst()->GetMonsterInfo(i);
	}

	m_BulletKingInfo = CExcelManager::GetInst()->GetBulletKingInfo();

	return true;
}

void CSceneMode::Update(float DeltaTime)
{
}

void CSceneMode::PostUpdate(float DeltaTime)
{
}
