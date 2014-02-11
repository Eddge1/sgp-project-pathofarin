#include "Npcs.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "GamePlayState.h"

CNpcs::CNpcs(void)
{
	SetType(OBJ_NPC);
	m_bContainsUnits = false;
	m_bIsHostile = false;
	m_nWaypoint = 0;
	m_szEventThrow = "";
	CSGD_EventSystem::GetInstance()->RegisterClient("BATTLE_END", this);
	m_fDelayChat = 0.0f;
	m_bGameVictory = false;
}


CNpcs::~CNpcs(void)
{
	for(unsigned int i = 0; i < m_vWaypoints.size(); i++)
	{
		delete m_vWaypoints[i];
	}

	for(unsigned int i = 0; i < m_vUnitList.size(); i++)
		m_vUnitList[i]->Release();

	m_vUnitList.clear();

	m_vWaypoints.clear();

}

void CNpcs::SetUnits(CEnemyUnit* l)
{
	if(l != nullptr)
	{
		m_vUnitList.push_back(l);
	}
}

void CNpcs::AddConversation(std::string szConvo)
{
	m_szConversation.push_back(szConvo);
}

CEnemyUnit* CNpcs::GetUnit(int nI)
{
	if(nI < int(m_vUnitList.size()))
		return m_vUnitList[nI];
	return nullptr;
}

void CNpcs::Update(float fElapsedTime)
{
	SetVelX(0);
	SetVelY(0);
	m_fDelayChat -= fElapsedTime;
	if(m_vWaypoints.size() > 0 && GetActive())
	{
		if(GetPosX() <= m_vWaypoints[m_nWaypoint]->locX + 1 && GetPosX() >= m_vWaypoints[m_nWaypoint]->locX - 1)
		{
			if(GetPosY() <= m_vWaypoints[m_nWaypoint]->locY + 1 && GetPosY() >= m_vWaypoints[m_nWaypoint]->locY - 1)
			{
				m_nWaypoint++;
				if(m_nWaypoint >= int(m_vWaypoints.size()))
					m_nWaypoint = 0;
			}
		}

		if(GetPosX() < m_vWaypoints[m_nWaypoint]->locX - 1)
		{
			SetVelX(100);
			if (GetName() == "Orc")
			{
				GetAnimInfo()->SetAnimation("Orc_Walk_Right");
			}
			else if (GetName() == "Pathetic_Orc")
			{
				GetAnimInfo()->SetAnimation("Pathetic_Orc_Walk_Right");
			}
			else if (GetName() == "Orc_Leader")
			{
				GetAnimInfo()->SetAnimation("Orc_Leader_Walk_Right");
			}
			else if (GetName() == "Orc_Shaman")
			{
				GetAnimInfo()->SetAnimation("Orc_Shaman_Walk_Right");
			}
			else if (GetName() == "Cave_Spider")
			{
				GetAnimInfo()->SetAnimation("Cave_Spider_Walk_Right");
			}
			else if (GetName() == "Cave_Bat")
			{
				GetAnimInfo()->SetAnimation("Cave_Bat_Walk_Right");
			}
			else if (GetName() == "Ogre")
			{
				GetAnimInfo()->SetAnimation("Ogre_Walk_Right");
			}
			else if (GetName() == "Thornbiter")
			{
				GetAnimInfo()->SetAnimation("Thornbiter_Walk_Right");
			}
		}
		else if(GetPosX() > m_vWaypoints[m_nWaypoint]->locX + 1)
		{
			SetVelX(-100);
			if (GetName() == "Orc")
			{
				GetAnimInfo()->SetAnimation("Orc_Walk_Left");
			}
			else if (GetName() == "Pathetic_Orc")
			{
				GetAnimInfo()->SetAnimation("Pathetic_Orc_Walk_Left");
			}
			else if (GetName() == "Orc_Leader")
			{
				GetAnimInfo()->SetAnimation("Orc_Leader_Walk_Right");
			}
			else if (GetName() == "Orc_Shaman")
			{
				GetAnimInfo()->SetAnimation("Orc_Shaman_Walk_Left");
			}
			else if (GetName() == "Cave_Spider")
			{
				GetAnimInfo()->SetAnimation("Cave_Spider_Walk_Left");
			}
			else if (GetName() == "Cave_Bat")
			{
				GetAnimInfo()->SetAnimation("Cave_Bat_Walk_Left");
			}
			else if (GetName() == "Ogre")
			{
				GetAnimInfo()->SetAnimation("Ogre_Walk_Left");
			}
			else if (GetName() == "Thornbiter")
			{
				GetAnimInfo()->SetAnimation("Thornbiter_Walk_Left");
			}
		}

		if(GetPosY() < m_vWaypoints[m_nWaypoint]->locY - 1)
		{
			SetVelY(100);
			if (GetName() == "Orc")
			{
				GetAnimInfo()->SetAnimation("Orc_Walk_Down");
			}
			else if (GetName() == "Pathetic_Orc")
			{
				GetAnimInfo()->SetAnimation("Pathetic_Orc_Walk_Down");
			}
			else if (GetName() == "Orc_Leader")
			{
				GetAnimInfo()->SetAnimation("Orc_Leader_Walk_Right");
			}
			else if (GetName() == "Orc_Shaman")
			{
				GetAnimInfo()->SetAnimation("Orc_Shaman_Walk_Down");
			}
			else if (GetName() == "Cave_Spider")
			{
				GetAnimInfo()->SetAnimation("Cave_Spider_Walk_Down");
			}
			else if (GetName() == "Cave_Bat")
			{
				GetAnimInfo()->SetAnimation("Cave_Bat_Walk_Down");
			}
			else if (GetName() == "Ogre")
			{
				GetAnimInfo()->SetAnimation("Ogre_Walk_Down");
			}
			else if (GetName() == "Thornbiter")
			{
				GetAnimInfo()->SetAnimation("Thornbiter_Walk_Down");
			}
		}
		else if(GetPosY() > m_vWaypoints[m_nWaypoint]->locY + 1)
		{
			SetVelY(-100);
			if (GetName() == "Orc")
			{
				GetAnimInfo()->SetAnimation("Orc_Walk_Up");
			}
			else if (GetName() == "Pathetic_Orc")
			{
				GetAnimInfo()->SetAnimation("Pathetic_Orc_Walk_Up");
			}
			else if (GetName() == "Orc_Leader")
			{
				GetAnimInfo()->SetAnimation("Orc_Leader_Walk_Right");
			}
			else if (GetName() == "Orc_Shaman")
			{
				GetAnimInfo()->SetAnimation("Orc_Shaman_Walk_Up");
			}
			else if (GetName() == "Cave_Spider")
			{
				GetAnimInfo()->SetAnimation("Cave_Spider_Walk_Up");
			}
			else if (GetName() == "Cave_Bat")
			{
				GetAnimInfo()->SetAnimation("Cave_Bat_Walk_Up");
			}
			else if (GetName() == "Ogre")
			{
				GetAnimInfo()->SetAnimation("Ogre_Walk_Up");
			}
			else if (GetName() == "Thornbiter")
			{
				GetAnimInfo()->SetAnimation("Thornbiter_Walk_Up");
			}
		}
		else
		{
			if (GetName() == "Orc")
			{
				GetAnimInfo()->SetAnimation("Orc_Idle");
			}
			else if (GetName() == "Pathetic_Orc")
			{
				GetAnimInfo()->SetAnimation("Pathetic_Orc_Idle");
			}
			else if (GetName() == "Orc_Leader")
			{
				GetAnimInfo()->SetAnimation("Orc_Leader_Idle");
			}
			else if (GetName() == "Orc_Shaman")
			{
				GetAnimInfo()->SetAnimation("Orc_Shaman_Idle");
			}
			else if (GetName() == "Cave_Spider")
			{
				GetAnimInfo()->SetAnimation("Cave_Spider_Idle");
			}
			else if (GetName() == "Cave_Bat")
			{
				GetAnimInfo()->SetAnimation("Cave_Bat_Idle");
			}
			else if (GetName() == "Ogre")
			{
				GetAnimInfo()->SetAnimation("Ogre_Idle");
			}
			else if (GetName() == "Thornbiter")
			{
				GetAnimInfo()->SetAnimation("Thornbiter_Idle");
			}
		}

		CEntity::Update(fElapsedTime);
	}
}

