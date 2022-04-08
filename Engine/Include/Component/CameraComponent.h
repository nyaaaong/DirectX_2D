#pragma once

#include "SceneComponent.h"

class CCameraComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& com);
	virtual ~CCameraComponent();

protected:
	Camera_Type m_CameraType;
	Matrix      m_matView;
	Matrix      m_matProj;
	float		m_ViewAngle;
	float		m_Distance;
	Resolution	m_RS;
	Vector2		m_Ratio;
	float		m_CameraSpeed;
	bool		m_UseLimit;	// 카메라 제한
	Vector3		m_LimitStartPos;
	Vector3		m_LimitEndPos;

public:
	virtual void SetRelativePos(const Vector3& Pos);
	virtual void SetRelativePos(float x, float y, float z);
	virtual void SetRelativePosX(float x);
	virtual void SetRelativePosY(float y);
	virtual void AddRelativePos(const Vector3& Pos);
	virtual void AddRelativePos(float x, float y, float z);
	virtual void SetWorldPos(const Vector3& Pos);
	virtual void SetWorldPos(float x, float y, float z);
	virtual void SetWorldPosX(float x);
	virtual void SetWorldPosY(float y);
	virtual void AddWorldPos(const Vector3& Pos);

public:
	Vector3	GetResolutionVector3()	const
	{
		return Vector3((float)m_RS.Width, (float)m_RS.Height, 0.f);
	}

	float GetCameraSpeed()	const
	{
		return m_CameraSpeed;
	}

	Vector2 GetLeftBottom()	const
	{
		Vector2	LB;

		LB.x = GetWorldPos().x;
		LB.y = GetWorldPos().y;

		return LB;
	}

	Resolution GetResolution()	const
	{
		return m_RS;
	}

	Camera_Type GetCameraType()	const
	{
		return m_CameraType;
	}

	const Matrix& GetViewMatrix()	const
	{
		return m_matView;
	}

	const Matrix& GetProjMatrix()	const
	{
		return m_matProj;
	}

public:
	void SetCameraLimit(const Vector3& StartPos, const Vector3& EndPos)
	{
		m_UseLimit = true;

		m_LimitStartPos = StartPos;
		m_LimitEndPos = EndPos;
	}

	void SetCameraSpeed(float Speed)
	{
		m_CameraSpeed = Speed;
	}

	void SetViewAngle(float Angle)
	{
		m_ViewAngle = Angle;

		if (m_CameraType == Camera_Type::Camera3D)
			CreateProjectionMatrix();
	}

	void SetDistance(float Distance)
	{
		m_Distance = Distance;

		CreateProjectionMatrix();
	}

	void SetCameraType(Camera_Type Type)
	{
		m_CameraType = Type;

		CreateProjectionMatrix();
	}

	// 2D 전용
	void OnViewportCenter()
	{
		if (m_CameraType == Camera_Type::Camera2D)
		{
			float	z = GetRelativePos().z;
			SetRelativePos(m_RS.Width / -2.f, m_RS.Height / -2.f, z);

			m_Ratio.x = 0.5f;
			m_Ratio.y = 0.5f;
		}
	}

	// 2D 전용
	void SetViewportRatio(float x, float y)
	{
		if (m_CameraType == Camera_Type::Camera2D)
		{
			float	z = GetRelativePos().z;
			SetRelativePos(m_RS.Width * -x, m_RS.Height * -y, z);

			m_Ratio.x = x;
			m_Ratio.y = y;
		}
	}

private:
	void CreateProjectionMatrix();
	void LimitCheck();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CCameraComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

