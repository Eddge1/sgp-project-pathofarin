#include "BasicAttack.h"
#include "Game.h"
#include "BitmapFont.h"


CBasicAttack::CBasicAttack(void)
{

}


CBasicAttack::~CBasicAttack(void)
{
}

void CBasicAttack::DoAttack(void)
{
	CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
	if(GetOwner() != nullptr)
	{

		int temp = GetOwner()->GetAttack();
		tempP->ModifyHealth(temp, false);
		GetOwner()->EndTurn();
	}
}

void CBasicAttack::Update(float fElapsedTime)
{
	DoAttack();
}