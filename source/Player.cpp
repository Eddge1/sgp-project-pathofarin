#include "Player.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CPlayer::CPlayer(void)
{

	SetType(OBJ_PLAYER);
	m_szName = "Arin";
	m_cBattle = nullptr;

	m_fLastY = -1;
	m_fLastX = -1;
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
	m_fLastY = GetPosY();
	m_fLastX = GetPosX();

	SetVelX(0);
	SetVelY(0);

	if(pDI->KeyDown( DIK_A ) == true || pDI->JoystickDPadDown(DIR_LEFT))
	{
		this->GetAnimInfo()->SetAnimation("Warrior_Walk_Left");
		SetVelX(-100);
	}
	else if(pDI->KeyDown( DIK_D ) == true || pDI->JoystickDPadDown(DIR_RIGHT))
	{
		this->GetAnimInfo()->SetAnimation("Warrior_Walk_Right");
		SetVelX(100);
	}
	else
		SetVelX( GetVelX() - (GetVelX() * 0.005f));


	if(pDI->KeyDown( DIK_W ) == true || pDI->JoystickDPadDown(DIR_UP))
	{
		this->GetAnimInfo()->SetAnimation("Warrior_Walk_Up");
		SetVelY(-100);
	}
	else if(pDI->KeyDown( DIK_S ) == true || pDI->JoystickDPadDown(DIR_DOWN))
	{
		this->GetAnimInfo()->SetAnimation("Warrior_Walk_Down");
		SetVelY(100);
	}

	if (this->GetVelX() == 0 && this->GetVelY() == 0)
	{
		if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Up")
		{
			this->GetAnimInfo()->SetAnimation("Warrior_Idle_Up");
		}
		else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Down")
		{
			this->GetAnimInfo()->SetAnimation("Warrior_Idle_Down");
		}
		else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Left")
		{
			this->GetAnimInfo()->SetAnimation("Warrior_Idle_Left");
		}
		else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Right")
		{
			this->GetAnimInfo()->SetAnimation("Warrior_Idle_Right");
		}
	}

	CEntity::Update(fElapsedTime);
}

void CPlayer::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_UNDEFINE || col->GetType() == OBJ_NPC || col->GetType() == OBJ_CHEST)
	{
		RECT rTemp = col->GetCollisionRect();
		if(GetCollisionRect().left > rTemp.left && GetCollisionRect().left < rTemp.right)
		{
			SetPosX(m_fLastX);
		}
		else if(GetCollisionRect().right < rTemp.right && GetCollisionRect().right > rTemp.left)
		{
			SetPosX(m_fLastX);
		}
		else if(GetCollisionRect().left > rTemp.right && GetCollisionRect().right < rTemp.left)
		{
			if(GetCollisionRect().bottom > rTemp.top && GetCollisionRect().bottom < rTemp.bottom)
			{
				SetPosY(m_fLastY);
			}
			else if(GetCollisionRect().top > rTemp.top - 10 && GetCollisionRect().top < rTemp.bottom)
			{
				SetPosY(m_fLastY);
			}
		}

		if(GetCollisionRect().bottom > rTemp.top && GetCollisionRect().bottom < rTemp.bottom)
		{
			SetPosY(m_fLastY);
		}
		else if(GetCollisionRect().top > rTemp.top - 10 && GetCollisionRect().top < rTemp.bottom)
		{
			SetPosY(m_fLastY);
		}
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

