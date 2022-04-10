#pragma once

#pragma warning(disable:4005)
#pragma warning(disable:6011)
#pragma warning(disable:6029)
#pragma warning(disable:6387)
#pragma warning(disable:26451)
#pragma warning(disable:26812)
#pragma warning(disable:28182)

#define	DIRECTINPUT_VERSION	0x0800
#define _CRTDBG_MAP_ALLOC

#ifdef	_DEBUG
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <stdlib.h>
#include <functional>
#include <string>
#include <math.h>
#include <algorithm>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include <assert.h>
#include <dwrite.h>
#include <dwrite_3.h>
#include <d2d1.h>
#include <stack>
#include <process.h>

#include "Excel/include_cpp/libxl.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "libxl.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "fmod.hpp"
#include "Resource/Texture/DirectXTex.h"
#include "Flag.h"

#ifdef _DEBUG

#pragma comment(lib, "DirectXTex_Debug.lib")

#else

#pragma comment(lib, "DirectXTex.lib")

#endif // _DEBUG

#pragma comment(lib, "fmod64_vc.lib")

#define	ASSERT(text)	assert(!text);

#define	ROOT_PATH	"Root"
#define	SHADER_PATH	"Shader"
#define	TEXTURE_PATH	"Texture"
#define	MAP_PATH	"Map"
#define	EXCEL_PATH	"Excel"
#define	FONT_PATH		"Font"
#define	ANIMATION_PATH	"Animation"
#define	SCENE_PATH		"Scene"
#define	SOUND_PATH		"Sound"

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define	DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_Inst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_Inst)\
			m_Inst = DBG_NEW Type;\
		return m_Inst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_Inst);\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type)	Type* Type::m_Inst = nullptr;

struct Resolution
{
	unsigned int	Width = 1280;
	unsigned int	Height = 720;
};

struct VertexColor
{
	Vector3	Pos;
	Vector4	Color;

	VertexColor(const Vector3& _Pos, const Vector4& _Color)	:
		Pos(_Pos),
		Color(_Color)
	{
	}
};


struct VertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int		Size = 0;
	int		Count = 0;

	~VertexBuffer()
	{
		SAFE_RELEASE(Buffer);
	}
};

struct IndexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int		Size = 0;
	int		Count = 0;
	DXGI_FORMAT	Fmt = DXGI_FORMAT_UNKNOWN;

	~IndexBuffer()
	{
		SAFE_RELEASE(Buffer);
	}
};



struct MeshContainer
{
	VertexBuffer	VB;
	std::vector<IndexBuffer>	vecIB;
	D3D11_PRIMITIVE_TOPOLOGY	Primitive;
};

struct TransformCBuffer
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
	Matrix	matWV;
	Matrix	matWVP;
	Matrix	matVP;
	Vector3	Pivot;
	float	Empty1 = 0.f;
	Vector3	MeshSize;
	float	Empty = 0.f;
};

struct VertexUV
{
	Vector3	Pos;
	Vector2 UV;

	VertexUV(const Vector3& _Pos, const Vector2& _UV) :
		Pos(_Pos),
		UV(_UV)
	{
	}
};

struct MaterialCBuffer
{
	Vector4	BaseColor;
	float	Opacity = 1.f;
	int		PaperBurnEnable = 0;
	Vector2	Empty;
};

struct AnimationFrameData
{
	Vector2	Start;
	Vector2	Size;
};

struct Animation2DCBuffer
{
	Vector2	Animation2DStartUV;
	Vector2	Animation2DEndUV;
	int		Animation2DType = -1;
	Vector3	Animation2DEmpty;
};

struct Standard2DCBuffer
{
	int		AnimationEnable = -1;
	Vector3	Empty;
};

struct FindComponentName
{
	std::string	Name;
	std::string	ParentName;
	Component_Flag	ComponentFlag;
};

struct CollisionProfile
{
	std::string			Name;
	Collision_Channel	Channel = Collision_Channel::Max;
	bool				CollisionEnable = true;

	std::vector<Collision_Interaction>	vecInteraction;
};

struct CollisionResult
{
	class CColliderComponent* Src = nullptr;
	class CColliderComponent* Dest = nullptr;
	Vector3	HitPoint;
};

struct Box2DInfo
{
	Vector2	Center;
	Vector2	Axis[2];
	Vector2	Length;
	Vector2	Min;
	Vector2	Max;
};

struct CircleInfo
{
	Vector2	Center;
	float	Radius = 1.f;
	Vector2	Min;
	Vector2	Max;
};

struct PixelInfo
{
	unsigned char* Pixel = nullptr;
	unsigned int	Width = 0;
	unsigned int	Height = 0;
	PixelCollision_Type	Type = PixelCollision_Type::Color_Confirm;
	unsigned char	Color[4] = {};
	Box2DInfo		Box = {};
	Vector2	Min;
	Vector2	Max;
	ID3D11ShaderResourceView* SRV = nullptr;
	int		RefCount = 1;
};

