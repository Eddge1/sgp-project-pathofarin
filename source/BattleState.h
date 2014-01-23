#pragma once
#include "gamestates.h"
#include "../SGD Wrappers/IListener.h"
#include <vector>
#include <string>
using namespace std;

class CBitmapFont;
class CUnits;
class CObjects;
class CPlayerUnit;
class CEnemyUnit;

class CBattleState : public CGameStates
{
public:


	static CBattleState* GetInstance( void );

	// Temp player.
	CObjects* m_pSender;
	CPlayerUnit* CreateTempPlayer(void);
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp);

	void GetNextTarget(void);
	void GetPreviousTarget(void);


	void Initialize(void);
	void Battle(void);
	void EndBattle(void);

	virtual void Activate( void )	override;				// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;	

	void SetSender(CObjects* pSender);

private:

	enum PBattlephase {BP_INIT, BP_BATTLE, BP_END};

	CBitmapFont* m_pFont;

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

