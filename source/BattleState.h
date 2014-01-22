#pragma once
#include "gamestates.h"
#include <vector>
using namespace std;


class CUnits;

class CBattleState :
	public CGameStates
{
public:


	static CBattleState* GetInstance( void );



	void Initialize(void);
	void Battle(void);
	void End(void);

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;	

private:

	enum PBattlephase {BP_INIT, BP_BATTLE, BP_END};

	

	vector<CUnits*> m_vBattleUnits;
	vector<CUnits*> m_vDeadUnits;


	PBattlephase m_eCurrentPhase;

	int m_nTurn;
	int m_nMenuImage;
	int m_nHealthBar;
	int m_nAPBar;
	int m_nTarget;
	int m_nGoldObtained;
	int m_nExperience;


	CBattleState(void);
	virtual ~CBattleState(void);
	CBattleState( const CBattleState& );
	CBattleState& operator= ( const CBattleState& );
};
