#include "BasicAttack.h"
#include "Game.h"
#include "BitmapFont.h"
#include "GamePlayState.h"
#include "TutorialBattle.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CBasicAttack::CBasicAttack(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("BASIC_ATTACK", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("START_AUDIO", this);

	m_nSound = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Enemies/POA_tempEnemey.wav"));
	m_nOrcLeader = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcSiegeLeader_Attack.wav"));
	m_nPathOrc = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_PathOrc_Attack.wav"));
	bAttacked = false;
	bhasPlayed = false;
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
			tempP = CGamePlayState::GetInstance()->GetPlayerUnit();
		else
			tempP = reinterpret_cast<CUnits*>(CTutorialBattle::GetInstance()->GetPlayerUnit());

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
	else
	{
		string szTemp = GetOwner()->GetName() + "_Battle_Basic_Attack";
		GetOwner()->GetAnimInfo()->SetAnimation(szTemp.c_str());
		bAttacked = true;
		bhasPlayed = false;
	}
}
void CBasicAttack::ResetSkill()
{
	bAttacked = false;
	bhasPlayed = false;
}
void CBasicAttack::HandleEvent( const CEvent* pEvent )
{


	if (pEvent->GetEventID() == "START_AUDIO" && !bhasPlayed)
	{
		if(GetOwner() != nullptr)
		{
			if(GetOwner()->GetName() == "Orc_Leader")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeader);
			else if(GetOwner()->GetName() == "Orc")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeader);
			else if(GetOwner()->GetName() == "Orc_Shaman")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeader);
			else if(GetOwner()->GetName() == "Bat")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeader);
			else if(GetOwner()->GetName() == "Spider")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeader);
			else if(GetOwner()->GetName() == "Pathetic_Orc")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nPathOrc);


			bhasPlayed = true;
		}

	}

	if (pEvent->GetEventID() == "BASIC_ATTACK" && bAttacked)
	{
		bAttacked = false;
		DoAttack();
	}


}