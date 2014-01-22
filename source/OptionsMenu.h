#pragma once
#include "gamestates.h"
class COptionsMenu :
	public CGameStates
{
public:
	static COptionsMenu* GetInstance( void );

	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;	

private:
	COptionsMenu(void);
	virtual ~COptionsMenu(void);
	COptionsMenu( const COptionsMenu& );
	COptionsMenu& operator= ( const COptionsMenu& );

	bool m_bSubMenu;
	bool m_bIsWindow;
	bool m_bIsMemory;

	int m_nMusicVolume;
	int m_nSFXVolume;
};

