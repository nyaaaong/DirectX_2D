#pragma once

#include "IMGUIWindow.h"

class CSpriteWindow :
    public CIMGUIWindow
{
public:
	CSpriteWindow();
	virtual ~CSpriteWindow();

private:
	class CIMGUIImage* m_Sprite;
	class CIMGUIImage* m_SpriteFrame;
	class CIMGUIListBox* m_AnimationList;
	class CIMGUIListBox* m_AnimationFrameList;
	class CIMGUITextInput* m_AnimName;
	class CIMGUITextInput* m_AnimSizeX;
	class CIMGUITextInput* m_AnimSizeY;
	class CIMGUITextInput* m_AnimStartFrameX;
	class CIMGUITextInput* m_AnimStartFrameY;
	class CIMGUITextInput* m_AnimEndFrameX;
	class CIMGUITextInput* m_AnimEndFrameY;
	class CIMGUIRadio* m_Capture;
	class CIMGUIRadio* m_Drag;
	class CIMGUIButton* m_PlayAnimButton;
	class CAnimationSequence2DInstance* m_AnimInstance;
	CSharedPtr<class CSpriteEditObject> m_SpriteObject;
	std::vector<class CIMGUIWidget*>	m_vecTreeStorage;
	int					m_Mode;
	bool				m_PlayAnim;

public:
	int GetCaptureMode()	const
	{
		return m_Mode;
	}

	CSharedPtr<class CSpriteEditObject> GetSpriteObject()	const
	{
		return m_SpriteObject;
	}

public:
	Vector3 GetSpriteSize()	const;

public:
	virtual bool Init();
	virtual bool Start();
	virtual void Update(float DeltaTime);

private:
	void LoadTextureButton();
	void AddSequenceButton();
	void SelectAnimation(int Index, const char* Item);
	void SelectAnimationFrame(int Index, const char* Item);
	void DeleteSequenceButton();
	void AddAnimationFrameButton();
	void DeleteFrameButton();
	void ClearFrameButton();
	void PlayAnimation();
	void InputSize(const Vector2& size);
	void InputStartFrameData(const Vector2& Data);
	void InputEndFrameData(const Vector2& Data);
	void SaveSequence();
	void LoadSequence();
	void ClearSequenceList();

public:
	void RefreshInput();
	
private:
	void CaptureMode();
	void Modify();
	void DeleteAnimation(const std::string& SequenceName);
	void AddListBoxData(const std::string& SequenceName);
	void AddFrameListBoxData(const std::string& SequenceName);
};

