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

public:
	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAIValrion(void);
	~CAIValrion(void);
};

