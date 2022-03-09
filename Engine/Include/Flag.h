
#pragma once

enum class Engine_Space
{
	Space2D,
	Space3D
};

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX
};

enum class Buffer_Type
{
	Vertex,
	Index
};

enum class Shader_Type
{
	Graphic,
	Compute
};

enum class Buffer_Shader_Type
{
	Vertex = 0x1,
	Pixel = 0x2,
	Domain = 0x4,
	Hull = 0x8,
	Geometry = 0x10,
	Compute = 0x20,
	Graphic = Vertex | Pixel | Domain | Hull | Geometry,
	All = Vertex | Pixel | Domain | Hull | Geometry | Compute
};

enum class Component_Type
{
	SceneComponent,
	ObjectComponent
};

enum class Input_Type
{
	Direct,
	Window
};

enum Key_State
{
	KeyState_Down,
	KeyState_Push,
	KeyState_Up,
	KeyState_Max
};

enum class Image_Type
{
	Atlas,
	Frame,
	Array
};

enum class Sampler_Type
{
	Point,
	Linear,
	Anisotropic
};

enum class RenderState_Type
{
	Blend,
	Rasterizer,
	DepthStencil,
	Max
};

enum Radio_Type
{
	RT_NONE,
	RT_TEST,
	RT_MAX
};

enum Edit_Mode
{
	EM_CAPTURE,
	EM_DRAG
};

enum class SceneComponent_Type
{
	Sprite,
	StaticMesh,
	Box2D,
	Circle,
	Pixel,
	Camera,
	Widget,
	Particle,
	TileMap,
	Max
}; 

enum class Collision_Channel
{
	Object,
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
	Custom1,
	Custom2,
	Custom3,
	Custom4,
	Custom5,
	Custom6,
	Custom7,
	Custom8,
	Custom9,
	Custom10,
	Custom11,
	Custom12,
	Custom13,
	Custom14,
	Custom15,
	Custom16,
	Max
};

enum class Collision_Interaction
{
	Ignore,
	Collision
};

enum class Collision_State
{
	Begin,
	End,
	Max
};

enum class Collider_Type
{
	Box2D,
	Circle,
	Pixel
};

enum class Camera_Type
{
	Camera2D,
	Camera3D,
	CameraUI
};

enum class PixelCollision_Type
{
	Color_Ignore,
	Color_Confirm,
	Alpha_Ignore,
	Alpha_Confirm
};

enum class Button_State
{
	Normal,
	MouseOn,
	Click,
	Disable,
	Max
};

enum class Button_Sound_State
{
	MouseOn,
	Click,
	Max
};

enum class WidgetComponent_Space
{
	Screen,
	World
};

enum class ProgressBar_Dir
{
	RightToLeft,
	LeftToRight,
	TopToBottom,
	BottomToTop
};

enum class Mouse_State
{
	Normal,
	State1,
	State2,
	State3,
	State4,
	State5,
	State6,
	State7,
	State8,
	State9,
	State10,
	Max
};

enum class Tile_Type
{
	Normal,
	Wall,
	End
};

enum class Nav_Node_Type
{
	None,
	Open,
	Close
};

enum class Component_Flag
{
	Sprite = 0x1,
	StaticMesh = 0x2,
	Box2D = 0x4,
	Circle = 0x8,
	Pixel = 0x10,
	Camera = 0x20,
	Widget = 0x40,
	Particle = 0x80,
	TileMap = 0x100
};

enum class Character_Direction
{
	Down = 0x1,
	Left = 0x2,
	Right = 0x4,
	Up = 0x8,
	DownLeft = Down | Left,
	DownRight = Down | Right,
	UpLeft = Up | Left,
	UpRight = Up | Right,
	All = Down | Left | Right | Up
};

enum class Move_Dir
{
	LB,
	B,
	RB,
	L,
	R,
	LT,
	T,
	RT,
	End
};

enum class Weapon_Slot
{
	None,
	Weap1,
	Weap2,
	Weap3
};

enum class Character_Type
{
	Player,
	Monster
};