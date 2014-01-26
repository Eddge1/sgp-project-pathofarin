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

	void Update(float fElapsedTime);
	void Render();

	void SetDamage( float fDam ) {m_fDamageMultiplier = fDam;}
	void SetChances( int nAttempts ) {m_nChances = nAttempts;}
	void SetSkill(CSkills* pSkill);

	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}

};

