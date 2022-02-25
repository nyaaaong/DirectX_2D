#pragma once

#include "GameInfo.h"

class CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIWidget();
	virtual ~CIMGUIWidget();

protected:
	std::string		m_Name;
	class CIMGUIWindow* m_Owner;
	ImVec2			m_Size;
	ImColor			m_Color;
	ImFont*			m_Font;
	bool			m_Enable;
	bool		m_MouseCheck;
	bool		m_IsHovered;
	bool		m_IsClicked;

public:
	bool IsClicked()	const
	{
		return m_IsClicked;
	}

	bool IsHovered()	const
	{
		return m_IsHovered;
	}

	bool IsMouseCheck()	const
	{
		return m_MouseCheck;
	}

	bool IsEnable()	const
	{
		return m_Enable;
	}

	bool IsDisable()	const
	{
		return !m_Enable;
	}

	const std::string& GetName()	const
	{
		return m_Name;
	}

public:
	void MouseCheck(bool MouseCheck)
	{
		m_MouseCheck = MouseCheck;
	}

	void Enable()
	{
		m_Enable = true;
	}

	void Disable()
	{
		m_Enable = false;
	}

	void SetHideName(bool Hide = true)
	{
		if (Hide)
			m_Name = "##" + m_Name;
	}

	void SetOwner(class CIMGUIWindow* Owner)
	{
		m_Owner = Owner;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	void SetSize(const ImVec2& Size)
	{
		m_Size = Size;
	}

	void SetSize(const Vector2& Size)
	{
		m_Size.x = Size.x;
		m_Size.y = Size.y;
	}

	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetColor(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a = 255)
	{
		m_Color.Value.x = r / 255.f;
		m_Color.Value.y = g / 255.f;
		m_Color.Value.z = b / 255.f;
		m_Color.Value.w = a / 255.f;
	}

public:
	virtual bool Init();
	virtual bool Render();

protected:
	// 사용법 : IMGUI의 Render 함수에서 ImGui 객체를 생성한 코드 바로 밑에 사용한다.
	void CheckItemHovered();
	void CheckItemClicked();
};

