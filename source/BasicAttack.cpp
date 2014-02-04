#include "BasicAttack.h"
#include "Game.h"
#include "BitmapFont.h"
#include "GamePlayState.h"


CBasicAttack::CBasicAttack(void)
{

}


CBasicAttack::~CBasicAttack(void)
{

}

void CBasicAttack::DoAttack(void)
{
	if(GetOwner()->GetType() == OBJ_PLAYER_UNIT)
	{
		CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
		if(GetOwner() != nullptr)
		{

			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(temp, false);
			GetOwner()->EndTurn();
		}
	}
	else
	{
		CUnits* tempP = CGamePlayState::GetInstance()->GetPlayerUnit();
		if(tempP != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(temp, false);
			GetOwner()->EndTurn();
		}
	}
}

void CBasicAttack::Update(float fElapsedTime)
{
	DoAttack();
}