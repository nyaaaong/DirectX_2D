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
	void SetOpenCallback(T* Obj, void(T::* Func)())
	{
		m_OpenFunc = std::bind(Func, Obj);
	}

	template <typename T>
	void SetCloseCallback(T* Obj, void(T::* Func)())
	{
		m_CloseFunc = std::bind(Func, Obj);
	}
};

