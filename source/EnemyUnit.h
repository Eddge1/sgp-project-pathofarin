#pragma once
#include "units.h"
#include "AIController.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include <string>
using namespace std;


class CEnemyUnit :	public CUnits
{
	CObjects* m_pTarget;
	float m_fTimerToSlow;
	CAIController* m_pMaster;
	bool m_bEventSent;

public:

	void SetAIController(CAIController* l) { m_pMaster = l; }

	CEnemyUnit(void);
	virtual ~CEnemyUnit(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void Update(float fElapsedTime) override;

};