struct ColliderCBuffer
{
	Vector4	Color;
	Matrix	matWVP;
};

struct WidgetCBuffer
{
	Vector4	Tint;
	Matrix	matWP;
	int		UseTexture = 0;
	int		WidgetAnimType = 0;
	Vector2	WidgetAnimStartUV;
	Vector2	WidgetAnimEndUV;
	int		WidgetAnimEnable = 0;
	float	Opacity = 0.f;
};

struct ProgressBarCBuffer
{
	float	Percent;
	int		Dir;
	Vector2	Empty;

	ProgressBarCBuffer()	:
		Percent(0.f),
		Dir(0)
	{}
};

struct	ParticleCBuffer
{
	unsigned int	SpawnEnable = 0;	// ���� ��ƼŬ ���� ����
	Vector3	StartMin;		// ��ƼŬ�� ������ ������ Min
	Vector3	StartMax;		// ��ƼŬ�� ������ ������ Max
	unsigned int	SpawnCountMax = 0;	// ������ ��ƼŬ�� �ִ�
	Vector3	ScaleMin;		// ������ ��ƼŬ ũ���� Min
	float	LifeTimeMin = 0.f;	// ������ ��ƼŬ�� ������� �ּҽð�
	Vector3	ScaleMax;		// ������ ��ƼŬ ũ���� Max
	float	LifeTimeMax = 0.f;	// ������ ��ƼŬ�� ������� �ִ�ð�
	Vector4	ColorMin;		// ������ ��ƼŬ�� ���� Min
	Vector4	ColorMax;		// ������ ��ƼŬ�� ���� Max
	float	SpeedMin = 0.f;		// ��ƼŬ�� �ּ� �̵��ӵ�
	float	SpeedMax = 0.f;		// ��ƼŬ�� �ִ� �̵��ӵ�
	int		Move = 0;			// �̵��� �ϴ��� ���ϴ���
	int		Gravity = 0;		// �߷� ������ �޴��� �ȹ޴���
	Vector3	MoveDir;		// �̵��� �Ѵٸ� ������ �� �̵� ����
	int		Is2D = 1;			// 2D�� ��ƼŬ����
	Vector3	MoveAngle;	// �̵��� �Ѵٸ� ������ �� �������κ��� x, y, z �� ����� ������ŭ Ʋ���� ������ ������ ���Ѵ�.
	float	Empty = 0.f;
};

struct ParticleInfo
{
	Vector3	WorldPos;
	Vector3	Dir;
	float	Speed;
	float	LifeTime;
	float	LifeTimeMax;
	int		Alive;
	float	FallTime;
	float	FallStartY;
};

struct ParticleInfoShared
{
	unsigned int	SpawnEnable;
	Vector3	ScaleMin;
	Vector3	ScaleMax;
	Vector4	ColorMin;
	Vector4	ColorMax;
	int		GravityEnable;
};

struct GlobalCBuffer
{
	float	DeltaTime = 0.f;
	float	AccTime = 0.f;
	Vector2	Resolution;
	Vector2	NoiseResolution;
	Vector2	Empty;
};

struct PaperBurnCBuffer
{
	Vector4	InLineColor;
	Vector4	OutLineColor;
	Vector4	CenterLineColor;
	float	Filter;
	int		Inverse;
	float	InFilter;
	float	OutFilter;
	float	CenterFilter;
	Vector3	Empty;
};

struct TileMapCBuffer
{
	Vector2 ImageSize;
	Vector2 Size;
	Vector2 Start;
	Vector2 End;
	Matrix  matWVP;
};

struct TileInfo
{
	Matrix matWVP;
	Vector2 TileStart;
	Vector2 TileEnd;
	Vector4 TileColor;
	float Opacity = 0.f;;
	Vector3 Empty;
};

struct NavWorkData
{
	std::function<void(const std::list<Vector3>&)>	Callback;
	Vector3		Start;
	Vector3		End;
};

struct NavResultData
{
	std::function<void(const std::list<Vector3>&)>	Callback;
	std::list<Vector3>	vecPath;
};

struct PlayerInfo
{
	float	HP;
	float	MoveSpeed;

	PlayerInfo()	:
		HP(10.f),
		MoveSpeed(100.f)
	{
	}
};

struct MonsterInfo
{
	float	HP;
	float	MoveSpeed;
	float	Damage;
	float	AttackDelayMax;

	MonsterInfo() :
		HP(10.f),
		MoveSpeed(100.f),
		Damage(1.f),
		AttackDelayMax(1.f)
	{
	}
};

struct BossInfo
{
	float	HP;
	float	MoveSpeed;
	float	Damage;

	BossInfo() :
		HP(100.f),
		MoveSpeed(100.f),
		Damage(1.f)
	{
	}
};