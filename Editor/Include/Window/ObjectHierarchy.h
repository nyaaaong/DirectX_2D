#pragma once
#include "IMGUIWindow.h"
#include "GameObject/GameObject.h"
#include "Component/SceneComponent.h"

class CObjectHierarchy :
    public CIMGUIWindow
{
public:
	CObjectHierarchy();
	virtual ~CObjectHierarchy();

private:
	class CIMGUIListBox* m_ObjectListWidget;
	Object_Info*		m_SelectObjectInfo;
	CSharedPtr<CGameObject>		m_SelectObject;
	CSharedPtr<CSceneComponent>	m_SelectComponent;

public:
	class CIMGUIListBox* GetObjectList()	const
	{
		return m_ObjectListWidget;
	}

	Object_Info* GetSelectObjectInfo()	const
	{
		return m_SelectObjectInfo;
	}

	CSharedPtr<CGameObject> GetSelectObject()	const
	{
		return m_SelectObject;
	}

	CSharedPtr<CSceneComponent> GetSelectComponent()	const
	{
		return m_SelectComponent;
	}

public:
	void AddObjectList(const char* Name);
	void ClearObjectList();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void SelectObject(int Index, const char* Item);
};

