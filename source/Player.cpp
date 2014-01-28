#include "Player.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CPlayer::CPlayer(void)
{

	SetType(OBJ_PLAYER);
	m_szName = "Arin";
	m_cBattle = nullptr;
}


CPlayer::~CPlayer(void)
{
	SetUnit(nullptr);
}

void CPlayer::SetName(std::string szName) 
{
	if(szName != "")
		m_szName = szName;
}

void CPlayer::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	SetVelX(0);
	SetVelY(0);

	if(pDI->KeyDown( DIK_A ) == true || pDI->JoystickDPadDown(DIR_LEFT))
	{
		this->GetAnimInfo()->SetAnimation("TEMP_Player_Walk_Left");
		SetVelX(-100);
	}
	else if(pDI->KeyDown( DIK_D ) == true || pDI->JoystickDPadDown(DIR_RIGHT))
	{
		this->GetAnimInfo()->SetAnimation("TEMP_Player_Walk_Right");
		SetVelX(100);
	}
	else
		SetVelX( GetVelX() - (GetVelX() * 0.005f));


	if(pDI->KeyDown( DIK_W ) == true || pDI->JoystickDPadDown(DIR_UP))
	{
		this->GetAnimInfo()->SetAnimation("TEMP_Player_Walk_Up");
		SetVelY(-100);
	}
	else if(pDI->KeyDown( DIK_S ) == true || pDI->JoystickDPadDown(DIR_DOWN))
	{
		this->GetAnimInfo()->SetAnimation("TEMP_Player_Walk_Down");
		SetVelY(100);
	}
	CEntity::Update(fElapsedTime);
}

void CPlayer::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_UNDEFINE)
	{


		RECT rTemp = col->GetCollisionRect();
		int nMid = rTemp.top + (rTemp.bottom - rTemp.top) / 2;
		if(GetCollisionRect().left > rTemp.right - 10 && GetCollisionRect().left < rTemp.right)
		{
			SetPosX(GetPosX() +1);
			SetVelX(0);
		}
		else if(GetCollisionRect().right < rTemp.left + 10 && GetCollisionRect().right > rTemp.left)
		{
			SetPosX(GetPosX() -1);
			SetVelX(0);
		}
		else if(GetCollisionRect().left > rTemp.right && GetCollisionRect().right < rTemp.left)
		{
			if(GetCollisionRect().bottom < rTemp.top + 10 && GetCollisionRect().bottom > rTemp.top)
			{
				if(GetVelY() > 0)
				{
					SetPosY(GetPosY() - 1);
					SetVelY(0);
				}
			}
			else if(GetCollisionRect().top > rTemp.bottom - 10 && GetCollisionRect().top < rTemp.bottom)
			{
				SetPosY(GetPosY() + 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().bottom < rTemp.top + 10 && GetCollisionRect().bottom > rTemp.top)
		{
			if(GetVelY() > 0)
			{
				SetPosY(GetPosY() - 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().top > rTemp.bottom - 10 && GetCollisionRect().top < rTemp.bottom)
		{
			SetPosY(GetPosY() + 1);

			SetVelY(0);
		}
	}
	else if(col->GetType() == OBJ_NPC)
	{
		if(GetVelX() > 0 && col->GetPosX() >= GetPosX())
			SetPosX(GetPosX() -1);
		else if(GetVelX() < 0 && col->GetPosX() <= GetPosX())
			SetPosX(GetPosX() + 1);

		if(GetVelY() > 0 && col->GetPosY() >= GetPosY())
			SetPosY(GetPosY() -1);
		else if(GetVelY() < 0 && col->GetPosY() <= GetPosY())
			SetPosY(GetPosY() + 1);
	}
}

void CPlayer::HandleEvent( const CEvent* pEvent )
{


}

void CPlayer::SetUnit	(CPlayerUnit* pUnit)
{
	if(m_cBattle != nullptr)
		m_cBattle->Release();

	m_cBattle = pUnit;

	if(m_cBattle != nullptr)
		m_cBattle->AddRef();
}

