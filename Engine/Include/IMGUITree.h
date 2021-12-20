#pragma once
#include "IMGUIWidget.h"
class CIMGUITree :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITree();
	virtual ~CIMGUITree();

private:
	std::function<void()>	m_OpenFunc;
	std::function<void()>	m_CloseFunc;
	bool					m_Open;

public:
	bool IsOpened()	const
	{
		return ImGui::IsItemToggledOpen();
	}

public:
	virtual bool Init();
	virtual bool Render();

public:
	template <typename T>
	void RegisterFunc(bool UseOpen, T* Obj, void(T::*Func)())
	{
		if (UseOpen)
			m_OpenFunc = std::bind(Func, Obj);

		else
			m_CloseFunc = std::bind(Func, Obj);
	}
};

