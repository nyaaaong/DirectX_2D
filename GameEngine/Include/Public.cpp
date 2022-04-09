#include "Public.h"
#include "PathManager.h"
#include "GameObject/GameObject.h"
#include "Component/TileMapComponent.h"

DEFINITION_SINGLE(CPublic)

CPublic::CPublic()	:
	m_TileCountX(0),
	m_TileCountY(0),
	m_TileSizeX(0.f),
	m_TileSizeY(0.f)
{
}

CPublic::~CPublic()
{
	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

Object_Type CPublic::GetMultibyteToType(const char* Multibyte)
{
	if (!strcmp(Multibyte, "M_BulletKin"))
		return Object_Type::M_BulletKin;

	else if (!strcmp(Multibyte, "M_Bandana"))
		return Object_Type::M_Bandana;

	else if (!strcmp(Multibyte, "M_ShotgunKin1"))
		return Object_Type::M_ShotgunKin1;

	else if (!strcmp(Multibyte, "M_ShotgunKin2"))
		return Object_Type::M_ShotgunKin2;

	else if (!strcmp(Multibyte, "P_PlayerPos"))
		return Object_Type::P_PlayerPos;

	else if (!strcmp(Multibyte, "B_BulletKing"))
		return Object_Type::B_BulletKing;

	else if (!strcmp(Multibyte, "S_NextScene"))
		return Object_Type::S_NextScene;

	return Object_Type::Max;
}

void CPublic::GetObjectName(std::vector<std::string>& vecName)
{
	size_t Size = m_mapObject.size();

	vecName.reserve(Size);

	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		switch (iter->first)
		{
		case Object_Type::M_BulletKin:
			vecName.push_back("M_BulletKin");
			break;
		case Object_Type::M_Bandana:
			vecName.push_back("M_Bandana");
			break;
		case Object_Type::M_ShotgunKin1:
			vecName.push_back("M_ShotgunKin1");
			break;
		case Object_Type::M_ShotgunKin2:
			vecName.push_back("M_ShotgunKin2");
			break;
		case Object_Type::P_PlayerPos:
			vecName.push_back("P_PlayerPos");
			break;
		case Object_Type::B_BulletKing:
			vecName.push_back("B_BulletKing");
			break;
		case Object_Type::S_NextScene:
			vecName.push_back("S_NextScene");
			break;
		}
	}
}

void CPublic::GetObjectPos(Object_Type Type, std::vector<Vector3>& vecPos)
{
	auto	iter = m_mapObject.find(Type);

	if (iter == m_mapObject.end())
		return;

	int Size = (int)m_mapObject.size();

	for (int i = 0; i < Size; ++i)
	{
		int ObjCount = (int)iter->second->size();
		int j = 0;
		vecPos.resize(ObjCount);

		auto	iter1 = iter->second->begin();
		auto	iter1End = iter->second->end();

		for (; iter1 != iter1End; ++iter1)
		{
			vecPos[j] = (*iter1);
			++j;
		}
	}
}

bool CPublic::GetPlayerPos(Vector3& PlayerPos)
{
	auto	iter = m_mapObject.find(Object_Type::P_PlayerPos);

	if (iter == m_mapObject.end())
		ASSERT("if (iter == m_mapObject.end())");

	if (iter->second->empty())
		return false;

	PlayerPos = iter->second->front();
	
	return true;
}

void CPublic::AddObjectWorldPos(Object_Type Type, const Vector3& WorldPos)
{
	DeleteObjectWorldPos(WorldPos);

	std::list<Vector3>*	ObjectList = FindObjectPosList(Type);

	if (!ObjectList)
		CreateObjectType(Type);

	ObjectList->push_back(WorldPos);
}

void CPublic::DeleteObjectWorldPos(const Vector3& WorldPos)
{
	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->empty())
			return;

		auto	iter1 = iter->second->begin();
		auto	iter1End = iter->second->end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ((*iter1) == WorldPos)
			{
				iter->second->erase(iter1);
				return;
			}
		}
	}
}

void CPublic::ClearObjectWorldPos(Object_Type Type)
{
	auto	iter = m_mapObject.find(Type);

	if (iter == m_mapObject.end())
		return;

	iter->second->clear();
}

void CPublic::ClearPlayerWorldPos()
{
	ClearObjectWorldPos(Object_Type::P_PlayerPos);
}

void CPublic::ClearAllObjectWorldPos()
{
	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->clear();
	}
}

std::list<Vector3>* CPublic::FindObjectPosList(Object_Type Type)
{
	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == Type)
			return iter->second;
	}

	return nullptr;
}

bool CPublic::CreateObjectType(Object_Type Type)
{
	if (FindObjectType(Type))
		return true;

	else if (Type <= Object_Type::S_NextScene)
	{
		std::list<Vector3>* NewObjPosList = DBG_NEW std::list<Vector3>;

		m_mapObject.insert(std::make_pair(Type, NewObjPosList));
	}

	return false;
}

