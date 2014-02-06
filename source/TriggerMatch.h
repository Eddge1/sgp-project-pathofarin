#pragma once
#include "minigames.h"
class CTriggerMatch :
	public CMiniGames
{
public:
	CTriggerMatch(void);
	virtual ~CTriggerMatch(void);
	virtual void ResetSkill() override { }
	virtual void HandleEvent( const CEvent* pEvent ) override { }

};

