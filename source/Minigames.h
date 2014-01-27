#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>
#include <string>

class CUnits;
class CSkills;
class CMiniGames
{
	CUnits* m_pMaster;
	bool m_bFailed;
	bool m_bRight;
	int m_nChances;
	int m_nSuccess;
	float m_fDamageMultiplier;
	
	std::vector<RECT> m_rCollisionZones;
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
	void SetSkill(CSkills* pSkill);
	virtual void ResetSkill( void ) { }

	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}

};

