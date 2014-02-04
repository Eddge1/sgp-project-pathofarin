#pragma once
#include "AIController.h"
#include "Units.h"
#include "BattleState.h"
#include "Minigames.h"
#include <sstream>
#include <vector>
using namespace std;

class CAIBrute : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;
	bool m_bPrepare;
	bool m_bRaged;
	int m_nTurns;

public:

	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAIBrute(void);
	virtual ~CAIBrute(void);
};

