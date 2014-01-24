#pragma once
#include "units.h"
#include <string>
using namespace std;


class CEnemyUnit :	public CUnits
{
	CObjects* m_pTarget;

public:

	CEnemyUnit(void);
	virtual ~CEnemyUnit(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;

};

