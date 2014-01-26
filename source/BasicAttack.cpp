#include "BasicAttack.h"


CBasicAttack::CBasicAttack(void)
{

}


CBasicAttack::~CBasicAttack(void)
{
}

void CBasicAttack::DoAttack(void)
{
	CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
	int temp = GetOwner()->GetAttack();
	tempP->ModifyHealth(-temp, false);
	GetOwner()->EndTurn();
}