#pragma once
#include "gamestates.h"

class CMainMenuState :
	public CGameStates
{
public:

	static CMainMenuState* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual void Update( float fElapsedTime )	override;	// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;	



private:

	CMainMenuState(void);
	virtual ~CMainMenuState(void);
	CMainMenuState( const CMainMenuState& );
	CMainMenuState& operator= ( const CMainMenuState& );

};

