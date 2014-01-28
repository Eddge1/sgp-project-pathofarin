#include "TriggerSpree.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "PlayerUnit.h"
#include "BattleState.h"


CTriggerSpree::CTriggerSpree(void)
{
	m_bSuccess = false;
	m_bFailed = false;
	m_fTimer = 0.5f;
	m_nSuccess = 0;
	SetChances(10);
	SetDamage(0.6f);
	SetCost(10);

	RECT* pRect = new RECT;
	pRect->top = 64;
	pRect->left = 200;
	pRect->right = 600;
	pRect->bottom = 96;
	m_vGameElements.push_back(pRect);

	pRect = new RECT;
	pRect->top = 64;
	pRect->left = 264;
	pRect->right = 296;
	pRect->bottom = 96;
	m_vGameElements.push_back(pRect);

	pRect = new RECT;
	pRect->top = 64;
	pRect->left = 600;
	pRect->right = 600;
	pRect->bottom = 96;	
	m_vTriggers.push_back(pRect);
}


CTriggerSpree::~CTriggerSpree(void)
{
	for(unsigned int i = 0; i < m_vGameElements.size(); i++)
		delete m_vGameElements[i];

	m_vGameElements.clear();

	for(unsigned int i = 0; i < m_vTriggers.size(); i++)
		delete m_vTriggers[i];

	m_vTriggers.clear();
}

void CTriggerSpree::Render() 
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT rTemp = {};
	for(unsigned int i = 0; i < m_vGameElements.size(); i++)
	{
		rTemp.left =m_vGameElements[i]->left;
		rTemp.right = m_vGameElements[i]->right;
		rTemp.bottom =m_vGameElements[i]->bottom;
		rTemp.top = m_vGameElements[i]->top;
		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));

	}

	for(unsigned int i = 0; i < m_vTriggers.size(); i++)
	{
		rTemp.left =m_vTriggers[i]->left;
		rTemp.right = m_vTriggers[i]->right;
		rTemp.bottom =m_vTriggers[i]->bottom;
		rTemp.top = m_vTriggers[i]->top;
		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));
	}
}

void CTriggerSpree::Update(float fElpasedTime)
{
	m_fTimer -= fElpasedTime;

	if(m_fTimer < 0.0f)
	{
		m_fTimer = 0.5f;

		RECT* pRect = new RECT;
		pRect->top = 64;
		pRect->left = 600;
		pRect->right = 600;
		pRect->bottom = 96;	
		m_vTriggers.push_back(pRect);
	}

	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	for(int i = 0; i < m_vTriggers.size();)
	{
		m_vTriggers[i]->left -= (200 * fElpasedTime);
		if(m_vTriggers[i]->left <= 584)
			m_vTriggers[i]->right -= (200 * fElpasedTime);

		if(m_vTriggers[i]->left <= 200)
			m_vTriggers[i]->left = 200;

		if(m_vTriggers[i]->right <= 200)
		{
			delete m_vTriggers[i];
			m_vTriggers.erase(m_vTriggers.begin() + i);
			m_bFailed = true;
			return;
		}
		else i++;
	}

	if(pDI->KeyPressed(DIK_RETURN))
	{
		RECT rTemp = {};
		if(m_vTriggers.size() > 0)
		{
			if(IntersectRect(&rTemp, m_vTriggers[0], m_vGameElements[1]))
			{
				m_bSuccess = true;
				delete m_vTriggers[0];
				m_vTriggers.erase(m_vTriggers.begin());
			}
			else
				m_bFailed = true;
		}
	}

	if(m_bSuccess)
	{
		m_bSuccess = false;
		m_nSuccess++;

		CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(temp * GetDamage(), false);
		}

		if(m_nSuccess >= GetChances())
		{
			CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(GetOwner());
			if(pTemp != nullptr)
				GetOwner()->EndTurn();
		}
	}
	else if(m_bFailed)
	{
		CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(GetOwner());
		if(pTemp != nullptr)
			GetOwner()->EndTurn();
	}
}

void CTriggerSpree::ResetSkill()
{ 
	m_bSuccess = false;
	m_bFailed = false;
	m_fTimer = 0.5f;
	m_nSuccess = 0;


	for(unsigned int i = 0; i < m_vTriggers.size(); i++)
		delete m_vTriggers[i];
	m_vTriggers.clear();

	RECT* pRect = new RECT;
	pRect->top = 64;
	pRect->left = 600;
	pRect->right = 600;
	pRect->bottom = 96;	
	m_vTriggers.push_back(pRect);
}
