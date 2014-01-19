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


	if(pDI->KeyDown( DIK_A ) == true )
	{
		if(GetVelX() > 0 )
		{
			SetVelX(GetVelX() - 2 * fElapsedTime);
		}
		else
		{
			SetVelX(GetVelX() - 0.3 * fElapsedTime);

		}
	}
	else if(pDI->KeyDown( DIK_D ) == true )
	{
		if(GetVelX() < 0 )
		{
			SetVelX(GetVelX() + 2 * fElapsedTime);
		}
		else
		{
			SetVelX(GetVelX() + 0.3 * fElapsedTime);
		}

	}
	else
		SetVelX( GetVelX() - (GetVelX() * 0.005));


	if(pDI->KeyPressed( DIK_W ) == true)
	{
		SetVelY(GetVelY() - 0.70);
	}

	else if(pDI->KeyDown( DIK_S ) == true )
		SetVelY(GetVelY() + 5 * fElapsedTime);

	CEntity::Update(fElapsedTime);
}