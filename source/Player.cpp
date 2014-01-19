#include "Player.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	SetVelX(0);
	SetVelY(0);

	if(pDI->KeyDown( DIK_A ) == true )
	{
		SetVelX(-500);
	}
	else if(pDI->KeyDown( DIK_D ) == true )
	{

		SetVelX(500);
	}
	else
		SetVelX( GetVelX() - (GetVelX() * 0.005));


	if(pDI->KeyDown( DIK_W ) == true)
	{
		SetVelY(-500);
	}

	else if(pDI->KeyDown( DIK_S ) == true )
		SetVelY(500);

	CEntity::Update(fElapsedTime);
}