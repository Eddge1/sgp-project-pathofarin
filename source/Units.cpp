#include "Units.h"
#include "BattleState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include <sstream>


CUnits::CUnits(void)
{
	SetType(OBJECT_UNIT);
	m_nLevel = 1;
	m_nHealth = m_nMaxHealth = 100;
	m_nAbilityPoints = m_nMaxAbilityPoints = 100;
	m_nAttackPower	= 5;
	m_nSpeed = 0;
	m_nExperience = 0; 
	m_bTurn = false;
	m_nAvailStats = 0;
}


CUnits::~CUnits(void)
{

}

void CUnits::ModifyHealth(int nAmount, bool isCrit)
{
	std::wostringstream woss;
	m_nHealth -= nAmount;

	if(m_nHealth < 0)
		m_nHealth = 0;
	if(m_nHealth > m_nMaxHealth)
		m_nHealth = m_nMaxHealth;

	if(isCrit)
	{
		woss << "CRITICAL ";
		if(nAmount < 0)
		{
			woss << (nAmount * -1);
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,255), woss);
		}
		else if(nAmount > 0)
		{
			woss << nAmount;
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);
		}
		else
		{
			woss.str(_T(""));
			woss << "DODGED!";
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);

		}
	}
	else
	{
		if(nAmount < 0)
		{
			woss << (nAmount * -1);
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,0), woss);
		}
		else if(nAmount > 0)
		{
			woss << nAmount;
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(255,0,0), woss);
		}
		else
		{
			woss.str(_T(""));
			woss << "DODGED!";
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,0,255), woss);

		}
	}


	//Floating Text

}

void CUnits::ModifyAP(int nAmount)
{
	m_nAbilityPoints -= nAmount;

	if(m_nAbilityPoints < 0)
		m_nAbilityPoints = 0;
	if(m_nAbilityPoints > m_nMaxAbilityPoints)
		m_nAbilityPoints = m_nMaxAbilityPoints;

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
	m_nAvailStats += (5 * nLevels);

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

void CUnits::AddConsumableItem(CConsumable input)
{
	
	m_mInventory[input.GetName()].Item = input;
	m_mInventory[input.GetName()].Owned++;

}

void CUnits::RemoveConsumableItem(string input)
{
	//TODO:
}

