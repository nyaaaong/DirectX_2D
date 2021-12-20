#pragma once

#include "IMGUIWidget.h"

class CIMGUICheckBox :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUICheckBox();
	virtual ~CIMGUICheckBox();

private:
	bool*	m_Check;

public:
	void CheckBox(bool* Check);

public:
	virtual bool Init();
	virtual bool Render();
};

