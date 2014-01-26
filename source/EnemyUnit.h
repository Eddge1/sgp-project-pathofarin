#pragma once
#include "units.h"
#include <string>
using namespace std;


class CEnemyUnit :	public CUnits
{
	CObjects* m_pTarget;
	float m_fTimerToSlow;

public:

	CEnemyUnit(void);
	virtual ~CEnemyUnit(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void Update(float fElapsedTime) override;

};

