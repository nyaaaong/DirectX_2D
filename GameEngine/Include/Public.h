#pragma once

#include "GameInfo.h"

class CPublic
{
	friend class CEngine;

private:
	std::unordered_map<std::string, Object_Info*>	m_mapObjectInfo;

public:
	int GetObjectInfoSize()	const
	{
		return (int)m_mapObjectInfo.size();
	}

public:
	void GetObjectName(std::vector<std::string>& vecName);
	void SetObjectWorldPos(const std::string& Name, const Vector3& WorldPos);
	Object_Info* FindObjectInfo(const std::string& Name);

public:
	bool CreateObjectInfo(const std::string& Name, Object_Type Type);
	void DeleteObjectInfo(const std::string& Name);

public:
	void Save(FILE* File);
	void Save(const char* FileName, const std::string& PathName = SCENE_PATH);
	void SaveFullPath(const char* FullPath);
	void Load(FILE* File);
	void Load(const char* FileName, const std::string& PathName = SCENE_PATH);
	void LoadFullPath(const char* FullPath);

	DECLARE_SINGLE(CPublic)
};

