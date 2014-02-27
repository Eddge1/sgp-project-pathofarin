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
	m_bIsWarping = false;
	m_bBroadcast = false;
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
	float fDiff = 0.0f;

	if(GetVelX() > 10)
	{
		fDiff = GetVelX() - (500 * fElapsedTime);
		if(fDiff < 0)
			SetVelX(0);
		else
			SetVelX(fDiff);
	}
	else if(GetVelX () < - 10)
	{
		fDiff = GetVelX() + (500 * fElapsedTime);
		if(fDiff > 0)
			SetVelX(0);
		else
			SetVelX(fDiff);
	}
	else
		SetVelX(0);

	if(GetVelY() > 10)
	{
		fDiff = GetVelY() - (500 * fElapsedTime);
		if(fDiff < 0)
			SetVelY(0);
		else
			SetVelY(fDiff);
	}
	else if(GetVelY () < - 10)
	{
		fDiff = GetVelY() + (500 * fElapsedTime);
		if(fDiff > 0)
			SetVelY(0);
		else
			SetVelY(fDiff);
	}
	else
		SetVelY(0);

	if((pDI->KeyPressed(DIK_RETURN)|| pDI->JoystickButtonPressed(1)) && m_bInteraction == false)
		m_bInteraction = true;
	if(!pDI->KeyPressed(DIK_RETURN) && !pDI->JoystickButtonPressed(1))
		m_bInteraction = false;

	string szAnimation = "";

	switch (this->GetUnit()->GetClass())
	{
	case UC_NONE:
		szAnimation = "Kid";
		break;
	case UC_WARRIOR:
		szAnimation = "Warrior";
		break;

	case UC_MAGE:
		szAnimation = "Mage";
		break;

	case UC_RANGER:
		szAnimation = "Ranger";
		break;
	case UC_ENEMY:
		break;
	default:
		break;
	}

	if(pDI->KeyDown( DIK_W ) == true || pDI->JoystickDPadDown(DIR_UP) || pDI->JoystickGetLStickDirDown(DIR_UP))
	{
		szAnimation += "_Walk_Up";
		SetVelY(-125);
	}
	else if(pDI->KeyDown( DIK_S ) == true || pDI->JoystickDPadDown(DIR_DOWN) || pDI->JoystickGetLStickDirDown(DIR_DOWN))
	{
		szAnimation += "_Walk_Down";
		SetVelY(125);
	}

	if(pDI->KeyDown( DIK_A ) == true || pDI->JoystickDPadDown(DIR_LEFT) || pDI->JoystickGetLStickDirDown(DIR_LEFT))
	{
		if(GetVelY() == 0)
		{
			szAnimation += "_Walk_Left";
		}
		SetVelX(-125);
	}
	else if(pDI->KeyDown( DIK_D ) == true || pDI->JoystickDPadDown(DIR_RIGHT) || pDI->JoystickGetLStickDirDown(DIR_RIGHT))
	{
		if(GetVelY() == 0)
		{
			szAnimation += "_Walk_Right";
		}
		SetVelX(125);
	}

	if (this->GetVelX() == 0 && this->GetVelY() == 0)
	{
		if(this->GetUnit()->GetClass() == UC_NONE)
		{
			if (this->GetAnimInfo()->GetCurrentAnimation() == "Kid_Walk_Up")
			{
				szAnimation += "_Idle_Up";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Kid_Walk_Down")
			{
				szAnimation += "_Idle_Down";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Kid_Walk_Left")
			{
				szAnimation += "_Idle_Left";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Kid_Walk_Right")
			{
				szAnimation += "_Idle_Right";
			}
		}
		if(this->GetUnit()->GetClass() == UC_RANGER)
		{
			if (this->GetAnimInfo()->GetCurrentAnimation() == "Ranger_Walk_Up")
			{
				szAnimation += "_Idle_Up";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Ranger_Walk_Down")
			{
				szAnimation += "_Idle_Down";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Ranger_Walk_Left")
			{
				szAnimation += "_Idle_Left";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Ranger_Walk_Right")
			{
				szAnimation += "_Idle_Right";
			}
		}
		if(this->GetUnit()->GetClass() == UC_MAGE)
		{
			if (this->GetAnimInfo()->GetCurrentAnimation() == "Mage_Walk_Up")
			{
				szAnimation += "_Idle_Up";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Mage_Walk_Down")
			{
				szAnimation += "_Idle_Down";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Mage_Walk_Left")
			{
				szAnimation += "_Idle_Left";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Mage_Walk_Right")
			{
				szAnimation += "_Idle_Right";
			}
		}
		if(this->GetUnit()->GetClass() == UC_WARRIOR)
		{
			if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Up")
			{
				szAnimation += "_Idle_Up";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Down")
			{
				szAnimation += "_Idle_Down";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Left")
			{
				szAnimation += "_Idle_Left";
			}
			else if (this->GetAnimInfo()->GetCurrentAnimation() == "Warrior_Walk_Right")
			{
				szAnimation += "_Idle_Right";
			}
		}
	}

	if(szAnimation != "Warrior" && szAnimation != "Mage" && szAnimation != "Ranger" && szAnimation != "Kid")
		this->GetAnimInfo()->SetAnimation(szAnimation.c_str());

	CEntity::Update(fElapsedTime);
}

void CPlayer::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_UNDEFINE || col->GetType() == OBJ_NPC || col->GetType() == OBJ_CHEST)
	{
		int nCamX = CGamePlayState::GetInstance()->GetWorldCamX();
		int nCamY = CGamePlayState::GetInstance()->GetWorldCamY();
		float fWidthR =   GetCollisionRectNoCam().right -GetPosX();
		float fWidthL =   GetCollisionRectNoCam().left - GetPosX();
		float fHeightT = GetCollisionRectNoCam().top -	GetPosY();
		float fHeightB = GetCollisionRectNoCam().bottom -GetPosY();

		RECT rTemp = col->GetCollisionRect();
		if(GetCollisionRect().left >= rTemp.left && GetCollisionRect().right <= rTemp.right)
		{
			if(GetCollisionRect().bottom >= rTemp.top && GetCollisionRect().top <= rTemp.top)
			{
				if(GetVelY() > 0)
				{
					SetVelY(0);
					SetPosY(m_fLastY);
				}
			}
			else if(GetCollisionRect().top <= rTemp.bottom && GetCollisionRect().bottom >= rTemp.bottom)
			{
				if(GetVelY() < 0)
				{
					SetVelY(0);
					SetPosY(m_fLastY);
				}
			}
		}

		if(GetCollisionRect().left <= rTemp.right && GetCollisionRect().left >= rTemp.left)
		{
			if(GetVelX() < 0)
			{
				SetVelX(0);
				SetPosX(m_fLastX);
			}
		}
		else if(GetCollisionRect().right >= rTemp.left && GetCollisionRect().right <= rTemp.right)
		{
			if(GetVelX() > 0)
			{
				SetVelX(0);
				SetPosX(m_fLastX);
			}
		}

		if(GetCollisionRect().bottom >= rTemp.top && GetCollisionRect().top <= rTemp.top)
		{
			if(GetVelY() < 0)
			{
				SetVelY(0);
				SetPosY(m_fLastY);
			}
		}
		else if(GetCollisionRect().top <= rTemp.bottom && GetCollisionRect().bottom >= rTemp.bottom)
		{
			if(GetVelY() > 0)
			{
				SetVelY(0);
				SetPosY(m_fLastY);
			}
		}
	}
}

void CPlayer::HandleEvent( const CEvent* pEvent )
{
	for(unsigned int i = 0; i < m_szListen.size(); i++)
	{
		bool bHeard = false;
		if(pEvent->GetEventID() == m_szListen[i])
		{
			for(unsigned int nLoop = 0; nLoop < m_szHeard.size(); nLoop++)
			{
				if(m_szHeard[nLoop] == m_szListen[i])
				{
					bHeard = true;
					break;
				}
			}
			if(!bHeard)
				m_szHeard.push_back(m_szListen[i]);
			break;
		}
	}

}

void CPlayer::SetUnit	(CPlayerUnit* pUnit)
{
	if(m_cBattle != nullptr)
		m_cBattle->Release();

	m_cBattle = pUnit;

	if(m_cBattle != nullptr)
		m_cBattle->AddRef();
}

void CPlayer::AddListen (std::string szEvent)
{
	if(szEvent == "")
		return;
	for(unsigned int i = 0; i < m_szListen.size(); i++)
	{
		if(m_szListen[i] == szEvent)
			return;
	}

	m_szListen.push_back(szEvent);
	CSGD_EventSystem::GetInstance()->RegisterClient(szEvent.c_str(), this);
}

void CPlayer::BroadCastHeard()
{
	this->SetBroadcasting(true);
	for(unsigned int i = 0; i < m_szHeard.size(); i++)
	{
		CSGD_EventSystem::GetInstance()->SendEventNow(m_szHeard[i]);
	}
	this->SetBroadcasting(false);
}

void CPlayer::AddHeard (std::string szEvent)
{
	if(szEvent == "")
		return;
	for(unsigned int i = 0; i < m_szHeard.size(); i++)
	{
		if(m_szHeard[i] == szEvent)
			return;
	}

	m_szHeard.push_back(szEvent);
}
