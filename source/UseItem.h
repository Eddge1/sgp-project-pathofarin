#pragma once
#include "minigames.h"
class CUseItem :
	public CMiniGames
{


public:

	float timer;
	virtual void Update(float fElapsedTime);
	virtual void Render(void);


	CUseItem(void);
	virtual ~CUseItem(void);
	virtual void ResetSkill() override { }

};

