#pragma once
#include "minigames.h"
class CSteadyShot :
	public CMiniGames
{
public:
	CSteadyShot(void);
	virtual ~CSteadyShot(void);
	virtual void ResetSkill() override { }
	virtual void HandleEvent( const CEvent* pEvent ) override {}
	virtual void DoAttack(void) override {}

};