void CPublic::DeleteObjectType(Object_Type Type)
{
	if (!FindObjectType(Type))
		return;

	else if (Type <= Object_Type::S_NextScene)
	{
		auto	iter = m_mapObject.find(Type);

		SAFE_DELETE(iter->second);
		m_mapObject.erase(iter);
	}
}

bool CPublic::FindObjectType(Object_Type Type)
{
	auto	iter = m_mapObject.find(Type);

	if (iter == m_mapObject.end())
		return false;

	return true;
}

bool CPublic::FindObjectType(const char* TypeMultibyte)
{
	return FindObjectType(GetMultibyteToType(TypeMultibyte));
}

void CPublic::Save(FILE* File)
{
	int Size = (int)m_mapObject.size();
	fwrite(&Size, sizeof(int), 1, File);

	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		Object_Type Type = iter->first;

		fwrite(&Type, sizeof(Object_Type), 1, File);
	}
}

void CPublic::Save(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	SaveFullPath(FullPath);
}

void CPublic::SaveFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	Save(File);

	fclose(File);
}

void CPublic::Load(FILE* File)
{
	int Size = 0;
	fread(&Size, sizeof(int), 1, File);

	m_mapObject.reserve((size_t)Size);

	for (int i = 0; i < Size; ++i)
	{
		Object_Type Type = Object_Type::Max;

		fread(&Type, sizeof(Object_Type), 1, File);

		if (Type == Object_Type::Max)
			ASSERT("if (Type == Object_Type::Max)");

		CreateObjectType(Type);
	}
}

void CPublic::Load(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	LoadFullPath(FullPath);
}

void CPublic::LoadFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	Load(File);

	fclose(File);
}

void CPublic::LoadObjPos(CGameObject* TileMapObj)
{
	if (!TileMapObj)
		ASSERT("if (!TileMapObj)");

	CSceneComponent* Root = TileMapObj->GetRootComponent();

	CTileMapComponent* TileMapComponent = dynamic_cast<CTileMapComponent*>(Root);

	if (!TileMapComponent)
		ASSERT("if (!TileMapComponent)");

	m_TileCountX = TileMapComponent->GetTileCountX();
	m_TileCountY = TileMapComponent->GetTileCountY();
	m_TileSizeX = TileMapComponent->GetTileSize().x;
	m_TileSizeY = TileMapComponent->GetTileSize().y;
	
	auto	iter = m_mapObject.begin();
	std::vector<CTile*>	vecTypeTile;
	std::vector<CTile*> vecObjTypeTile;

	int TypeSize = (int)Tile_Type::End;

	for (int i = 0; i < TypeSize; ++i)
	{
		vecTypeTile.clear();
		vecObjTypeTile.clear();

		TileMapComponent->GetSameTypeTile((Tile_Type)i, vecTypeTile);

		if (vecTypeTile.empty() || (Tile_Type)i <= Tile_Type::T_Wall || (Tile_Type)i > Tile_Type::S_NextScene)
			continue;

		int Size = (int)vecTypeTile.size();

		for (int j = 0; j < Size; ++j)
		{
			switch ((Tile_Type)i)
			{
			case Tile_Type::M_BulletKin:
				iter = m_mapObject.find(Object_Type::M_BulletKin);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::M_BulletKin);
					iter = m_mapObject.find(Object_Type::M_BulletKin);
				}
				break;
			case Tile_Type::M_Bandana:
				iter = m_mapObject.find(Object_Type::M_Bandana);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::M_Bandana);
					iter = m_mapObject.find(Object_Type::M_Bandana);
				}
				break;
			case Tile_Type::M_ShotgunKin1:
				iter = m_mapObject.find(Object_Type::M_ShotgunKin1);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::M_ShotgunKin1);
					iter = m_mapObject.find(Object_Type::M_ShotgunKin1);
				}
				break;
			case Tile_Type::M_ShotgunKin2:
				iter = m_mapObject.find(Object_Type::M_ShotgunKin2);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::M_ShotgunKin2);
					iter = m_mapObject.find(Object_Type::M_ShotgunKin2);
				}
				break;
			case Tile_Type::P_PlayerPos:
				iter = m_mapObject.find(Object_Type::P_PlayerPos);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::P_PlayerPos);
					iter = m_mapObject.find(Object_Type::P_PlayerPos);
				}
				break;
			case Tile_Type::B_BulletKing:
				iter = m_mapObject.find(Object_Type::B_BulletKing);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::B_BulletKing);
					iter = m_mapObject.find(Object_Type::B_BulletKing);
				}
				break;
			case Tile_Type::S_NextScene:
				iter = m_mapObject.find(Object_Type::S_NextScene);

				if (iter == m_mapObject.end())
				{
					CreateObjectType(Object_Type::S_NextScene);
					iter = m_mapObject.find(Object_Type::S_NextScene);
				}
				break;
			}

			Vector3	Pos = vecTypeTile[j]->GetWorldPos();
			Pos.z = 0.f;

			iter->second->push_back(Pos);
		}
	}
}
