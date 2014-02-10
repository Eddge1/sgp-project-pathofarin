#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "Units.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

class CProjectile;
class CMiniGames : public IListener
{
	CUnits* m_pMaster;
	int m_nChances;
	int m_nCost;
	float m_fDamageMultiplier;
	bool m_bTutorial;
	CProjectile* m_pSkill;
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
	virtual void DoAttack() {};

	void SetSkill(CProjectile* pSkill) {m_pSkill = pSkill;}
	CProjectile* GetSkill() const {return m_pSkill;}
	void SetTutorial (bool bTut) {m_bTutorial = bTut;}
	bool GetTutorial ( ) const{return m_bTutorial;}
	virtual void ResetSkill( void ) {  }

	float ScalarDistance(float fx1, float fy1, float fx2, float fy2);
	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}
	int GetCost( void ) {return m_nCost;}
	virtual void HandleEvent( const CEvent* pEvent ) override {}

};

