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

	if(nLevels > 0)
	{
		if(GetType() == OBJ_PLAYER_UNIT)
			CSGD_EventSystem::GetInstance()->SendEventNow("LEVEL_UP", &nLevels, nullptr, this);
	}

	m_nExperience = nExp;
}