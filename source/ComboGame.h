#pragma once
#include "minigames.h"
class CComboGame :
	public CMiniGames
{
public:
	CComboGame(void);
	virtual ~CComboGame(void);
	virtual void ResetSkill() override { }
	virtual void HandleEvent( const CEvent* pEvent ) override { }
};

