#pragma once
#include "Minigames.h"
#include "Units.h"
#include "BattleState.h"
#include "AIController.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include <sstream>
#include <vector>
using namespace std;


class CAITigerlily : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	//vector<int> m_vMinionHealth;
	CUnits* m_pTarget;

	int m_nTurns;
	int m_nAoeHeal;
	int m_nSpellSfx;

public:


	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAITigerlily(void);
	~CAITigerlily(void);
};

