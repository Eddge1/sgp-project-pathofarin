#pragma once
#include "Minigames.h"
#include "Units.h"

class CAIController
{

	CMiniGames* m_pMiniGame;
	CUnits* m_pOwner;

public:

	virtual void MakeOwner(CUnits* l) final { m_pOwner = l; }
	virtual CUnits* GetOwner( void ) final { return m_pOwner; }
	virtual void AddMinigame(CMiniGames* l) final { m_pMiniGame = l; }
	virtual CMiniGames* GetMinigame(void) { return m_pMiniGame; }

	virtual void Update(float fElapsedTime );
	virtual void Render(void);


	CAIController(void);
	virtual ~CAIController(void);
};

