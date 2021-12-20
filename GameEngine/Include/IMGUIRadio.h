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
	// FinalVal : 같은 버튼끼리 공유할 최종 값의 주소
	//ButtonVal : enum 등을 이용해 FinalVal에 넣어줌
	void RadioButton(int* FinalVal, int ButtonVal);
	
public:
	virtual bool Init();
	virtual bool Render();
};

