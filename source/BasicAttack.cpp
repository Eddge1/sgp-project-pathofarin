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
	m_nSpider = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Spider_Attack.wav"));
	m_nBandit = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Bandit_Attack.wav"));
	m_nBat = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Bat_Attack.wav"));
	m_nOrcSha = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcShaman_Attack.wav"));
	m_nOrc = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_PathOrc_Attack.wav"));
	m_nThornBiter = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_ThornBiter_Attack.wav"));
	m_nGolem = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Golem_Attack.wav"));
	m_nShade = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Shade_Attack.wav"));
	m_nOgre = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Ogre_Attack.wav"));
	m_nSnake = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Snake_Attack.wav"));
	m_nValrion = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Valrion_Attack.wav"));
	m_nSnail = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Snail_Attack.wav"));
	m_nTree = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Tree_Attack.wav"));
	m_nBee = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Bee_Attack.wav"));

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
			tempP = reinterpret_cast<CUnits*>(CGamePlayState::GetInstance()->GetPlayerUnit());
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
		if(GetOwner()->GetClass () == UC_WARRIOR || GetOwner()->GetClass () == UC_NONE)
			GetOwner()->GetAnimInfo()->SetAnimation("Warrior_Battle_Basic_Attack");
		else if(GetOwner()->GetClass () == UC_MAGE)
			GetOwner()->GetAnimInfo()->SetAnimation("Mage_Battle_Basic_Attack");
		else if(GetOwner()->GetClass () == UC_RANGER)
			GetOwner()->GetAnimInfo()->SetAnimation("Ranger_Battle_Basic_Attack");

		bAttacked = true;
	}
	else
	{
		string szTemp = GetOwner()->GetName() + "_Battle_Basic_Attack";
		CSGD_EventSystem::GetInstance()->SendEventNow("DODGE");
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
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nPathOrc);
			else if(GetOwner()->GetName() == "Orc_Shaman")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcSha);
			else if(GetOwner()->GetName() == "Cave_Bat")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nBat);
			else if(GetOwner()->GetName() == "Cave_Spider")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSpider);
			else if(GetOwner()->GetName() == "Pathetic_Orc")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nPathOrc);
			else if(GetOwner()->GetName() == "Snail")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSnail);
			else if(GetOwner()->GetName() == "Tree")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nTree);
			else if(GetOwner()->GetName() == "Ogre")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOgre);
			else if(GetOwner()->GetName() == "Thornbiter")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nThornBiter);
			else if(GetOwner()->GetName() == "Mandrake")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nThornBiter);
			else if(GetOwner()->GetName() == "Shade")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nShade);
			else if(GetOwner()->GetName() == "TigerLily")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nThornBiter);
			else if(GetOwner()->GetName() == "Valrion")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nValrion);
			else if(GetOwner()->GetName() == "Bandit")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nBandit);
			else if(GetOwner()->GetName() == "Golem")
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nGolem);
			bhasPlayed = true;
		}
	}

	if (pEvent->GetEventID() == "BASIC_ATTACK" && bAttacked)
	{
		bAttacked = false;
		DoAttack();
	}


}