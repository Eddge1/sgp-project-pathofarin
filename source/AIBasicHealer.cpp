#include "AIBasicHealer.h"
#include "Buff.h"

CAIBasicHealer::CAIBasicHealer(void)
{
	m_pTarget = nullptr;
	m_nTurns = 0;
	m_nManDrake = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_ThornBiter_Spell.wav"));
	m_nTree = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_tempEnemey.wav"));
	m_nBat = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Bat_Attack.wav"));
	m_nSnake = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Snake_Spell.wav"));
	m_nOrcSha = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcShaman_CastSpell.wav"));
	m_nCult = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_Cult_Spell.wav"));


}


CAIBasicHealer::~CAIBasicHealer(void)
{

}

void CAIBasicHealer::Update(float fElapsedTime)
{
	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();

	if(m_nTurns >= 3 && GetOwner()->GetHealth() < GetOwner()->GetMaxHealth() / 2)
	{
		int tempRestore = GetOwner()->GetMaxHealth() / 3; // TODO: add random values
		GetOwner()->ModifyHealth(-tempRestore, false);
		m_pTarget = nullptr;
		m_nTurns = 0;
		GetOwner()->EndTurn();

		//Heal Animation
		CBuff* pHeal = new CBuff();
		pHeal->SetPosX(GetOwner()->GetPosX());
		pHeal->SetPosY(GetOwner()->GetPosY());
		pHeal->GetAnimInfo()->SetAnimation("Enemy_Heal");
		CBattleState::GetInstance()->AddSkill(pHeal);
		pHeal->Release();

		if(GetOwner()->GetName() == "Cave_Bat")
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nBat);
		else if(GetOwner()->GetName() == "Orc_Shaman")
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcSha);
		else if(GetOwner()->GetName() == "Snake")
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSnake);
		else if(GetOwner()->GetName() == "Mandrake")
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nManDrake);
		else if(GetOwner()->GetName() == "Cultist")
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nCult);


	}
	else if(m_nTurns >= 3)
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
			{
				if(m_vBattleUnits[i]->GetHealth() <= m_vBattleUnits[i]->GetMaxHealth() * 0.75)
				{ 
					m_pTarget = m_vBattleUnits[i];
					break;
				}
			}
		}


		if(m_pTarget != nullptr)
		{
			CBuff* pHeal = new CBuff();
			pHeal->SetPosX(GetOwner()->GetPosX());
			pHeal->SetPosY(GetOwner()->GetPosY());
			pHeal->GetAnimInfo()->SetAnimation("Enemy_Heal_Other");
			CBattleState::GetInstance()->AddSkill(pHeal);
			pHeal->Release();

			m_pTarget->ModifyHealth(-m_pTarget->GetMaxHealth() / 3, false);
			m_pTarget = nullptr;
			m_nTurns = 0;
			GetOwner()->EndTurn();
		}
		else
		{
			for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
			{
				if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
					m_pTarget = m_vBattleUnits[i];
			}
			if(m_pTarget != nullptr)
			{
				GetMinigame()->SetOwner(GetOwner());
				GetMinigame()->Update(fElapsedTime);
				m_pTarget = nullptr;
				m_nTurns += 1;
			}

		}

	}
	else
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
				m_pTarget = m_vBattleUnits[i];
		}
		if(m_pTarget != nullptr)
		{
			GetMinigame()->SetOwner(GetOwner());
			GetMinigame()->Update(fElapsedTime);
			m_pTarget = nullptr;
			m_nTurns += 1;
		}
	}
}

void CAIBasicHealer::Render(void)
{

}
