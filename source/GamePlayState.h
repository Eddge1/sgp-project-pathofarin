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
#include "Npcs.h"
#include <sstream>
#include "Npcs.h"
#include "Augment.h"
#include "Armor.h"
#include "Weapon.h"
using namespace std;

// Forward Class Declarations
enum GamePhase {GP_NAV, GP_INIT, GP_BATTLE, GP_MENU, GP_START, GP_END};

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
	CPlayerUnit* GetPlayerUnit();
	virtual void HandleEvent( const CEvent* pEvent ) override;
	void TransitionWorld(std::string szNewWorld);

	CWorld* GetWorld(void) { return m_mWorldManager[m_sCurrWorld]; }
	CPlayer* GetPlayer() {return m_pPlayer;}

	//void LoadWorld(void);
	void LoadWorld(string szFileName);

	//void LoadNPCs(void);
	CUnits* LoadUnit(std::string szFileName);

	CWorld* GetWorld(string szName);
	CEnemyUnit* CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp, int attack = 5);
	CConsumable* CreatePotion(string input);

	// New stuff
	CAugment* CreateAugment(string Type, float Effect);
	CArmor* CreateArmor(string Name, float Hp, float Attk, float Speed);
	CWeapon* CreateWeapon(string Name, int Attack);
	map<string, InventoryItems>* GetItemManager() {return &m_mItemManager;}

	//Accessor for Map Name:
	string GetMapName() { return m_sCurrWorld; }
	void SetGameState(GamePhase ePhase) {m_eCurrPhase = ePhase;}
private:

	struct NPCDialogue
	{
		wostringstream szText;
		CObjects* pOwner;
		float m_fTimer;
		DWORD Color;
		RECT rPos;
	};

	// Singleton (but not dynamically allocated)
	CGamePlayState( void );
	virtual ~CGamePlayState( void );
	CGamePlayState( const CGamePlayState& );
	CGamePlayState& operator= ( const CGamePlayState& );

	map<string, CWorld*> m_mWorldManager;
	map<string, InventoryItems> m_mItemManager;

	vector<NPCDialogue*> m_vShowOnScreen;
	string m_sCurrWorld;

	// Systems initialized by CGamePlayState
	CSGD_EventSystem*		m_pES;
	CRenderManager*			m_pRM;
	CMiniGames				m_temp;

	bool m_bDialogue;

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
	int m_nSaveSelection;
	float m_fFireBallTimer;
	float m_fGameText;
	float m_fGameEndTimer;
	bool m_bSaveGameStatus;
	bool m_bSaveSuccess;
	GamePhase m_eCurrPhase;
};

