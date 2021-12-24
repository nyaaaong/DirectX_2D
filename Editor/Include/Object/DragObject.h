#pragma once

#include "GameObject/GameObject.h"

class CDragObject :
    public CGameObject
{
    friend class CScene;

protected:
    CDragObject();
    CDragObject(const CDragObject& obj);
    virtual ~CDragObject();

private:
    CSharedPtr<class CStaticMeshComponent>    m_Mesh;
    Vector2     m_StartPos;
    Vector2     m_EndPos;
	Vector3		m_FirstWorldPos;

public:
	void AddStartPos(const Vector2& StartPos)
	{
		m_StartPos += StartPos;
	}

	void AddEndPos(const Vector2& EndPos)
	{
		m_EndPos += EndPos;
	}

	void SetFirstWorldPos(const Vector3& FirstWorldPos)
	{
		m_FirstWorldPos = FirstWorldPos;
	}

public:
	Vector3 GetFirstWorldPos()	const
	{
		return m_FirstWorldPos;
	}

	Vector2 GetStartPos()	const
	{
		return m_StartPos;
	}

	Vector2 GetEndPos()	const
	{
		return m_EndPos;
	}

public:
    void SetStartPos(const Vector2& Pos);
    void SetEndPos(const Vector2& Pos);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDragObject* Clone();
};

