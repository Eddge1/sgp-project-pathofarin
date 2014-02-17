#pragma once
#include "Minigames.h"
#include "Units.h"
#include "BattleState.h"
#include "AIController.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include <sstream>
#include <vector>
using namespace std;


class CAIOrcLeader : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;

	int m_nAttk;
	int m_nHurt;
	int m_nSpell;
	int m_nRage;

	bool m_bPrepare;
	int m_nTurns;

public:

	virtual void Update(float fElapsedTime );
	virtual void Render(void);


	CAIOrcLeader(void);
	virtual ~CAIOrcLeader(void);
};

