#pragma once

#include "GameInfo.h"

enum class EditMode
{
	Scene,
	Sprite,
	TileMap
};

class CEditorManager
{
private:
	EditMode	m_EditMode;
	class CDragObject* m_DragObj;
	class CSpriteWindow* m_SpriteWindow;
	class CEditorMenu* m_EditorMenu;
	class CObjectHierarchy* m_ObjectHierarchy;
	class CTileMapWindow* m_TileMapWindow;
	class CTileWindow* m_TileWindow;
	Vector3		m_PrevMousePos;
	Vector3		m_CurMousePos;
	bool				m_MousePush;
	float				m_CameraMoveSpeed;
	bool	m_HasTileMap;

public:
	void TileMap(bool HasTileMap)
	{
		m_HasTileMap = HasTileMap;
	}

public:
	bool HasTileMap()	const
	{
		return m_HasTileMap;
	}

	class CSpriteWindow* GetSpriteWindow()	const
	{
		return m_SpriteWindow;
	}

	class CTileMapWindow* GetTileMapWindow()	const
	{
		return m_TileMapWindow;
	}

	class CTileWindow* GetTileWindow()	const
	{
		return m_TileWindow;
	}

	bool GetLButtonPush()	const
	{
		return m_MousePush;
	}

	class CDragObject* GetDragObj()	const
	{
		return m_DragObj;
	}

	EditMode GetEditMode()
	{
		return m_EditMode;
	}

public:
	void SetEditMode(EditMode Mode);

public:
	Object_Type GetSelectObjectType();

public:
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

public:
	void Esc(float DeltaTime);

	void MouseLButtonDown(float DeltaTime);
	void MouseLButtonPush(float DeltaTime);
	void MouseLButtonUp(float DeltaTime);

	void KeyboardUp(float DeltaTime);
	void KeyboardDown(float DeltaTime);
	void KeyboardLeft(float DeltaTime);
	void KeyboardRight(float DeltaTime);

	void MoveCameraUp(float DeltaTime);
	void MoveCameraDown(float DeltaTime);
	void MoveCameraLeft(float DeltaTime);
	void MoveCameraRight(float DeltaTime);

	void MoveTabUp(float DeltaTime);
	void MoveTabDown(float DeltaTime);
	void MoveTabLeft(float DeltaTime);
	void MoveTabRight(float DeltaTime);

public:
	void CreateSceneMode(class CScene* Scene, size_t Type);
	class CGameObject* CreateObject(class CScene* Scene, size_t Type);
	class CComponent* CreateComponent(class CGameObject* Obj, size_t Type);
	void CreateAnimInstance(class CSpriteComponent* Sprite, size_t Type);

public:
	void LoadSceneObject();

public:
	DECLARE_SINGLE(CEditorManager)
};

