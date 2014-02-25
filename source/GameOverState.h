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
	int m_background;
	int m_cursor;
	float timer;
	CPlayer* m_pPlayer;
	string m_szGameOverMsg;
	
	bool m_bMainMenu;
	bool m_bShowMenu;
	float m_fFadeScreen;
	float m_fFadeText;

public:
	static CGameOverState* GetInstance( void );
	void SetMessage(string szMessage) {m_szGameOverMsg = szMessage;}
	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;


};

