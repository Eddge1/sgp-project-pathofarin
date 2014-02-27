#pragma once
#include "gamestates.h"
#include "../SGD Wrappers/IListener.h"
#include "Minigames.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "TriggerSpree.h"
#include "ComboGame.h"
#include "BasicAttack.h"
using namespace std;

class CBitmapFont;
class CUnits;
class CObjects;
class CPlayerUnit;
class CEnemyUnit;
class CTutorialBattle :	public CGameStates
{
	CTriggerSpree* m_pTrigger;
	CComboGame* m_pCombo;
	CBasicAttack* m_pAttack;
	CTutorialBattle(void);
	virtual ~CTutorialBattle(void);

	struct FloatingText
	{
		std::wostringstream szText;
		float m_fLocX;
		float m_fLocY;
		float m_fTimer;
		DWORD Color;
	};

	enum PBattlephase {BP_INIT, BP_BATTLE, BP_END};

	CBitmapFont* m_pFont;

	vector<CUnits*> m_vBattleUnits;
	CPlayerUnit* m_pPlayerUnit;

	PBattlephase m_eCurrentPhase;

	int m_nForestBattleID;
	int m_nTurn;
	int m_nMenuImage;
	int m_nMenuSelectionImage;
	int m_nVictoryMusic;
	int m_nDefeatMusic;
	int m_nHealthBar;
	int m_nHealthBarPlate;
	int m_nAPBar;
	int m_nTarget;
	bool m_bTutorialPause;
	int m_nTutorialPauseSelection;
	bool m_bVictory;
	bool m_bDelayed;
	bool m_bMenu;
	bool m_bPlayerTurn;
	bool m_bPlayerUnitSelection;
	bool m_bPlayerConduct;
	bool m_bSubMenuSelection;
	bool m_bExplanation;
	bool m_bSendOncePerTurn;
	bool m_bExplainOnceTurn;
	float m_fEnemyDelay;
	float m_fEndBatleTimer;
	float m_fCancelTimer;
	float m_fDelayTurn;
	float timer;
	int m_nSelectionChange;
	int m_nTopMenuSelection;
	int m_nSubMenuSelect;
	int m_nCombArrowImgID;

	vector<FloatingText*> m_vText;

	bool m_bExplainDodge;
	bool m_bExplainAttack;
	bool m_bExplainTrigger;
	bool m_bExplainCombo;

public:
	static CTutorialBattle* GetInstance( void );

	virtual void Activate( void )	override;				
	virtual void Sleep( void )	override;					
	virtual bool Input( void )	override;					
	virtual void Update( float fElapsedTime )	override;	
	virtual void Render( void )	override;	

	void SetPlayerTurn(bool bTurn) {m_bPlayerTurn = bTurn;}

	CPlayerUnit* GetPlayerUnit() {return m_pPlayerUnit;}
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp);
	CPlayerUnit* CreateTempPlayer();
	void EnemyTurn();
	void PlayerTurn();

	void GetNextTarget(void);
	void GetPreviousTarget(void);
	void Initialize(void);
	void Battle(float fElapsedTime);
	void EndBattle(void);
	void AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText);
	void FromMenu(bool bMenu) {m_bMenu = bMenu;}
	CUnits* GetCurrentTarget(void);
};