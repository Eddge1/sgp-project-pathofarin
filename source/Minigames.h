#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>
#include <string>

class CUnits;
class CMiniGames
{
	CUnits* m_pMaster;
	bool m_bFailed;
	bool m_bRight;
	int m_nChances;
	int m_nSuccess;
	float m_fDamageMultiplier;
	
	std::string m_szAbilityName;
	std::vector<RECT> m_rCollisionZones;
	std::vector<CMiniGames*> m_vSubSkills;

public:

	CMiniGames* GetSubMenu(int nID);
	virtual void SetOwner(CUnits* pOwner) final;

	CMiniGames(void);
	virtual ~CMiniGames(void);

	void Update(float fElapsedTime);
	void Render();

	void SetAbilityName(std::string szName)	{m_szAbilityName = szName;}
	void SetDamage( float fDam ) {m_fDamageMultiplier = fDam;}
	void SetChances( int nAttempts ) {m_nChances = nAttempts;}
	
	std::string GetAbilityName( void )	{return m_szAbilityName;}
	float GetDamage( void )	{return m_fDamageMultiplier;}
	int GetChances( void ) {return m_nChances;}

};

