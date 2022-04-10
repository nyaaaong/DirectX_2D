#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/StartWidget.h"

class CEndingScene :
	public CSceneMode
{
public:
	CEndingScene();
	virtual ~CEndingScene();

private:

public:
	virtual void Start();
	virtual bool Init();

private:
	void CreateSound();
};