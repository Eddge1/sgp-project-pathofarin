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

	bool GetLeftMenuState() const {return m_bLeftMenuState;}
	void SetLeftMenuState(bool bState) {m_bLeftMenuState = bState;}
private:

	float m_fRotation;
	int m_nLogoID;
	int m_nSelectionMenuID;
	int m_nRangerID;
	int m_nWarriorID;
	int m_nMageID;
	float m_fPosX;
	float m_fPosY;
	bool m_bLeft;
	bool m_bLeftMenuState;
	char m_cTrans;
	float m_fRune1Scale;
	float m_fRune2Scale;
	float m_fRunes3Scale;
	float m_fRune1ReactTimer;
	float m_fRune2ReactTimer;
	float m_fRunes3ReactTimer;

	CMainMenuState(void);
	virtual ~CMainMenuState(void);
	CMainMenuState( const CMainMenuState& );
	CMainMenuState& operator= ( const CMainMenuState& );

};

