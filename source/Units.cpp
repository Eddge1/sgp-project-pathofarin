#include "Units.h"
#include "BattleState.h"
#include "TutorialBattle.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include <sstream>
#include "Particle.h"
#include"../SGD Wrappers/CSGD_XAudio2.h"


CUnits::CUnits(void)
{
	SetType(OBJECT_UNIT);
	m_nLevel = 1;
	m_nHealth = m_nMaxHealth = 100;
	m_nAbilityPoints = m_nMaxAbilityPoints = 100;
	m_nAttackPower = 5;
	m_nSpeed = 0;
	m_nExperience = 0; 
	m_bTurn = false;
	m_nAvailStats = 0;

	m_bTutorial = false;


	m_nOrcLeaderHurt = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/Enemies/POA_OrcSiegeLeader_Hurt.wav"));
}

CUnits::~CUnits(void)
{
	m_mInventory.clear();
}

void CUnits::ModifyHealth(int nAmount, bool isCrit, bool inMenu)
{
	std::wostringstream woss;
	m_nHealth -= nAmount;
	if(GetType() != OBJ_PLAYER_UNIT)
	{
		string szTemp = GetName() + "_Battle_Taking_Damage";
		GetAnimInfo()->SetAnimation(szTemp.c_str());
	}

	if(m_nHealth < 0)
		m_nHealth = 0;
	if(m_nHealth > GetMaxHealth())
		m_nHealth = GetMaxHealth();

	if(!inMenu)
	{
		if(isCrit)
		{
			if(nAmount < 0)
			{
				CParticle* pPart = new CParticle();
				pPart->GetAnimInfo()->SetAnimation("Health_Recover");
				pPart->SetPosX(GetPosX());
				pPart->SetPosY(GetPosY());
				woss << "+" << nAmount * -1 << " HP";
				if(!m_bTutorial)
				{
					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,0), woss);
					CBattleState::GetInstance()->AddSkill(pPart);
				}
				else
				{
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,255), woss);
				}
				pPart->Release();
			}
			else if(nAmount > 0)
			{
				CParticle* pPart = new CParticle();
				//pPart->SetAudio();
				pPart->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/General/POA_TakeDamage.wav")));
				pPart->PlaySFX();
				pPart->GetAnimInfo()->SetAnimation("Blood_Splatter");
				pPart->SetPosX(GetPosX());
				pPart->SetPosY(GetPosY());
				woss << "-" << nAmount << " HP";
				if(!m_bTutorial)
				{
					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);
					CBattleState::GetInstance()->AddSkill(pPart);
				}
				else
				{
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);
				}
				pPart->Release();
			}
			else
			{
				woss.str(_T(""));
				woss << "DODGED!";
				if(!m_bTutorial)
				{
					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);


				}
				else
				{
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);


				}
			}
		}
		else
		{
			if(nAmount < 0)
			{
				woss << "+" << (nAmount * -1) << " HP";
				CParticle* pPart = new CParticle();
				//pPart->SetAudio();
				pPart->GetAnimInfo()->SetAnimation("Health_Recover");
				pPart->SetPosX(GetPosX());
				pPart->SetPosY(GetPosY());
				if(!m_bTutorial)
				{
					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,0), woss);
					CBattleState::GetInstance()->AddSkill(pPart);


				}
				else
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,0), woss);
			}
			else if(nAmount > 0)
			{
				woss << "-" << nAmount << " HP";
				CParticle* pPart = new CParticle();
				//pPart->SetAudio();

				if(this->GetName() == "Orc_Leader")
					CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nOrcLeaderHurt);

				pPart->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/General/POA_TakeDamage.wav")));
				pPart->PlaySFX();
				pPart->GetAnimInfo()->SetAnimation("Blood_Splatter");
				pPart->SetPosX(GetPosX());
				pPart->SetPosY(GetPosY());
				if(!m_bTutorial)
				{

					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);
					CBattleState::GetInstance()->AddSkill(pPart);
				}
				else
				{
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);


				}
				pPart->Release();
			}
			else
			{
				woss.str(_T(""));
				woss << "DODGED!";
				if(!m_bTutorial)
				{
					CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);


				}
				else
				{
					CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);


				}
			}
		}
	}
}

void CUnits::ModifyAP(int nAmount, bool inMenu)
{
	m_nAbilityPoints -= nAmount;

	if(m_nAbilityPoints < 0)
		m_nAbilityPoints = 0;
	if(m_nAbilityPoints > GetMaxAP())
		m_nAbilityPoints = GetMaxAP();

	if(!inMenu)
	{
		if(nAmount < 0)
		{	
			wostringstream woss;
			CParticle* pPart = new CParticle();
			//pPart->SetAudio();
			pPart->GetAnimInfo()->SetAnimation("AP_Recover");
			pPart->SetPosX(GetPosX());
			pPart->SetPosY(GetPosY());
			woss << "+" << nAmount * -1<< " AP";
			if(!GetTutorial())
			{
				CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);
				CBattleState::GetInstance()->AddSkill(pPart);
			}
			else
			{


			}
			pPart->Release();
		}
	}
	//Floating Text
}

