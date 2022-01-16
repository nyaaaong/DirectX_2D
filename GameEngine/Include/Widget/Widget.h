#pragma once

#include "../Ref.h"
#include "../Resource/Texture/Texture.h"

struct WidgetImageInfo
{
	CSharedPtr<CTexture>	Texture;
	Vector4			Tint;
	std::vector<AnimationFrameData> vecFrameData;

	WidgetImageInfo()
	{
		Tint = Vector4::White;
	}
};

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
	Vector2	m_RenderPos;
	Vector2	m_Size;
	float	m_Angle;
	bool	m_Start;
	Vector4	m_Tint;
	bool	m_MouseHovered;
	bool	m_CollisionMouseEnable;
	class CWidgetConstantBuffer* m_CBuffer;
	CSharedPtr<class CShader>	m_Shader;
	CSharedPtr<class CMesh>		m_Mesh;

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

	float GetAngle()	const
	{
		return m_Angle;
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

	virtual void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	virtual void SetSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}

	void SetOwner(class CWidgetWindow* Owner)
	{
		m_Owner = Owner;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

	void SetShader(const std::string& Name);
	void SetUseTexture(bool Use);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const Vector2& MousePos);
	virtual CWidget* Clone();
};

