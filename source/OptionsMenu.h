#pragma once
#include "gamestates.h"
class COptionsMenu :
	public CGameStates
{
public:
	COptionsMenu(void);
	virtual ~COptionsMenu(void);

	//virtual void Activate( void )	override;					// load resources
	//virtual void Sleep( void )	override;					// unload resources
	//virtual void Update( float fElapsedTime )	override;	// update the state
	//virtual void Render( void )	override;	
	//virtual bool Input( void )	override;	
};

