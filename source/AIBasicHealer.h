#pragma once
#include "AIController.h"
#include "Units.h"
#include "BattleState.h"
#include "Minigames.h"
#include <sstream>
#include <vector>
using namespace std;

class CAIBasicHealer : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;
	int m_nTurns;

public:

	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAIBasicHealer(void);
	~CAIBasicHealer(void);
};

