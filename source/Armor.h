#pragma once
#include "item.h"
class CArmor :
	public CItem
{

	float hp_Stat;
	float attk_Stat;
	float speed_Stat;


public:



	float GetHpStat(void) { return hp_Stat;}
	void SetHpStat(float input) { hp_Stat = input;}

	float GetAttkStat(void) { return attk_Stat; }
	void SetAttkStat(float input) {attk_Stat = input; }

	float GetSpeedStat(void) { return speed_Stat; }
	void SetSpeedStat(float input) { speed_Stat = input; }

	CArmor(void);
	virtual ~CArmor(void);
};

