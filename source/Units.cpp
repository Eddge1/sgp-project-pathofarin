#include "Units.h"


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
	m_nHealth -= nAmount;

	if(m_nHealth < 0)
		m_nHealth = 0;
	if(m_nHealth > m_nMaxHealth)
		m_nHealth = m_nMaxHealth;

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
