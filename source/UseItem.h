#pragma once
#include "minigames.h"
class CUseItem :
	public CMiniGames
{
public:
	CUseItem(void);
	virtual ~CUseItem(void);
	virtual void ResetSkill() override { }

};

