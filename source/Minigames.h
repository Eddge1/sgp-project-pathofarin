#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include "Units.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

class CSkills;
class CMiniGames : public IListener
{
	CUnits* m_pMaster;
	int m_nChances;
	int m_nCost;
	float m_fDamageMultiplier;

	CSkills* m_pSkill;
public:
	virtual void SetOwner(CUnits* pOwner) final;
	CUnits* GetOwner(void) { return m_pMaster; }

	CMiniGames(void);
	virtual ~CMiniGames(void);

	virtual void Update(float fElapsedTime);
	virtual void Render();

	virtual void SetDamage( float fDam ) {m_fDamageMultiplier = fDam;}
	virtual void SetChances( int nAttempts ) {m_nChances = nAttempts;}
	virtual void SetCost ( int nAmount ) {m_nCost = nAmount;}

	void SetSkill(CSkills* pSkill);
	virtual void ResetSkill( void ) {  }

	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}
	int GetCost( void ) {return m_nCost;}
	virtual void HandleEvent( const CEvent* pEvent ) override {}

};

