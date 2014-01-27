#pragma once
#include "gamestates.h"
#include <Windows.h>
#include "Minigames.h"
#include <map>
#include "World.h"
#include "../SGD Wrappers/IListener.h"
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

	CPlayer* CreatePlayer();
	CPlayerUnit* CreateTempPlayer(void);
	CUnits* GetPlayerUnit();
	virtual void HandleEvent( const CEvent* pEvent ) override;
	void TransitionWorld(std::string szNewWorld);

	CWorld* GetWorld(void) { return m_mWorldManager[m_sCurrWorld]; }

	void LoadWorld(string input);

private:

	enum GamePhase {GP_NAV, GP_BATTLE, GP_MENU, GP_START, GP_END};
	// Singleton (but not dynamically allocated)
	CGamePlayState( void );
	virtual ~CGamePlayState( void );
	CGamePlayState( const CGamePlayState& );
	CGamePlayState& operator= ( const CGamePlayState& );


	map<string, CWorld*> m_mWorldManager;
	string m_sCurrWorld;

	// Systems initialized by CGamePlayState
	CSGD_EventSystem*		m_pES;
	CRenderManager*			m_pRM;
	CMiniGames m_temp;

	// Game Entities

	CPlayer* m_pPlayer;

	// Game Assets
	int WorldWidth;
	int WorldHeight;
	int WorldCamX;
	int WorldCamY;

	bool bisPaused;
	int m_nCursor;
	int m_nConversationID;
	float m_fFireBallTimer;
	GamePhase m_eCurrPhase;

};

