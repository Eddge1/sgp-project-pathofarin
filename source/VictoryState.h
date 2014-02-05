#pragma once
#include "gamestates.h"
#include "PlayerUnit.h"
class CVictoryState : public CGameStates
{
	bool m_bLeveled;
	int m_nExperienceGained;
	CPlayerUnit* m_pPlayer;
	int m_nLevel;
	int m_nCurrentExp;
	int m_nNeeded;
	int m_nCurrMaxHP;
	int m_nCurrMaxAP;
	int m_nCurrAttack;
	int m_nHealthMod;
	int m_nAPMod;
	int m_nAttackMod;
	int m_nMaxStat;

	float 	m_fTimer;

	CVictoryState( void );
	virtual ~CVictoryState( void );
	CVictoryState( const CVictoryState& );
	CVictoryState& operator= ( const CVictoryState& );
public:
	static CVictoryState* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;					// render entities

	void SetPlayer(CPlayerUnit*);
	void SetExperience(int nAmount) {m_nExperienceGained = nAmount;}
};

