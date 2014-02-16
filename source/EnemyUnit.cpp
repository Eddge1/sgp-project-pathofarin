#include "EnemyUnit.h"


CEnemyUnit::CEnemyUnit(void)
{
	SetType(OBJ_ENEMY_UNIT);
	m_pTarget = nullptr;
	m_fTimerToSlow = 2.0f;
	m_bEventSent = false;
}


CEnemyUnit::~CEnemyUnit(void)
{
	delete m_pMaster;
}

void CEnemyUnit::HandleEvent( const CEvent* pEvent )
{


}

void CEnemyUnit::Update(float fElapsedTime)
{ 
	if(GetTurn() && GetHealth() > 0)
	{
		if(m_bEventSent == false && m_fTimerToSlow < 1)
		{
			if(GetType() ==  OBJ_ENEMY_UNIT)
			{
				CSGD_EventSystem::GetInstance()->SendEventNow("DODGE");
				m_bEventSent = true;
			}
		}

		m_fTimerToSlow -= fElapsedTime;
		if(m_fTimerToSlow < 0.0f)
		{
			if(m_pMaster == nullptr)
			{
				EndTurn();
				m_fTimerToSlow = 2.0f;
				m_bEventSent = false;

			}
			else
			{
				m_pMaster->Update(fElapsedTime);
				m_fTimerToSlow = 2.0f;
				m_bEventSent = false;

			}
		}
	}
	else if(GetTurn() && GetHealth() <1 )
		EndTurn();
	CEntity::Update(fElapsedTime);
}