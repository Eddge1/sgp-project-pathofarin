#pragma once
#include "item.h"
class CWeapon :
	public CItem
{
	int Attack;

public:



	int GetAttack(void) { return Attack;}
	void SetAttack(int input) { Attack = input; }

	CWeapon(void);
	virtual ~CWeapon(void);
};

