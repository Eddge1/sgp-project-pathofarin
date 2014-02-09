#include "BasicAttack.h"
#include "Game.h"
#include "BitmapFont.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"


CBasicAttack::CBasicAttack(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("BASIC_ATTACK", this);

	bAttacked = false;
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
			GetOwner()->ModifyAP(-(temp * 2 * 0.2f));
			tempP->ModifyHealth(temp * 2, false);
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
	if (GetOwner()->GetType() == OBJ_PLAYER_UNIT)
	{
		GetOwner()->GetAnimInfo()->SetAnimation("Warrior_Battle_Basic_Attack");
		bAttacked = true;
	}
	else if (GetOwner()->GetName() == "Tree" || GetOwner()->GetName() == "Orc" || GetOwner()->GetName() == "Snail" || GetOwner()->GetName() == "Pathetic_Orc" || GetOwner()->GetName() == "Orc_Leader" || GetOwner()->GetName() == "Orc_Shaman")
	{
		string szTemp = GetOwner()->GetName() + "_Battle_Basic_Attack";
		GetOwner()->GetAnimInfo()->SetAnimation(szTemp.c_str());
		bAttacked = true;
	}
	else 
		DoAttack();
}

void CBasicAttack::ResetSkill()
{
	bAttacked = false;
}

void CBasicAttack::HandleEvent( const CEvent* pEvent )
{
	if (pEvent->GetEventID() == "BASIC_ATTACK" && bAttacked)
	{
		bAttacked = false;
		DoAttack();
	}
}