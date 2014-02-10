#pragma once
#include "minigames.h"
#include "BattleState.h"
#include "Units.h"

class CBasicAttack : public CMiniGames
{

	CUnits* m_pTarget;
	bool bAttacked;
public:

	virtual void Update(float fElapsedTime) override;

	virtual void DoAttack(void) override;

	CUnits* GetTarget(void) { return m_pTarget; }
	void SetTarget(CUnits* l) { m_pTarget = l; }
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override;

	CBasicAttack(void);
	virtual ~CBasicAttack(void);
};