#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

#include "BitmapFont.h"

#include <ctime>

class CGameStates;

class CGame
{
public:

	// Singleton accessors:
	static CGame* GetInstance( void );
	static void DeleteInstance( void );


	// Setup, Run, Cleanup
	void Initialize( HWND hWnd, HINSTANCE hInstance,
		int nWidth, int nHeight,
		bool bIsWindowed );

	bool Run( void );

	void Terminate( void );

	// Window Accessors:
	int GetScreenWidth ( void ) const	{	return m_nScreenWidth;	}
	int GetScreenHeight( void ) const	{	return m_nScreenHeight;	}

	//BitmapFont Accessor
	CBitmapFont* GetFont() const { return m_pFont; }

	void ChangeState( CGameStates* pState );

private:

	// Static pointer to the singleton object
	static CGame* s_pInstance;

	// Private constructor / destructor to prevent multiple objects
	CGame( void );						// default ctor
	virtual ~CGame( void );				// dtor
	CGame( const CGame& );				// copy ctor
	CGame& operator= ( const CGame& );	// assignment op

	// Helper Methods
	bool Update( void );
	void Render( void );
	bool Load( void );
	void GetFM( void );


	// SGD Wrappers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CSGD_XAudio2*			m_pXA;

	//TODO: Bitmap font.
	CBitmapFont*			m_pFont;
	// Window Attributes
	int						m_nScreenWidth;
	int						m_nScreenHeight;
	bool					m_bIsWindowed;

	// Current Game State TODO:
	CGameStates*				m_pCurrState;


	// Current time
	DWORD					m_dwCurrTime;



};

