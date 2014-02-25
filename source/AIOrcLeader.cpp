#include "AIOrcLeader.h"
#include "Buff.h"

CAIOrcLeader::CAIOrcLeader(void)
{
	m_bPrepare = false;
	m_nTurns = 0;
	m_nAttk = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcSiegeLeader_Attack.wav"));
	m_nSpell = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcSiegeLeader_Spell.wav"));
	m_nRage = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcSiegeLeader_PowerAttack.wav"));
}


CAIOrcLeader::~CAIOrcLeader(void)
{
}


void CAIOrcLeader::Update(float fElapsedTime )
{

	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();


	if(m_bPrepare)
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_pTarget = m_vBattleUnits[i];
				break;
			}
		}
		//int temp = GetOwner()->GetAttack();
		//GetOwner()->SetAttack(GetOwner()->GetAttack() * 4);
		//GetMinigame()->SetOwner(GetOwner());
		//GetMinigame()->Update(fElapsedTime);
		//GetOwner()->SetAttack(GetOwner()->GetAttack() / 4);



		m_pTarget->ModifyHealth(GetOwner()->GetAttack() * 4, false);
		CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nAttk);
		m_pTarget = nullptr;
		m_bPrepare = false;
		GetOwner()->EndTurn();
	}
	else if(m_nTurns >= 3)
	{
		if(GetOwner()->GetHealth() < GetOwner()->GetMaxHealth() * 0.75)
		{
			int tempRestore = GetOwner()->GetMaxHealth() / 4; // TODO: add random values
			GetOwner()->ModifyHealth(-tempRestore, false);

			//Heal Animation:
			CBuff* pHeal = new CBuff();
			pHeal->SetPosX(GetOwner()->GetPosX());
			pHeal->SetPosY(GetOwner()->GetPosY());
			pHeal->GetAnimInfo()->SetAnimation("Enemy_Heal");
			CBattleState::GetInstance()->AddSkill(pHeal);
			pHeal->Release();

			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSpell);
			m_pTarget = nullptr;
			m_nTurns = 0;
			GetOwner()->EndTurn();
			return;
		}


		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
			{
				if(m_vBattleUnits[i]->GetHealth() < m_vBattleUnits[i]->GetMaxHealth() / 2)
				{
					m_pTarget = m_vBattleUnits[i];
					break;
				}
			}
		}

		if(m_pTarget != nullptr)
		{
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSpell);
			m_pTarget->ModifyHealth(-m_pTarget->GetMaxHealth() / 3, false);

			//Heal Animation:
			CBuff* pHeal = new CBuff();
			pHeal->SetPosX(GetOwner()->GetPosX());
			pHeal->SetPosY(GetOwner()->GetPosY());
			pHeal->GetAnimInfo()->SetAnimation("Enemy_Heal_Other");
			CBattleState::GetInstance()->AddSkill(pHeal);
			pHeal->Release();

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

			if(m_pTarget->GetHealth() - GetOwner()->GetAttack() * 2 <= 5)
			{
				m_bPrepare = true;
				wostringstream woss;
				woss << "Prepare";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nRage);
				m_pTarget = nullptr;
				m_nTurns += 1;
				GetOwner()->EndTurn();
			}
			else if(m_nTurns > 2 && rand()%100 + 1 > 75)
			{
				m_bPrepare = true;
				wostringstream woss;
				woss << "Prepare";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nRage);
				m_pTarget = nullptr;
				m_nTurns += 1;
				GetOwner()->EndTurn();
			}
			else
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

		if(m_pTarget->GetHealth() - GetOwner()->GetAttack() * 2 <= 5)
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nRage);
			m_pTarget = nullptr;
			m_nTurns += 1;
			GetOwner()->EndTurn();
		}
		else if(m_nTurns > 2 && rand()%100 + 1 > 75)
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nRage);
			m_pTarget = nullptr;
			m_nTurns += 1;
			GetOwner()->EndTurn();
		}
		else
		{
			GetMinigame()->SetOwner(GetOwner());
			GetMinigame()->Update(fElapsedTime);
			m_pTarget = nullptr;
			m_nTurns += 1;
		}


	}

}


void CAIOrcLeader::Render(void)
{

}

