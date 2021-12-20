#pragma once
#include "IMGUIWindow.h"
class CIMGUITestWindow :
    public CIMGUIWindow
{
public:
	CIMGUITestWindow();
	virtual ~CIMGUITestWindow();

private:
	std::vector<class CIMGUIRadio*>	m_vecRadio;
	bool	m_CheckBoxValue1;
	bool	m_CheckBoxValue2;
	int		m_RadioValue;
	class CIMGUICheckBox* m_CB1;
	class CIMGUICheckBox* m_CB2;
	class CIMGUIRadio*	m_Radio1;
	class CIMGUIRadio*	m_Radio2;
	class CIMGUIRadio*	m_Radio3;
	class CIMGUITree*	m_Tree;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void ClickButton1();
	void ClickButton2();

public:
	void OpenTree();
	void CloseTree();
};

