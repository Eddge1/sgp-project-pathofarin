#include "ComboGame.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "PlayerUnit.h"
#include "BattleState.h"
#include "TutorialBattle.h"
#include "Game.h"

CComboGame::CComboGame(void)
{
	int nMove = 0;
	SetCost(50);
	SetDamage(1.5f);
	m_vMoveList.clear();
	m_nTotalMoves = 4;
	m_nSuccessCombo = 0;
	for(int i = 0; i < m_nTotalMoves; i++)
	{
		m_vMoveList.push_back(rand() % 4);
	}
	m_vMovesMade.clear();
	m_nCombArrowImgID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_MoveArrow.png"));
	m_fTimer = 10.0f;

	m_bSuccess = false;
	m_nCurr = 0;
	m_fComboCompletionTimer = 0.0f;
	m_fComboFailTimer = 0.0f;
}


CComboGame::~CComboGame(void)
{
}

void CComboGame::ResetSkill()
{
	m_vMovesMade.clear();
	m_vMoveList.clear();
	m_nTotalMoves = 4;
	m_nSuccessCombo = 0;
	for(int i = 0; i < m_nTotalMoves; i++)
	{
		m_vMoveList.push_back(rand() % 4);
	}
	m_fTimer = 10.0f;
	m_bSuccess = false;
	m_nCurr = 0;
	m_fComboCompletionTimer = 0.0f;
	m_fComboFailTimer = 0.0f;
}

void CComboGame::Render()
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	RECT rTemp = {200,64,long(200 + (400 * (m_fTimer/ 10.0f))), 96};

	pD3D->DrawRect(rTemp, D3DCOLOR_XRGB(0,255,255));
	rTemp.right = 600;
	pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0),1);

	rTemp.left = 0;
	rTemp.right = 16;
	rTemp.top = 0;
	rTemp.bottom = 16;
	for(int i = m_nCurr; i < int(m_vMoveList.size()); i++)
	{
		if(m_vMoveList[i] == 0)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (i*16),97,1.0f,1.0f);
		else if(m_vMoveList[i] == 1)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f* 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI/2);
		else if(m_vMoveList[i] == 2)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f* 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI);
		else if(m_vMoveList[i] == 3)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f* 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,3*D3DX_PI/2);
	}
	for(int i = 0; i < m_nCurr; i++)
	{
		if(m_vMovesMade[i] == 0)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,0.0f,D3DCOLOR_XRGB(100,255,100));
		else if(m_vMovesMade[i] == 1)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI/2,D3DCOLOR_XRGB(100,255,100));
		else if(m_vMovesMade[i] == 2)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI,D3DCOLOR_XRGB(100,255,100));
		else if(m_vMovesMade[i] == 3)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (i*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,3*D3DX_PI/2,D3DCOLOR_XRGB(100,255,100));
	}
	if(m_fComboFailTimer > 0)
	{
		if(m_vMoveList[m_nCurr ] == 0)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (m_nCurr*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,0.0f,D3DCOLOR_XRGB(255,0,0));
		else if(m_vMoveList[m_nCurr] == 1)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (m_nCurr*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI/2,D3DCOLOR_XRGB(255,0,0));
		else if(m_vMoveList[m_nCurr] == 2)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (m_nCurr*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI,D3DCOLOR_XRGB(255,0,0));
		else if(m_vMoveList[m_nCurr ] == 3)
			pTM->Draw(m_nCombArrowImgID,400 - int(m_nTotalMoves *0.5f * 16) + (m_nCurr*16),97,1.0f,1.0f,&rTemp,8.0f,8.0f,3*D3DX_PI/2,D3DCOLOR_XRGB(255,0,0));

	}
}

