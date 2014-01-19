#pragma once
#include "gamestates.h"
#include <Windows.h>

// Forward Class Declarations

class CSGD_EventSystem;
class CObject;
class CObjectManager;
class CPlayer;
class CRenderManager;


class CGamePlayState :
	public CGameStates
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

	

private:

	// Singleton (but not dynamically allocated)
	CGamePlayState( void );
	virtual ~CGamePlayState( void );
	CGamePlayState( const CGamePlayState& );
	CGamePlayState& operator= ( const CGamePlayState& );



	// Systems initialized by CGamePlayState
	CSGD_EventSystem*		m_pES;
	CObjectManager*			m_pOM;
	CRenderManager*			m_pRM;

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


};

