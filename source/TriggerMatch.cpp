#include "TriggerMatch.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "PlayerUnit.h"
#include "BattleState.h"
#include "Game.h"
#include "BitmapFont.h"


CTriggerMatch::CTriggerMatch(void)
{
	SetDamage(1.4f);
	SetCost(30);
	SetChances(5);
	m_fMoveSpeed = 200.0f;
	m_nSuccess = 0;

	RECT* pRect = new RECT;
	pRect->top = 64;
	pRect->left = 516;
	pRect->right = 536;
	pRect->bottom = 96;
	m_vGameElements.push_back(pRect);

	pRect = new RECT;
	pRect->top = 64;
	pRect->bottom = 96;
	pRect->left = 396;
	pRect->right = 404;
	m_vGameElements.push_back(pRect);

	pRect = new RECT;
	pRect->top = 64;
	pRect->left = 264;
	pRect->right = 284;
	pRect->bottom = 96;
	m_vGameElements.push_back(pRect);

	pRect = new RECT;
	pRect->top = 64;
	pRect->left = 200;
	pRect->right = 600;
	pRect->bottom = 96;
	m_vGameElements.push_back(pRect);

	m_rTrigger.top = 64;
	m_rTrigger.left = 200;
	m_rTrigger.right = 206;
	m_rTrigger.bottom = 96;	
	m_bLeft = false;
	m_bSuccess = false;
	m_bCritical = false;
	m_bFailed = false;
}


CTriggerMatch::~CTriggerMatch(void)
{
	for(unsigned int i = 0; i < m_vGameElements.size(); i++)
		delete m_vGameElements[i];

	m_vGameElements.clear();
}

void CTriggerMatch::Render() 
{
	CBitmapFont* pFont = CGame::GetInstance()->GetFont("Arial");
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT rTemp = {};
	rTemp.left =m_vGameElements[3]->left;
	rTemp.right = m_vGameElements[3]->right;
	rTemp.bottom =m_vGameElements[3]->bottom;
	rTemp.top = m_vGameElements[3]->top;
	pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(120, 255, 0, 0 ));
	pD3D->DrawHollowRect(rTemp, D3DCOLOR_ARGB(255, 0, 0, 0 ), 1);


	for(unsigned int i = 0; i < m_vGameElements.size() - 1; i++)
	{
		rTemp.left =m_vGameElements[i]->left;
		rTemp.right = m_vGameElements[i]->right;
		rTemp.bottom =m_vGameElements[i]->bottom;
		rTemp.top = m_vGameElements[i]->top;

		if(i != 1)
			pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(255, 0, 200, 0 ));
		else
			pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(255, 0, 0, 200 ));

		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0), 1);

	}

	pD3D->DrawRect(m_rTrigger, D3DCOLOR_ARGB(255, 0, 0, 255 ));
	pD3D->DrawHollowRect(m_rTrigger, D3DCOLOR_XRGB(0,0,0), 1);

	wostringstream woss;
	wostringstream coss;


	woss << m_nSuccess;
	coss << GetChances();

	pFont->Draw(woss.str().c_str(), 264, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));
	pFont->Draw(_T(" out of "), 300, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));
	pFont->Draw(coss.str().c_str(), 400, 35, 1.0f, D3DCOLOR_XRGB(0,0,0));

}

void CTriggerMatch::Update(float fElpasedTime) 
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(m_bLeft)
	{
		m_rTrigger.left -= long(m_fMoveSpeed * fElpasedTime);
		m_rTrigger.right -= long(m_fMoveSpeed * fElpasedTime);
	}
	else
	{
		m_rTrigger.left += long(m_fMoveSpeed * fElpasedTime);
		m_rTrigger.right += long(m_fMoveSpeed * fElpasedTime);
	}
	if(m_rTrigger.right >= 600)
		m_bLeft = true;
	else if(m_rTrigger.left <= 200)
		m_bLeft = false;


	if(pDI->KeyPressed(DIK_RETURN))
	{
		GetOwner()->GetAnimInfo()->SetCurrentFrame(0);
		GetOwner()->GetAnimInfo()->SetAnimation("Warrior_Battle_Special_Attack");
		RECT rTemp = {};
		for(unsigned int i = 0; i < m_vGameElements.size() - 1; i++)
		{
			if(IntersectRect(&rTemp, &m_rTrigger,m_vGameElements[i]))
			{
				if(i == 1)
				{
					m_bCritical = true;
					break;
				}
				else
				{
					m_bSuccess = true;
					break;
				}
			}
		}
		if(!m_bCritical && !m_bSuccess)
			m_bFailed = true;
	}

	if(m_bSuccess)
	{
		m_fMoveSpeed += 30.0f;
		m_nSuccess++;
		CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(int(temp * GetDamage()), false);
		}
		m_bSuccess = false;
	}
	else if(m_bCritical)
	{
		m_fMoveSpeed += 50.0f;
		m_nSuccess++;
		CUnits* tempP = CBattleState::GetInstance()->GetCurrentTarget();
		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(int(temp * GetDamage() + int(temp * GetDamage() * 0.1f)), true);
		}
		m_bCritical = false;
	}

	if(m_nSuccess >= GetChances() || m_bFailed)
	{
		GetOwner()->EndTurn();
		ResetSkill();
	}
}

void CTriggerMatch::ResetSkill() 
{
	m_bLeft = false;
	m_rTrigger.top = 64;
	m_rTrigger.left = 200;
	m_rTrigger.right = 206;
	m_rTrigger.bottom = 96;

	m_bSuccess = false;
	m_bCritical = false;
	m_bFailed = false;
	m_fMoveSpeed = 200.0f;
	m_nSuccess = 0;
}
