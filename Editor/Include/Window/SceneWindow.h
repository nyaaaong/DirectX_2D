#pragma once
#include "IMGUIWindow.h"
class CSceneWindow :
    public CIMGUIWindow
{
public:
	CSceneWindow();
	virtual ~CSceneWindow();

private:

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

