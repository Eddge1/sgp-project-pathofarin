#include "Player.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CPlayer::CPlayer(void)
{
	SetType(OBJ_PLAYER);
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	SetVelX(0);
	SetVelY(0);

	if(pDI->KeyDown( DIK_A ) == true || pDI->JoystickDPadDown(DIR_LEFT))
		SetVelX(-100);
	else if(pDI->KeyDown( DIK_D ) == true || pDI->JoystickDPadDown(DIR_RIGHT))
		SetVelX(100);
	else
		SetVelX( GetVelX() - (GetVelX() * 0.005f));


	if(pDI->KeyDown( DIK_W ) == true || pDI->JoystickDPadDown(DIR_UP))
		SetVelY(-100);
	else if(pDI->KeyDown( DIK_S ) == true || pDI->JoystickDPadDown(DIR_DOWN))
		SetVelY(100);

	CEntity::Update(fElapsedTime);
}

void CPlayer::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_UNDEFINE)
	{
		
		if(GetVelX() > 0)
			SetPosX(GetPosX() -1);
		else if(GetVelX() < 0)
			SetPosX(GetPosX() + 1);
		
		if(GetVelY() > 0)
			SetPosY(GetPosY() -1);
		else if(GetVelY() < 0)
			SetPosY(GetPosY() + 1);
	
	}
}

void CPlayer::HandleEvent( const CEvent* pEvent )
{


}
