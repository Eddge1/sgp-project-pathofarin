#pragma once
#include "minigames.h"
class CPrecisionStrike :
	public CMiniGames
{
public:
	CPrecisionStrike(void);
	virtual ~CPrecisionStrike(void);
	virtual void ResetSkill() override { }
	virtual void HandleEvent( const CEvent* pEvent ) override { }

};

