#pragma once

#include "../Ref.h"

class CSceneMode :
    public CRef
{
	friend class CScene;

protected:
	CSceneMode();
	virtual ~CSceneMode();

private:
	class CScene* m_pScene;

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
};

