#pragma once
enum ItemTypes {IT_UNDEFINE, IT_CONSUMABLE, IT_ARMOR, IT_WEAPON};
#include <string>
#include "AnimationTimeStamp.h"
using namespace std;


class CItem
{
	string m_sName;
	ItemTypes m_eType;
	CAnimationTimeStamp* m_aAnimationTimeInfo;

public:
	string GetName(void) { return m_sName; }
	void SetName(string input) { m_sName = input; }
	CItem(void);
	virtual ~CItem(void);
	virtual ItemTypes GetItemType() const final {return m_eType;}
	virtual void SetItemType(ItemTypes eType) final {m_eType = eType;}

	CAnimationTimeStamp* GetAnimInfo() {return m_aAnimationTimeInfo;}
};

