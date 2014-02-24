#include "TriggerSpree.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "PlayerUnit.h"
#include "BattleState.h"
#include "Game.h"
#include "BitmapFont.h"
#include "TutorialBattle.h"
#include <sstream>
using namespace std;


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

	CBitmapFont* pFont = CGame::GetInstance()->GetFont("Arial");
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT rTemp = {};
	for(unsigned int i = 0; i < m_vGameElements.size(); i++)
	{
		rTemp.left =m_vGameElements[i]->left;
		rTemp.right = m_vGameElements[i]->right;
		rTemp.bottom =m_vGameElements[i]->bottom;
		rTemp.top = m_vGameElements[i]->top;

		RECT temp1;
		temp1.top = 64;
		temp1.left = 200;
		temp1.right = 600;
		temp1.bottom = 96;
		pD3D->DrawRect(temp1, D3DCOLOR_ARGB(120, 255, 0, 0 ));

		RECT temp;
		temp.top = 64;
		temp.left = 264;
		temp.right = 296;
		temp.bottom = 96;
		pD3D->DrawRect(temp, D3DCOLOR_ARGB(255, 0, 200, 0 ));

		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));

	}

	for(unsigned int i = 0; i < m_vTriggers.size(); i++)
	{
		rTemp.left =m_vTriggers[i]->left;
		rTemp.right = m_vTriggers[i]->right;
		rTemp.bottom =m_vTriggers[i]->bottom;
		rTemp.top = m_vTriggers[i]->top;
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(255, 0, 0, 255 ));
		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));
	}

	wostringstream woss;
	wostringstream coss;


	woss << m_nSuccess;
	coss << GetChances();

	pFont->Draw(woss.str().c_str(), 264, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));
	pFont->Draw(_T(" out of "), 300, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));
	pFont->Draw(coss.str().c_str(), 400, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));


}

void CTriggerSpree::Update(float fElapsedTime)
{
	m_fTimer -= fElapsedTime;

	if(m_fTimer < 0.0f)
	{
		m_fTimer = (rand() % 5 + 1) * 0.1f;

		RECT* pRect = new RECT;
		pRect->top = 64;
		pRect->left = 600;
		pRect->right = 600;
		pRect->bottom = 96;	
		m_vTriggers.push_back(pRect);
	}

	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	for(unsigned int i = 0; i < m_vTriggers.size();)
	{
		m_vTriggers[i]->left -= long(200 * fElapsedTime);
		if(m_vTriggers[i]->left <= 584)
			m_vTriggers[i]->right -= long(200 * fElapsedTime);

		if(m_vTriggers[i]->left <= 200)
			m_vTriggers[i]->left = 200;

		if(m_vTriggers[i]->right <= 200)
		{
			delete m_vTriggers[i];
			m_vTriggers.erase(m_vTriggers.begin() + i);
			m_bFailed = true;
			PlayFail();
			return;
		}
		else i++;
	}

	if(pDI->KeyPressed(DIK_RETURN)|| pDI->JoystickButtonPressed(1))
	{
		GetOwner()->GetAnimInfo()->SetCurrentFrame(0);
		GetOwner()->GetAnimInfo()->SetAnimation("Warrior_Battle_Special_Attack");
		RECT rTemp = {};
		if(m_vTriggers.size() > 0)
		{
			if(IntersectRect(&rTemp, m_vTriggers[0], m_vGameElements[1]))
			{
				m_bSuccess = true;
				PlaySuccess();
				delete m_vTriggers[0];
				m_vTriggers.erase(m_vTriggers.begin());
			}
			else
			{
				m_bFailed = true;
				PlayFail();
			}
		}
	}

	if(m_bSuccess)
	{
		m_bSuccess = false;
		m_nSuccess++;
		CUnits* tempP;

		if(!GetTutorial())
			tempP = CBattleState::GetInstance()->GetCurrentTarget();
		else
			tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(int(temp * GetDamage()), false);
		}

		if(m_nSuccess >= GetChances())
		{
			CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(GetOwner());
			if(pTemp != nullptr)
			{
				if(!GetTutorial())
				{
					GetOwner()->EndTurn();
					PlayCompletion();

				}
				else
				{
					CTutorialBattle::GetInstance()->SetPlayerTurn(false);
					PlayCompletion();
					GetOwner()->EndTurn();
				}
			}
		}
	}
	else if(m_bFailed)
	{
		CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(GetOwner());
		if(pTemp != nullptr)
		{
			if(!GetTutorial())
				GetOwner()->EndTurn();
			else
			{
				CTutorialBattle::GetInstance()->SetPlayerTurn(false);
				GetOwner()->EndTurn();
			}
		}
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

void CTriggerSpree::HandleEvent( const CEvent* pEvent )
{

}
