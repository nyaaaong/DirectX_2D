#pragma once

#include "../Ref.h"

class CWidget :
	public CRef
{
	friend class CWidgetWindow;

protected:
	CWidget();
	CWidget(const CWidget& widget);
	virtual ~CWidget();

protected:
	class CWidgetWindow* m_Owner;
	int     m_ZOrder;
	Vector2	m_Pos;
	Vector2	m_Size;

public:
	virtual void Enable(bool bEnable)
	{
		CRef::Enable(bEnable);
	}

	class CWidgetWindow* GetOwner()	const
	{
		return m_Owner;
	}

	Vector2 GetWindowPos()	const
	{
		return m_Pos;
	}

	Vector2 GetWindowSize()	const
	{
		return m_Size;
	}

	int GetZOrder()	const
	{
		return m_ZOrder;
	}

public:
	void SetZOrder(int ZOrder)
	{
		m_ZOrder = ZOrder;
	}

	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y)
	{
		m_Pos = Vector2(x, y);
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
};

