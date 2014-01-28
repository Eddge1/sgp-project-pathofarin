#pragma once
#include "Minigames.h"
#include "Units.h"

class CAIController
{

	CMiniGames* m_pMiniGame;
	CUnits* m_pOwner;

public:

	virtual void MakeOwner(CUnits* l) { m_pOwner = l; }
	void AddMinigame(CMiniGames* l) { m_pMiniGame = l; }


	virtual void Update(float fElapsedTime );
	virtual void Render(void);


	CAIController(void);
	virtual ~CAIController(void);
};

