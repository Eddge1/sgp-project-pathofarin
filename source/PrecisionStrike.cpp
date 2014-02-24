#include "PrecisionStrike.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "BattleState.h"
#include "TutorialBattle.h"
#include "GamePlayState.h"

CPrecisionStrike::CPrecisionStrike(void)
{

	m_vTargets.clear();

	m_fTimer = 5.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;

	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_TargetPractice.png"));
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_Cross.png"));
	m_bReady = false;
	m_pTarget = nullptr;
}


CPrecisionStrike::~CPrecisionStrike(void)
{
}

void CPrecisionStrike::DoAttack(void) 
{

	if(GetOwner() != nullptr)
	{
		int temp = GetOwner()->GetAttack();
		temp = int(temp * GetDamage());
		if(m_pTarget != nullptr)
		{
			m_pTarget->ModifyHealth(temp, false);
			m_pTarget = nullptr;
		}
	}
}
void CPrecisionStrike::Update(float fElapsedTime)
{
	if(m_bReady)
	{
		m_fTimer -= fElapsedTime;
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
		float fX = 0.0f;
		float fY = 0.0f;

		if(pDI->KeyDown(DIK_UPARROW) ||pDI->KeyDown(DIK_W)  || pDI->JoystickDPadDown(DIR_UP) || pDI->JoystickGetLStickDirDown(DIR_UP) )
			fY -= 100.0f * fElapsedTime;
		else if(pDI->KeyDown(DIK_DOWNARROW) || pDI->KeyDown(DIK_S) || pDI->JoystickDPadDown(DIR_DOWN) || pDI->JoystickGetLStickDirDown(DIR_DOWN) )
			fY += 100.0f * fElapsedTime;
		if(pDI->KeyDown(DIK_LEFTARROW) || pDI->KeyDown(DIK_A) || pDI->JoystickDPadDown(DIR_LEFT) || pDI->JoystickGetLStickDirDown(DIR_LEFT) )
			fX -= 100.0f * fElapsedTime;
		else if(pDI->KeyDown(DIK_RIGHTARROW) || pDI->KeyDown(DIK_D) || pDI->JoystickDPadDown(DIR_RIGHT) || pDI->JoystickGetLStickDirDown(DIR_RIGHT) )
			fX += 100.0f * fElapsedTime;

		m_fCursorX += fX;
		m_fCursorY += fY;


		if(pDI->KeyPressed(DIK_RETURN)|| pDI->JoystickButtonPressed(1))
		{
			bool bSuccess = false;
			for(unsigned int i = 0; i < m_vTargets.size(); i++)
			{
				if(ScalarDistance(m_vTargets[i].fX + 16, m_vTargets[i].fY + 16, m_fCursorX, m_fCursorY) < 16.0f)
				{
					auto vUnits = CBattleState::GetInstance()->GetBattleUnits();
					for(unsigned int nLoop = 0; nLoop < vUnits.size(); nLoop++)
					{
						if(PointToRect(vUnits[nLoop]->GetCollisionRectNoCam(), int(m_vTargets[i].fX), int(m_vTargets[i].fY)))
						{
							m_pTarget = vUnits[nLoop];
							break;
						}
					}
					m_vTargets.erase(m_vTargets.begin() + i);
					bSuccess = true;
					break;
				}
			}
			if(bSuccess)
			{
				DoAttack();
				PlaySuccess();
			}
			else
				PlayFail();
		}

		if(m_fTimer <= 0 || m_vTargets.size() == 0)
		{
			if( m_vTargets.size() == 0)
				PlayCompletion();
			else if( m_vTargets.size() <= 5)
				PlayCrit();
			else
				PlayFail();
			GetOwner()->EndTurn();
		}
	}
	else
	{
		auto vUnits = CBattleState::GetInstance()->GetBattleUnits();

		for(unsigned int i = 0; i < vUnits.size(); i++)
		{
			if(vUnits[i]->GetType() != OBJ_PLAYER_UNIT)
			{
				int nRandom = rand() % 6 + 1;
				for(int nLoop = 0; nLoop < nRandom; nLoop++)
				{
					RECT rArea = vUnits[i]->GetCollisionRectNoCam();

					int nRangeX = rArea.right - rArea.left;
					int nRangeY = rArea.bottom - rArea.top;
					TargetLocs nTemp;
					nTemp.fX = float((rand() % nRangeX) + rArea.left);
					nTemp.fY = float((rand() % nRangeY) + rArea.top);

					m_vTargets.push_back(nTemp);
				}
			}
		}


		m_bReady = true;
	}
}
void CPrecisionStrike::Render()
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	for(unsigned int i = 0; i < m_vTargets.size(); i++)
		pTM->Draw(m_nImageID, int(m_vTargets[i].fX - 8), int(m_vTargets[i].fY - 8));

	pTM->Draw(m_nCursorImageID, int(m_fCursorX - 16), int(m_fCursorY - 16));

	RECT rTimer = {272,140,long(272 + (256 * m_fTimer / 4.0f)),156};
	CSGD_Direct3D::GetInstance()->DrawRect(rTimer, D3DCOLOR_XRGB(0,255,255));
	rTimer.right = 528;
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rTimer, D3DCOLOR_XRGB(0,0,0), 1);
}
void CPrecisionStrike::ResetSkill()
{
	m_vTargets.clear();

	m_bReady = false;

	m_fTimer = 5.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;
}

bool CPrecisionStrike::PointToRect(RECT& rCol, int nX, int nY)
{
	if(nX <= rCol.right && nX >= rCol.left)
	{
		if(nY >= rCol.top && nY <= rCol.bottom)
			return true;
	}
	return false;
}
