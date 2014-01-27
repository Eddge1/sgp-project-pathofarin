#include "Units.h"
#include "BattleState.h"
#include <sstream>


CUnits::CUnits(void)
{
	SetType(OBJECT_UNIT);
	m_nLevel = 0;
	m_nHealth = m_nMaxHealth = 100;
	m_nAbilityPoints = m_nMaxAbilityPoints = 100;
	m_nAttackPower	= 5;
	m_nSpeed = 0;;

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
