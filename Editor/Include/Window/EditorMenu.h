#pragma once
#include "IMGUIWindow.h"
#include "../EditorInfo.h"
class CEditorMenu :
    public CIMGUIWindow
{
public:
	CEditorMenu();
	virtual ~CEditorMenu();

private:
	class CIMGUIButton* m_ObjectCreateButton;
	class CIMGUIComboBox* m_ObjectCombo;

	class CPublic* m_Public;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void ObjectCreateButton();

public:
	void LoadSceneObject();
};

