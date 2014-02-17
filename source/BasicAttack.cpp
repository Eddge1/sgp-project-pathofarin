#include "BasicAttack.h"
#include "Game.h"
#include "BitmapFont.h"
#include "GamePlayState.h"
#include "TutorialBattle.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CBasicAttack::CBasicAttack(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("BASIC_ATTACK", this);
	m_nSound = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Enemies/POA_tempEnemey.wav"));

	bAttacked = false;
}

CBasicAttack::~CBasicAttack(void)
{

}

void CBasicAttack::DoAttack(void)
{
	if(GetOwner()->GetType() == OBJ_PLAYER_UNIT)
	{
		CUnits* tempP;

		if(!GetTutorial())
			 tempP = CBattleState::GetInstance()->GetCurrentTarget();
		else
			 tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			GetOwner()->ModifyAP(-int((temp * 2 * 0.2f)));
			tempP->ModifyHealth(temp * 2, false);
			if(!GetTutorial())
				GetOwner()->EndTurn();
			else
			{
				CTutorialBattle::GetInstance()->SetPlayerTurn(false);
				GetOwner()->EndTurn();
			}
		}
	}
	else
	{
		CUnits* tempP;

		if(!GetTutorial())
			tempP = reinterpret_cast<CUnits*>(CGamePlayState::GetInstance()->GetPlayerUnit());
		else
			tempP = reinterpret_cast<CUnits*>(CTutorialBattle::GetInstance()->GetPlayerUnit());

		if(tempP != nullptr)
		{
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSound);
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
	else
	{
		string szTemp = GetOwner()->GetName() + "_Battle_Basic_Attack";
		GetOwner()->GetAnimInfo()->SetAnimation(szTemp.c_str());
		bAttacked = true;
	}
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