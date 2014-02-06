#pragma once
#include "minigames.h"
class CChargeCrystal :
	public CMiniGames
{
public:
	CChargeCrystal(void);
	virtual ~CChargeCrystal(void);
	virtual void ResetSkill() override { }
	virtual void HandleEvent( const CEvent* pEvent ) override { }


};

