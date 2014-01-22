#pragma once
#include "gamestates.h"
class CCreditState :
	public CGameStates
{
	CCreditState(void);
	virtual ~CCreditState(void);
	CCreditState( const CCreditState& );
	CCreditState& operator= ( const CCreditState& );
public:
	static CCreditState* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;

};

