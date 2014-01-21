#pragma once
#include "units.h"
#include <vector>
using namespace std;
#include "Commands.h"

class CPlayerUnit :
	public CUnits
{
public:

	CPlayerUnit(void);
	virtual ~CPlayerUnit(void);

private:

	bool m_bInSubMenu;
	bool m_bSkillSelected;
	vector<CCommands> m_vCommands;

};

