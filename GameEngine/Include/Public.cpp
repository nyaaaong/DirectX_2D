#include "Public.h"
#include "PathManager.h"

DEFINITION_SINGLE(CPublic)

CPublic::CPublic()
{
}

CPublic::~CPublic()
{
	auto	iter = m_mapObjectInfo.begin();
	auto	iterEnd = m_mapObjectInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void CPublic::GetObjectName(std::vector<std::string>& vecName)
{
	size_t Size = m_mapObjectInfo.size();

	vecName.resize(Size);

	int Index = 0;

	auto	iter = m_mapObjectInfo.begin();
	auto	iterEnd = m_mapObjectInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		vecName[Index] = iter->second->Name;

		++Index;
	}
}

void CPublic::SetObjectWorldPos(const std::string& Name, const Vector3& WorldPos)
{
	Object_Info* Data = FindObjectInfo(Name);

	if (!Data)
		return;

	Data->WorldPos = WorldPos;
}

Object_Info* CPublic::FindObjectInfo(const std::string& Name)
{
	auto	iter = m_mapObjectInfo.find(Name);

	if (iter == m_mapObjectInfo.end())
		return nullptr;

	return iter->second;
}

bool CPublic::CreateObjectInfo(const std::string& Name, Object_Type Type)
{
	if (FindObjectInfo(Name))
		return false;

	Object_Info* NewInfo = new Object_Info;

	NewInfo->Name = Name;
	NewInfo->Type = Type;

	m_mapObjectInfo.insert(std::make_pair(Name, NewInfo));

	return true;
}

void CPublic::DeleteObjectInfo(const std::string& Name)
{
	auto	iter = m_mapObjectInfo.find(Name);

	if (iter == m_mapObjectInfo.end())
		return;

	SAFE_DELETE(iter->second);

	m_mapObjectInfo.erase(iter);
}

void CPublic::Save(FILE* File)
{
	int Size = (int)m_mapObjectInfo.size();
	fwrite(&Size, sizeof(int), 1, File);

	auto	iter = m_mapObjectInfo.begin();
	auto	iterEnd = m_mapObjectInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		Object_Info*	Data = iter->second;

		int Length = (int)(Data->Name.length());
		fwrite(&Length, sizeof(int), 1, File);
		fwrite(Data->Name.c_str(), sizeof(char), 1, File);

		fwrite(&Data->Type, sizeof(Object_Type), 1, File);

		fwrite(&Data->WorldPos.x, sizeof(float), 1, File);
		fwrite(&Data->WorldPos.y, sizeof(float), 1, File);
		fwrite(&Data->WorldPos.z, sizeof(float), 1, File);
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
	auto	iter = m_mapObjectInfo.begin();
	auto	iterEnd = m_mapObjectInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	
	int Size = 0;
	fread(&Size, sizeof(int), 1, File);

	m_mapObjectInfo.reserve((size_t)Size);

	for (int i = 0; i < Size; ++i)
	{
		Object_Info*	Data = new Object_Info;

		int Length = 0;
		fread(&Length, sizeof(int), 1, File);

		char	Name[256] = {};
		fread(Name, sizeof(char), Length, File);
		Data->Name = Name;

		fread(&Data->Type, sizeof(Object_Type), 1, File);
		fread(&Data->WorldPos.x, sizeof(float), 1, File);
		fread(&Data->WorldPos.y, sizeof(float), 1, File);
		fread(&Data->WorldPos.z, sizeof(float), 1, File);

		m_mapObjectInfo.insert(std::make_pair(Name, Data));
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
