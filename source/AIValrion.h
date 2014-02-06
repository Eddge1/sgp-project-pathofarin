#pragma once
#include "Minigames.h"
#include "Units.h"
#include "BattleState.h"
#include "AIController.h"
#include <sstream>
#include <vector>
using namespace std;


class CAIValrion : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;
	bool m_bPrepare;
	bool Cataclysm;
	bool once;
	int m_nSincePrepare;
	int m_nTurns;
	int m_nLifeDevoured;
	int m_nAttempts;
	int m_nRageCount;

public:
	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAIValrion(void);
	~CAIValrion(void);
};

