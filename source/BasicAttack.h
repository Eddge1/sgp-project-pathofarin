#pragma once
#include "minigames.h"
#include "BattleState.h"
#include "Units.h"

class CBasicAttack : public CMiniGames
{

	CUnits* m_pTarget;

public:

	void DoAttack(void);

	CUnits* GetTarget(void) { return m_pTarget; }
	void SetTarget(CUnits* l) { m_pTarget = l; }


	CBasicAttack(void);
	virtual ~CBasicAttack(void);
};