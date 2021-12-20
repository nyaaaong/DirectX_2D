#pragma once
#include "IMGUIWidget.h"
class CIMGUIRadio :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIRadio();
	virtual ~CIMGUIRadio();

private:
	int*		m_FinalValue;
	int			m_ButtonValue;

public:
	// FinalVal : ���� ��ư���� ������ ���� ���� �ּ�
	//ButtonVal : enum ���� �̿��� FinalVal�� �־���
	void RadioButton(int* FinalVal, int ButtonVal);
	
public:
	virtual bool Init();
	virtual bool Render();
};

