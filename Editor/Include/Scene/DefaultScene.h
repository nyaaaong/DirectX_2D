#pragma once
#include "Scene/SceneMode.h"
class CDefaultScene :
	public CSceneMode
{
public:
	CDefaultScene();
	virtual ~CDefaultScene();

public:
	virtual bool Init();

private:
	bool CreateMaterial();
};

