#pragma once
#include "gamestates.h"
#include <Windows.h>
#include "Minigames.h"
#include <map>
#include "World.h"
#include "EnemyUnit.h"
#include "Item.h"
#include "Consumable.h"
#include "../SGD Wrappers/IListener.h"
#include <sstream>
using namespace std;

// Forward Class Declarations

class CSGD_EventSystem;
class CObjects;
class CObjectManager;
class CPlayer;
class CRenderManager;
class CPlayerUnit;

class CGamePlayState :	public CGameStates, public IListener
{

public:

	void AddFloatingText(CObjects* pOwner, DWORD dColor, wostringstream &szText);
	int GetWorldWidth  () { return WorldWidth ; }
	int GetWorldHeight () { return WorldHeight ; }
	int GetWorldCamX   () { return WorldCamX ; }
	int GetWorldCamY   () { return WorldCamY ; }

	void SetWorldWidth  ( int x ) { WorldWidth = x; }
	void SetWorldHeight  ( int x ) { WorldHeight = x; }
	void SetWorldCamX  ( int x ) { WorldCamX = x; }
	void SetWorldCamY ( int x ) { WorldCamY = x; }

	static CGamePlayState* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual bool Input( void )	override;					// handle user input
	virtual void Update( float fElapsedTime )	override;	// update entities
	virtual void Render( void )	override;					// render entities

	void SetPlayer(CPlayer* pPlayer);
	CUnits* GetPlayerUnit();
	virtual void HandleEvent( const CEvent* pEvent ) override;
	void TransitionWorld(std::string szNewWorld);

	CWorld* GetWorld(void) { return m_mWorldManager[m_sCurrWorld]; }
	CPlayer* GetPlayer() {return m_pPlayer;}

	void LoadWorld(void);
	void LoadNPCs(void);
	void LoadUnits(void);
	CUnits* GetUnit(std::string);
	CNpcs* GetNpc(std::string);

	CWorld* GetWorld(string szName);
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp, int attack = 5);
	CConsumable* CreatePotion(string input);


private:
	struct NPCDialogue
	{
		wostringstream szText;
		CObjects* pOwner;
		float m_fTimer;
		DWORD Color;
	};

	enum GamePhase {GP_NAV, GP_BATTLE, GP_MENU, GP_START, GP_END};
	// Singleton (but not dynamically allocated)
	CGamePlayState( void );
	virtual ~CGamePlayState( void );
	CGamePlayState( const CGamePlayState& );
	CGamePlayState& operator= ( const CGamePlayState& );

	map<string, CWorld*> m_mWorldManager;
	map<string, InventoryItems> m_mItemManager;

	map<string, CNpcs*> m_mNPCManager;
	map<string, CUnits*> m_mUnitsManager;

	vector<NPCDialogue*> m_vShowOnScreen;
	string m_sCurrWorld;

	// Systems initialized by CGamePlayState
	CSGD_EventSystem*		m_pES;
	CRenderManager*			m_pRM;
	CMiniGames				m_temp;

	// Game Entities

	CPlayer* m_pPlayer;

	// Game Assets
	int WorldWidth;
	int WorldHeight;
	int WorldCamX;
	int WorldCamY;
	bool m_bGameVictory;
	bool bisPaused;
	int m_nCursor;
	int m_nConversationID;
	float m_fFireBallTimer;
	float m_fGameText;
	float m_fGameEndTimer;
	GamePhase m_eCurrPhase;

};

