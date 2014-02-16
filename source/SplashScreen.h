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

