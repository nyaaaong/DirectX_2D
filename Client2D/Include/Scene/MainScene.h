#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/MainWidget.h"

class CMainScene :
    public CSceneMode
{
public:
    CMainScene();
    ~CMainScene();

private:
	CSharedPtr<CMainWidget> m_MainWidget;

public:
    virtual bool Init();

private:
	void CreateMaterial();
	void CreateAnimationSequence();
};