void CComboGame::Update(float fElapsedTime)
{
	if(m_fComboFailTimer > 0)
		m_fComboFailTimer -= fElapsedTime;
	if(m_fComboCompletionTimer <= 0)
	{
		m_fTimer -= fElapsedTime;
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
		if(pDI->KeyPressed(DIK_RIGHTARROW) || pDI->KeyPressed(DIK_D) || pDI->JoystickDPadPressed(DIR_RIGHT) || pDI->JoystickGetLStickDirPressed(DIR_RIGHT)  )
		{
			if(m_vMoveList[m_nCurr] == 0)
			{
				m_vMovesMade.push_back(0);
				m_nCurr++;
				PlaySuccess();
			}
			else
			{
				if(m_vMovesMade.size() > 0)
					m_vMovesMade.pop_back();
				m_nCurr--;
				PlayFail();
				m_fComboFailTimer = 0.5f;

			}

		}

		if(pDI->KeyPressed(DIK_UPARROW) || pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP)  )
		{
			if(m_vMoveList[m_nCurr] == 3)
			{
				m_vMovesMade.push_back(3);
				m_nCurr++;
				PlaySuccess();

			}
			else
			{
				if(m_vMovesMade.size() > 0)
					m_vMovesMade.pop_back();
				m_nCurr--;
				PlayFail();
				m_fComboFailTimer = 0.5f;

			}
		}

		if(pDI->KeyPressed(DIK_LEFTARROW) || pDI->KeyPressed(DIK_A) || pDI->JoystickDPadPressed(DIR_LEFT) || pDI->JoystickGetLStickDirPressed(DIR_LEFT))
		{
			if(m_vMoveList[m_nCurr] == 2)
			{
				m_vMovesMade.push_back(2);
				m_nCurr++;
				PlaySuccess();
			}
			else
			{
				if(m_vMovesMade.size() > 0)
					m_vMovesMade.pop_back();
				m_nCurr--;
				PlayFail();
				m_fComboFailTimer = 0.5f;

			}
		}

		if(pDI->KeyPressed(DIK_DOWNARROW) || pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			if(m_vMoveList[m_nCurr] == 1)
			{
				m_vMovesMade.push_back(1);
				m_nCurr++;
				PlaySuccess();
			}
			else
			{
				if(m_vMovesMade.size() > 0)
					m_vMovesMade.pop_back();
				m_nCurr--;
				PlayFail();
				m_fComboFailTimer = 0.5f;
			}
		}

		if(m_nCurr < 0)
			m_nCurr = 0;

		if(m_vMovesMade.size() > unsigned int(m_nTotalMoves))
			m_vMovesMade.erase(m_vMovesMade.begin());

		if(m_vMovesMade.size() > unsigned int(m_nTotalMoves - 1))
		{
			if(m_vMoveList == m_vMovesMade)
				m_bSuccess =true;
		}

		if(m_bSuccess)
		{
			m_fComboCompletionTimer = 0.33f;
			PlayCrit();
		}
	}
	else
		m_fComboCompletionTimer -= fElapsedTime;

	if(m_bSuccess && m_fComboCompletionTimer <0)
	{
		m_nSuccessCombo++;
		if(m_nSuccessCombo >= 3)
		{
			m_nTotalMoves++;
			m_nSuccessCombo = 0;
		}

		m_bSuccess = false;
		vector<int> vMoves;
		m_vMoveList.clear();
		for(int i = 0; i < m_nTotalMoves; i++)
		{
			m_vMoveList.push_back(rand() % 4);
		}
		m_vMovesMade.clear();
		m_fTimer += 1.0f;
		m_nCurr = 0;
		CUnits* tempP;

		if(!GetTutorial())
			tempP = CBattleState::GetInstance()->GetCurrentTarget();
		else
			tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

		if(GetOwner() != nullptr)
		{
			int temp = GetOwner()->GetAttack();
			tempP->ModifyHealth(int(temp * (GetDamage() + (0.25f * (m_nTotalMoves - 4)))), false);
		}
	}

	if(m_fTimer <= 0.0f)
	{
		if(!GetTutorial())
		{
			if(m_nTotalMoves >= 6)
				PlayCompletion();
			else if (m_nTotalMoves <= 4)
				PlayFail();
			else
				PlayCrit();
			GetOwner()->EndTurn();
		}
		else
		{
			CTutorialBattle::GetInstance()->SetPlayerTurn(false);
			if(m_nTotalMoves >= 6)
				PlayCompletion();
			else if (m_nTotalMoves <= 4)
				PlayFail();
			else
				PlayCrit();
			GetOwner()->EndTurn();
		}
		ResetSkill();
	}
}