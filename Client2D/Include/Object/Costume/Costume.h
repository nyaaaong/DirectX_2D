#pragma once

#include "../Player2D.h"

class CCostume :
    public CPlayer2D
{
	friend class CScene;

protected:
	CCostume();
	CCostume(const CCostume& obj);
	virtual ~CCostume();

private:
	CPlayer2D* m_Player;
	CSharedPtr<CSpriteComponent>	m_PlayerSprite;
	CSharedPtr<CSpriteComponent>	m_CostumeComponentLeft;
	CSharedPtr<CSpriteComponent>	m_CostumeComponentRight;

public:
	void SetPlayer(CPlayer2D* Player)
	{
		m_Player = Player;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CCostume* Clone();
};

