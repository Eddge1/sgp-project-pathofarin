#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "Units.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

class CProjectile;
class CMiniGames : public IListener
{
	CUnits* m_pMaster;
	int m_nChances;
	int m_nCost;
	int m_nSFXID;
	int m_nCriticalSFXID;
	int m_nFailSFXID;
	int m_nSuccessCompleteSFXID;
	float m_fDamageMultiplier;
	bool m_bTutorial;
	CProjectile* m_pSkill;
	bool m_bAOE;
	enum MiniType {MG_OFFENSIVE, MG_DEFENSIVE};
	MiniType m_eType;
	bool m_bDamage;

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

	virtual void SetType(MiniType eType) {m_eType = eType;}
	MiniType GetType() const {return m_eType;}

	void SetSkill(CProjectile* pSkill) {m_pSkill = pSkill;}
	CProjectile* GetSkill() const {return m_pSkill;}
	void SetTutorial (bool bTut) {m_bTutorial = bTut;}
	bool GetTutorial ( ) const{return m_bTutorial;}
	void SetAOE (bool bAOE) {m_bAOE = bAOE;}
	bool GetAOE ( ) const{return m_bAOE;}

	void SetDamageSkill(bool bValue) {m_bDamage = bValue;}
	bool DamageSkill(void) {return m_bDamage;}

	void PlaySuccess()  {CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSFXID);}
	void PlayCrit() {CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nCriticalSFXID);}
	void PlayFail() {CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nFailSFXID);}
	void PlayCompletion() {CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSuccessCompleteSFXID);}


	virtual void ResetSkill( void ) {  }

	float ScalarDistance(float fx1, float fy1, float fx2, float fy2);
	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}
	int GetCost( void ) {return m_nCost;}
	virtual void HandleEvent( const CEvent* pEvent ) override {}

};

