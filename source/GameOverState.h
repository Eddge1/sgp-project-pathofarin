#pragma once
#include "gamestates.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "Game.h"
#include "BitmapFont.h"
#include "ProfileMenuState.h"
#include "Player.h"
#include "GamePlayState.h"
#include <string>
using namespace std;

class CGameOverState :
	public CGameStates
{

	CGameOverState(void);
	virtual ~CGameOverState(void);
	CGameOverState( const CGameOverState& );
	CGameOverState& operator= ( const CGameOverState& );

	int selection;
	int m_music;
	float timer;
	CPlayer* m_pPlayer;
	

public:
	static CGameOverState* GetInstance( void );


	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;


};

