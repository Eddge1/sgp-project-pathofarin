#pragma once
#include "AIController.h"
#include "Units.h"
#include "BattleState.h"
#include "Minigames.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include <sstream>
#include <vector>
using namespace std;

class CAIBasicHealer : CAIController
{

	vector<CUnits*> m_vBattleUnits;
	CUnits* m_pTarget;
	int m_nTurns;

public:

	int m_nTree;
	int m_nBat;
	int m_nManDrake;
	int m_nSnake;
	int m_nCult;
	int m_nOrcSha;

	virtual void Update(float fElapsedTime );
	virtual void Render(void);

	CAIBasicHealer(void);
	~CAIBasicHealer(void);
};

