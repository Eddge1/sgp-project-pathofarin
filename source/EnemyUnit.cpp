#include "EnemyUnit.h"


CEnemyUnit::CEnemyUnit(void)
{
	SetType(OBJ_ENEMY_UNIT);
	m_pTarget = nullptr;
	m_fTimerToSlow = 1.0f;
}


CEnemyUnit::~CEnemyUnit(void)
{
}

void CEnemyUnit::HandleEvent( const CEvent* pEvent )
{


}

void CEnemyUnit::Update(float fElapsedTime)
{ 
	if(GetTurn())
	{
		m_fTimerToSlow -= fElapsedTime;
		if(m_fTimerToSlow < 0.0f)
		{
			EndTurn();
			m_fTimerToSlow = 1.0f;
		}
	}
}