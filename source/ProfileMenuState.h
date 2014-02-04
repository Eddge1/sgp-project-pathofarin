#pragma once
#include "gamestates.h"
#include "Player.h"
class CProfileMenuState : public CGameStates
{
	enum ProfileState {PS_NEWGAME, PS_SELECT, PS_DELETE};

	ProfileState m_eCurrState;
	float m_fPosY;
	bool m_bLeft;
	float m_fOffSetX;
	std::vector<CPlayer*> m_vCharacterList;
	std::vector<std::vector<int>> m_vWorldData;


public:

	CProfileMenuState(void);
	virtual ~CProfileMenuState(void);

	static CProfileMenuState* GetInstance( void );
	void SaveGame(std::string szFileName);

	CPlayerUnit* CreateTempPlayer(void);
	CPlayer* CreatePlayer();


	virtual void Activate	( void )	override;				// load resources
	virtual void Sleep		( void )	override;					// unload resources
	virtual void Update		( float fElapsedTime )	override;	// update the state
	virtual void Render		( void )	override;	
	virtual bool Input		( void )	override;	
	void LoadSave			( std::string szFileName );

};

