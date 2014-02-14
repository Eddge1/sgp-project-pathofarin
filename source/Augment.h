#pragma once
#include "Item.h"
#include <string>
using namespace std;

class CAugment : public CItem
{
	float Effect;
	string Type;
public:
	float GetEffect(void) { return Effect;}
	void SetEffect(float input) { Effect = input; }
	string GetAugType(void) { return Type; }
	void SetAugType(string input) { Type = input; }
	CAugment(void);
	virtual ~CAugment(void);
};

