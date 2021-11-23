#pragma once

#include "../Ref.h"

class CSceneMode	:
	public CRef
{
	friend class CScene;

protected:
	CSceneMode();
	virtual ~CSceneMode();

private:
	class CScene* m_Scene;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
};

