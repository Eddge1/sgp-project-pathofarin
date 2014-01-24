#include "EnemyUnit.h"


CEnemyUnit::CEnemyUnit(void)
{
	SetType(OBJ_ENEMY_UNIT);
	m_pTarget = nullptr;
}


CEnemyUnit::~CEnemyUnit(void)
{
}

void CEnemyUnit::HandleEvent( const CEvent* pEvent )
{


}