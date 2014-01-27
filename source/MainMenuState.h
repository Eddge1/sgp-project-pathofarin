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
	float m_fRotation;
	int m_nLogoID;
	int m_nSelectionMenuID;
	int m_nRangerID;
	int m_nWarriorID;
	int m_nMageID;
	float m_fPosX;
	bool m_bLeft;

	int m_nMenu1;
	int m_nMenu2;
	int m_nMenu3;



	CMainMenuState(void);
	virtual ~CMainMenuState(void);
	CMainMenuState( const CMainMenuState& );
	CMainMenuState& operator= ( const CMainMenuState& );

};

