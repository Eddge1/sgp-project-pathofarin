#pragma once
#include "gamestates.h"
#include "../SGD Wrappers/IListener.h"
#include "Minigames.h"
#include "Projectile.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
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
public:
	static CBattleState* GetInstance( void );
	static bool CBattleState::SortSpeed(CUnits *l, CUnits *r);

	// Temp player.
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp);

	void GetNextTarget(void);
	void GetPreviousTarget(void);
	CUnits* GetCurrentTarget(void);
	vector<CUnits*>& GetBattleUnits(void) { return m_vBattleUnits; }
	vector<CProjectile*> m_vSkills;
	void Initialize(void);
	void Battle(float fElapsedTime);
	void EndBattle(void);
	void AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText);
	void AddSkill(CProjectile* pTemp) {m_vSkills.push_back(pTemp); pTemp->AddRef();}
	virtual void Activate( void )	override;				// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;	
	unsigned int GetTotalUnits() {return m_vBattleUnits.size();}

	void SetSender(CObjects* pSender);
	void SetPlayer(CUnits* pPlayer);
	void SetItems(CUnits* pDead);
	void ClearItems();
	map<string,InventoryItems>* GetItems() {return &m_vItems;}

private:
	enum PBattlephase {BP_INIT, BP_BATTLE, BP_END};

	CBitmapFont* m_pFont;

	vector<CUnits*> m_vBattleUnits;
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
	int m_nHealthBarPlate;
	int m_nAPBar;
	int m_nTarget;
	int m_nGoldObtained;
	bool m_bVictory;
	bool m_bDefeat;
	bool m_bLeveled;
	bool m_bDelayed;
	float m_fEndBatleTimer;
	float m_fCancelTimer;
	float m_fDelayTurn;
	vector<FloatingText*> m_vText;
	map<string, InventoryItems> m_vItems;
	int m_nExperienceGained;
	int m_nSelectionChange;

	CBattleState(void);
	virtual ~CBattleState(void);
	CBattleState( const CBattleState& );
	CBattleState& operator= ( const CBattleState& );
};

