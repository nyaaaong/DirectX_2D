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
	std::vector<class CIMGUITree*>	m_vecComponentTree;
	std::vector<class CIMGUIListBox*>	m_vecComponentListBox;
	class CIMGUITree* m_ComponentTree;
	CSharedPtr<CGameObject>		m_SelectObject;
	CSharedPtr<CSceneComponent>	m_SelectComponent;

public:
	class CIMGUIListBox* GetObjectList()	const
	{
		return m_ObjectListWidget;
	}

	class CIMGUIListBox* GetComponentList(int Index)	const
	{
		if (m_vecComponentListBox.size() <= Index)
			return nullptr;

		return m_vecComponentListBox[Index];
	}

	CGameObject* GetSelectObject()	const
	{
		return m_SelectObject;
	}

	CSceneComponent* GetSelectComponent()	const
	{
		return m_SelectComponent;
	}

public:
	void AddObjectList(const char* Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void SelectObject(int Index, const char* Item);
	void SelectComponent(int Index, const char* Item);

private:
	void ComponentTreeOpen();
	void ComponentTreeClose();
	void ComponentListBoxTreeOpen();
	void ComponentListBoxTreeClose();
};