void CNpcs::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "BATTLE_END" && this == pEvent->GetDestination())
	{
		if(m_szEventThrow != "")
		{
			CSGD_EventSystem::GetInstance()->SendEventNow(m_szEventThrow.c_str(), nullptr, nullptr, this);
		}
	}
	if (pEvent->GetEventID() == "VALRION_DEFEAT")
	{
		m_szConversation.pop_back();
		m_szConversation.push_back("Thank you for saving our Village! We are forever in your debt!\n...You have Won the First Playable! Congratulations!");
		m_bGameVictory = true;
	}
}

void CNpcs::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER)
	{
		if(m_bIsHostile)
		{
			CSGD_EventSystem::GetInstance()->SendEventNow("INIT_BATTLE", nullptr, nullptr, this);
			SetActive(false);
			SetRender(false);
		}
		else
		{
			if(m_fDelayChat < 0)
			{
				wostringstream woss;
				if(m_szConversation.size() > 0)
				{
					woss << m_szConversation[0].c_str();
					CGamePlayState::GetInstance()->AddFloatingText(this, D3DCOLOR_XRGB(0,0,0), woss);
					if(m_bGameVictory)
						CSGD_EventSystem::GetInstance()->SendEventNow("GAME_WON", nullptr, nullptr, this);
					m_fDelayChat = 1.0f;
				}
			}
		}
		RECT rTemp = col->GetCollisionRect();
		int nMid = rTemp.top + (rTemp.bottom - rTemp.top) / 2;
		if(GetCollisionRect().left > rTemp.right - 20 && GetCollisionRect().left < rTemp.right)
		{
			SetPosX(GetPosX() +1);
			SetVelX(0);
		}
		else if(GetCollisionRect().right < rTemp.left + 20 && GetCollisionRect().right > rTemp.left)
		{
			SetPosX(GetPosX() -1);
			SetVelX(0);
		}
		else if(GetCollisionRect().left > rTemp.right && GetCollisionRect().right < rTemp.left)
		{
			if(GetCollisionRect().bottom < rTemp.top + 20 && GetCollisionRect().bottom > rTemp.top)
			{
				if(GetVelY() > 0)
				{
					SetPosY(GetPosY() - 1);
					SetVelY(0);
				}
			}
			else if(GetCollisionRect().top > rTemp.bottom - 20 && GetCollisionRect().top < rTemp.bottom)
			{
				SetPosY(GetPosY() + 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().bottom < rTemp.top + 20 && GetCollisionRect().bottom > rTemp.top)
		{
			if(GetVelY() > 0)
			{
				SetPosY(GetPosY() - 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().top > rTemp.bottom - 20 && GetCollisionRect().top < rTemp.bottom)
		{
			SetPosY(GetPosY() + 1);

			SetVelY(0);
		}

	}

}

void CNpcs::AddWaypoint(float fX, float fY)
{
	SWaypoint* pTemp = new SWaypoint();
	pTemp->locX = fX;
	pTemp->locY = fY;
	m_vWaypoints.push_back(pTemp);
}
