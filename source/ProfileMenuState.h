#pragma once
#include "gamestates.h"
class CProfileMenuState :
	public CGameStates
{
public:
	CProfileMenuState(void);
	virtual ~CProfileMenuState(void);

	static CProfileMenuState* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;					// unload resources
	virtual void Update( float fElapsedTime )	override;	// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;	

};

