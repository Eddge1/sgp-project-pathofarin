#include "Npcs.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "GamePlayState.h"
#include "Player.h"

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

	m_nChat = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_Chat_Open.wav"));
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
	m_fLastX = GetPosX();
	m_fLastY = GetPosY();
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

		if(GetPosY() < m_vWaypoints[m_nWaypoint]->locY - 1)
		{
			SetVelY(100);
			string szTemp = GetName();
			szTemp += "_Walk_Down";
			GetAnimInfo()->SetAnimation(szTemp.c_str());
		}
		else if(GetPosY() > m_vWaypoints[m_nWaypoint]->locY + 1)
		{
			SetVelY(-100);
			string szTemp = GetName();
			szTemp += "_Walk_Up";
			GetAnimInfo()->SetAnimation(szTemp.c_str());
		}


		if(GetPosX() < m_vWaypoints[m_nWaypoint]->locX - 1)
		{
			SetVelX(100);
			if(GetVelY() == 0)
			{
				string szTemp = GetName();
				szTemp += "_Walk_Right";
				GetAnimInfo()->SetAnimation(szTemp.c_str());

			}
		}
		else if(GetPosX() > m_vWaypoints[m_nWaypoint]->locX + 1)
		{
			SetVelX(-100);
			if(GetVelY() == 0)
			{
				string szTemp = GetName();
				szTemp += "_Walk_Left";
				GetAnimInfo()->SetAnimation(szTemp.c_str());
			}
		}
	}
	if (GetVelX() == 0 && GetVelY() == 0)
	{
		string szTemp = GetName();
		szTemp += "_Idle";
		GetAnimInfo()->SetAnimation(szTemp.c_str());
	}

	CEntity::Update(fElapsedTime);
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
	for(unsigned int i = 0; i < m_szEraseEvents.size();i++)
	{
		if(pEvent->GetEventID() == m_szEraseEvents[i])
		{
			this->SetActive(false);
			this->SetRender(false);
		}
	}
}

void CNpcs::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER)
	{		
		CPlayer* pTemp = reinterpret_cast<CPlayer*>(col);
		if(pTemp != nullptr)
		{
			if(!pTemp->GetIsWarping())
			{
				if(m_bIsHostile)
				{
					CSGD_EventSystem::GetInstance()->SendEventNow("INIT_BATTLE", nullptr, nullptr, this);
					SetActive(false);
					SetRender(false);
				}
				else
				{
					if(pTemp->GetInteraction() && m_fDelayChat <= 0.0f)
					{
						wostringstream woss;
						if(m_szConversation.size() > 0)
						{
							CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nChat);

							woss << m_szConversation[0].c_str();
							CGamePlayState::GetInstance()->AddFloatingText(this, D3DCOLOR_XRGB(0,0,0), woss);
							m_fDelayChat = 1.0f;
							if(m_szEventThrow != "")
							{
								CSGD_EventSystem::GetInstance()->SendEventNow(m_szEventThrow.c_str(), nullptr, nullptr, this);
							}
						}
						m_fDelayChat = 0.25f;
					}
				}
			}
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
}

void CNpcs::AddWaypoint(float fX, float fY)
{
	SWaypoint* pTemp = new SWaypoint();
	pTemp->locX = fX;
	pTemp->locY = fY;
	m_vWaypoints.push_back(pTemp);
}

void CNpcs::AddEraseEvent(std::string szEvent)
{
	if(szEvent == "")
		return;
	for(unsigned int i = 0; i < m_szEraseEvents.size(); i++)
	{
		if(m_szEraseEvents[i] == szEvent)
			return;
	}
	m_szEraseEvents.push_back(szEvent); 
	CSGD_EventSystem::GetInstance()->RegisterClient(szEvent.c_str(), this);
}