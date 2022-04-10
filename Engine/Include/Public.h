#pragma once

#include "GameInfo.h"

class CPublic
{
	friend class CEngine;

private:
	std::unordered_map<Object_Type, std::list<Vector3>*>	m_mapObject;
	int		m_TileCountX;
	int		m_TileCountY;
	float	m_TileSizeX;
	float	m_TileSizeY;

public:
	float GetTileSizeX()	const
	{
		return m_TileSizeX;
	}

	float GetTileSizeY()	const
	{
		return m_TileSizeY;
	}

	int GetTileCountX()	const
	{
		return m_TileCountX;
	}

	int GetTileCountY()	const
	{
		return m_TileCountY;
	}

	int ObjectSize(Object_Type Type)	const
	{
		auto	iter = m_mapObject.find(Type);

		if (iter == m_mapObject.end())
			return 0;

		return (int)iter->second->size();
	}

public:
	Object_Type GetMultibyteToType(const char* Multibyte);

public:
	void GetObjectName(std::vector<std::string>& vecName);
	void GetObjectPos(Object_Type Type, std::vector<Vector3>& vecPos);
	bool GetPlayerPos(Vector3& OutputPos);
	bool GetBossRoomEndPos(Vector3& OutputPos);
	void AddObjectWorldPos(Object_Type Type, const Vector3& WorldPos);
	void DeleteObjectWorldPos(const Vector3& WorldPos);
	void ClearObjectWorldPos(Object_Type Type);
	void ClearPlayerWorldPos();
	void ClearBossRoomEndWorldPos();
	void ClearAllObjectWorldPos();

public:
	bool CreateObjectType(Object_Type Type);
	void DeleteObjectType(Object_Type Type);
	bool FindObjectType(Object_Type Type);
	bool FindObjectType(const char* TypeMultibyte);

private:
	std::list<Vector3>* FindObjectPosList(Object_Type Type);

public:
	void Save(FILE* File);
	void Save(const char* FileName, const std::string& PathName = SCENE_PATH);
	void SaveFullPath(const char* FullPath);
	void Load(FILE* File);
	void Load(const char* FileName, const std::string& PathName = SCENE_PATH);
	void LoadFullPath(const char* FullPath);
	void LoadObjPos(class CGameObject* TileMapObj);

	DECLARE_SINGLE(CPublic)
};

