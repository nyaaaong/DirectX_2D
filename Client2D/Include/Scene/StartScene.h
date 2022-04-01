#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/StartWidget.h"

class CStartScene :
	public CSceneMode
{
public:
	CStartScene();
	virtual ~CStartScene();

private:
	CSharedPtr<CStartWidget> m_StartWidget;

public:
	virtual void Start();
	virtual bool Init();

private:
	void CreateSound();
};

