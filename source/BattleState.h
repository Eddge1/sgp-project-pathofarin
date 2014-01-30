#pragma once
#include "gamestates.h"
#include "../SGD Wrappers/IListener.h"
#include "Minigames.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class CBitmapFont;
class CUnits;
class CObjects;
class CPlayerUnit;
class CEnemyUnit;

class CBattleState : public CGameStates
{
	struct FloatingText
	{
		std::wostringstream szText;
		float m_fLocX;
		float m_fLocY;
		float m_fTimer;
		DWORD Color;
	};

	std::vector<FloatingText*> m_vText;

public:
	static CBattleState* GetInstance( void );

	// Temp player.
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp);

	void GetNextTarget(void);
	void GetPreviousTarget(void);
	CUnits* GetCurrentTarget(void);

	void Initialize(void);
	void Battle(float fElapsedTime);
	void EndBattle(void);
	void AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText);

	virtual void Activate( void )	override;				// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;	

	void SetSender(CObjects* pSender);
	void SetPlayer(CUnits* pPlayer);

private:
	enum PBattlephase {BP_INIT, BP_BATTLE, BP_END};

	CBitmapFont* m_pFont;

	vector<CUnits*> m_vBattleUnits;
	vector<CUnits*> m_vDeadUnits;
	CObjects* m_pSender;
	CUnits* m_pPlayerUnit;

	PBattlephase m_eCurrentPhase;

	int m_nForestBattleID;
	int m_nTurn;
	int m_nMenuImage;
	int m_nMenuSelectionImage;
	int m_nVictoryMusic;
	int m_nDefeatMusic;
	int m_nHealthBar;
	int m_nAPBar;
	int m_nTarget;
	int m_nGoldObtained;
	int m_nExperience;
	bool m_bVictory;
	bool m_bDefeat;
	float m_fEndBatleTimer;
	float m_fCancelTimer;

	CBattleState(void);
	virtual ~CBattleState(void);
	CBattleState( const CBattleState& );
	CBattleState& operator= ( const CBattleState& );
};

