#pragma once
#include "Minigames.h"
#include "Units.h"
#include "BattleState.h"
#include "AIController.h"
#include <sstream>
#include <vector>
using namespace std;


class CAIOrcLeader : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;

	bool m_bPrepare;
	int m_nTurns;

public:

	virtual void Update(float fElapsedTime );
	virtual void Render(void);


	CAIOrcLeader(void);
	virtual ~CAIOrcLeader(void);
};

