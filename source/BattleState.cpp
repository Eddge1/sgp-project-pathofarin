#include "BattleState.h"
#include "Units.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "RenderManager.h"
#include "Game.h"

// GetInstance
CBattleState* CBattleState::GetInstance( void )
{
	static CBattleState s_Instance;

	return &s_Instance;
}

CBattleState::CBattleState(void)
{
}

CBattleState::~CBattleState(void)
{
}

void CBattleState::Activate(void)
{

}

void CBattleState::Sleep(void)
{

}

bool CBattleState::Input(void)
{
	return true;
}

void CBattleState::Update(float fElapsedTime)
{

}

void CBattleState::Render(void)
{
	CSGD_TextureManager*	pTM	= CSGD_TextureManager::GetInstance();
	CSGD_Direct3D*			pD3D = CSGD_Direct3D::GetInstance();

	RECT temp = { 0, 478, 800, 600 };
	pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,0 ));

	
	

}

void CBattleState::Initialize(void)
{

}

void CBattleState::Battle(void)
{

}

void CBattleState::End(void)
{

}