void CUnits::Update(float fElapsedTime)
{ }

void CUnits::HandleEvent( const CEvent* pEvent )
{ }

void CUnits::GiveExperience		( int nAmount )
{
	int nToLevel = m_nLevel * m_nLevel * 100;
	int nExp = m_nExperience + nAmount;
	int nLevels = 0;
	while( nExp > nToLevel)
	{
		nLevels++;
		nExp -= nToLevel;
		nToLevel = (nLevels + m_nLevel) * (nLevels + m_nLevel) * 100;
	}

	m_nLevel += nLevels;
	if(nLevels > 0)
	{
		switch (m_eClass)
		{
		case UC_ENEMY:
			break;
		case UC_NONE:
			break;
		case UC_WARRIOR:
			SetMaxHealth(CUnits::GetMaxHealth() + (nLevels * 40));
			SetAttack(CUnits::GetAttack() + (nLevels * 3));
			SetMaxAP(CUnits::GetMaxAP() + (nLevels * 20));
			break;
		case UC_RANGER:
			SetMaxHealth(CUnits::GetMaxHealth() + (nLevels * 30));
			SetAttack(CUnits::GetAttack() + (nLevels * 3));
			SetMaxAP(CUnits::GetMaxAP() + (nLevels * 30));		

			break;
		case UC_MAGE:
			SetMaxHealth(CUnits::GetMaxHealth() + (nLevels * 20));
			SetAttack(CUnits::GetAttack() + (nLevels * 3));
			SetMaxAP(CUnits::GetMaxAP() + (nLevels * 40));			

			break;
		default:
			break;
		}
		m_nAvailStats += (5 * nLevels);
	}
	m_nExperience = nExp;
}

bool CUnits::decrStat()
{
	if(m_nAvailStats > 0)
	{
		m_nAvailStats--;
		return true;
	}
	return false;

}

bool CUnits::incrStat()
{
	if(m_nAvailStats + 1 <= (m_nLevel -1) * 5)
	{
		m_nAvailStats++;
		return true;
	}
	return false;
}

bool CUnits::incrAttack()
{
	if(decrStat())
	{
		m_nAttackPower += 1;
		return true;
	}
	else
		return false;
}

bool CUnits::decrAttack()
{
	if(incrStat())
	{
		m_nAttackPower-= 1;
		return true;
	}
	return false;
}

bool CUnits::incrHealth()
{
	if(decrStat())
	{
		m_nMaxHealth += 10;
		m_nHealth = m_nMaxHealth;
		return true;
	}
	else
		return false;

}

bool CUnits::decrHealth()
{
	if(incrStat())
	{
		m_nMaxHealth -= 10;
		m_nHealth = m_nMaxHealth;
		return true;
	}
	return false;

}

bool CUnits::incrAbility()
{
	if(decrStat())
	{
		m_nMaxAbilityPoints += 10;
		m_nAbilityPoints = m_nMaxAbilityPoints;
		return true;
	}
	else
		return false;

}

bool CUnits::decrAbility()
{
	if(incrStat())
	{
		m_nMaxAbilityPoints -= 10;
		m_nAbilityPoints = m_nMaxAbilityPoints;
		return true;
	}
	return false;
}

void CUnits::AddConsumableItem(CItem* input, int nAmount, float fChance)
{
	if(input == nullptr)
		return;
	if(m_mInventory[input->GetName()].Item != nullptr)
	{
		m_mInventory[input->GetName()].Owned += nAmount;
		if(m_mInventory[input->GetName()].Owned > 9)
			m_mInventory[input->GetName()].Owned = 9;
		m_mInventory[input->GetName()].DropChance = fChance;
	}
	else
	{
		m_mInventory[input->GetName()].Item = input;
		m_mInventory[input->GetName()].Owned += nAmount;
		m_mInventory[input->GetName()].DropChance = fChance;
	}
}

void CUnits::RemoveConsumableItem(CConsumable* input)
{
	if(input == nullptr)
		return;

	if(m_mInventory[input->GetName()].Item != nullptr)
	{
		m_mInventory[input->GetName()].Owned--;
		if(m_mInventory[input->GetName()].Owned < 0)
			m_mInventory[input->GetName()].Owned = 0;
	}
	else
	{
		return;
	}
}