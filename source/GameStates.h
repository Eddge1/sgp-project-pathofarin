#pragma once
class CGameStates
{
	CGameStates(void);

	int m_nCursorSelection;
	int m_nTotalOptions;
	int m_nBackgroundImg;
	int m_nBackgroundMusic;
	int m_nSFXID;
	int m_nCursorIMG;
	
public:

	virtual ~CGameStates(void) = 0
	{

	}

	virtual void Activate() = 0;
	virtual void Sleep() = 0;
	virtual bool Input() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	// ACCESSORS
	int GetCursorSelection	( void )		{return m_nCursorSelection;}
	int GetTotalOptions		( void )		{return m_nTotalOptions;}
	int GetBackgroundImg	( void )		{return m_nBackgroundImg;}
	int GetBackgroundMusic	( void )		{return m_nBackgroundMusic;}
	int GetGetSFXID			( void )		{return m_nSFXID;}
	int GetCursorIMG		( void )		{return m_nCursorIMG;}

	// MUTATORS
	void SetCursorSelection	( int nOption )	{m_nCursorSelection		= nOption;}
	void SetTotalOptions	( int nOption )	{m_nTotalOptions		= nOption;}
	void SetBackgroundImg	( int nOption )	{m_nBackgroundImg		= nOption;}
	void SetBackgroundMusic	( int nOption )	{m_nBackgroundMusic		= nOption;}
	void SetSFXID			( int nOption )	{m_nSFXID				= nOption;}
	void SetCursorIMG		( int nOption )	{m_nCursorIMG			= nOption;}

};

