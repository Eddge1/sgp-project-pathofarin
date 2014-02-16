#pragma once
#include "gamestates.h"
#include <string>
class CSplashScreen : public CGameStates
{
	CSplashScreen(void);
	virtual ~CSplashScreen(void);
	CSplashScreen( const CSplashScreen& );
	CSplashScreen& operator= ( const CSplashScreen& );
	std::string m_szLoadStatus;
	float m_fPercentDone;
	int m_nLogoID;
	float  m_fDisappear1;
	float  m_fAppearDisappear;
	float m_fDelay;
	bool m_bFadeIn;
	bool  m_bComplete;
public:
	static CSplashScreen* GetInstance( void );

	void SetString(std::string szStatus) {m_szLoadStatus = szStatus;}
	void SetPercentDone(float fPercent) {m_fPercentDone = fPercent;}
	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;
};

