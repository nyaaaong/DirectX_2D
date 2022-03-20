#include "Public.h"
#include "PathManager.h"
#include "GameObject/GameObject.h"
#include "Component/TileMapComponent.h"

DEFINITION_SINGLE(CPublic)

CPublic::CPublic()
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
	if (!strcmp(Multibyte, "BulletKin"))
		return Object_Type::BulletKin;

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
		case Object_Type::BulletKin:
			vecName.push_back("BulletKin");
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

void CPublic::AddObjectWorldPos(Object_Type Type, const Vector3& WorldPos)
{
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
	if (!FindObjectType(Type))
		return;

	auto	iter = m_mapObject.begin();
	auto	iterEnd = m_mapObject.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
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

	switch (Type)
	{
	case Object_Type::BulletKin:
	{
		std::list<Vector3>* NewObjPosList = DBG_NEW std::list<Vector3>;

		m_mapObject.insert(std::make_pair(Type, NewObjPosList));
	}
		break;
	}

	return false;
}

void CPublic::DeleteObjectType(Object_Type Type)
{
	if (!FindObjectType(Type))
		return;

	switch (Type)
	{
	case Object_Type::BulletKin:
	{
		auto	iter = m_mapObject.find(Type);

		SAFE_DELETE(iter->second);
		m_mapObject.erase(iter);
	}
	break;
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
	
	auto	iter = m_mapObject.begin();
	std::vector<CTile*>	vecTypeTile;
	std::vector<CTile*> vecObjTypeTile;

	TileMapComponent->GetSameTypeTile(Tile_Type::Object, vecTypeTile);

	int Size = (int)m_mapObject.size();

	for (int i = 0; i < Size; ++i)
	{
		vecObjTypeTile.clear();

		TileMapComponent->GetSameObjectTypeTile(iter->first, vecTypeTile, vecObjTypeTile);

		int ObjTypeSize = (int)vecObjTypeTile.size();

		for (int j = 0; j < ObjTypeSize; ++j)
		{
			iter->second->push_back(vecObjTypeTile[j]->GetWorldPos());
		}
	}
}
