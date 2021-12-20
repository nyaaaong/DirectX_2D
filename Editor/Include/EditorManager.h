#pragma once

#include "GameInfo.h"

enum class EditMode
{
	Scene,
	Sprite
};

class CEditorManager
{
private:
	EditMode	m_EditMode;
	class CDragObject* m_DragObj;
	class CSpriteWindow* m_SpriteWindow;
	class CDetailWindow* m_DetailWindow;
	class CEditorMenu* m_EditorMenu;
	class CObjectHierarchy* m_ObjectHierarchy;

public:
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
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

public:
	void MouseLButtonDown(float DeltaTime);
	void MouseLButtonPush(float DeltaTime);
	void MouseLButtonUp(float DeltaTime);

	void KeyboardUp(float DeltaTime);
	void KeyboardDown(float DeltaTime);
	void KeyboardLeft(float DeltaTime);
	void KeyboardRight(float DeltaTime);

	DECLARE_SINGLE(CEditorManager)
};

