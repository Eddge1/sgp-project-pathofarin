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

	for(int i = 0; i < 8; i++)
	{
		TargetLocs nTemp;
		nTemp.fX = rand() % 240 + 280.0f;
		nTemp.fY = rand() % 240 + 180.0f;

		m_vTargets.push_back(nTemp);
	}

	m_fTimer = 5.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;

	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_TargetPractice.png"));
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_Cross.png"));
}


CPrecisionStrike::~CPrecisionStrike(void)
{
}

void CPrecisionStrike::DoAttack(void) 
{
	CUnits* tempP;

	if(!GetTutorial())
		tempP = CBattleState::GetInstance()->GetCurrentTarget();
	else
		tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

	if(GetOwner() != nullptr)
	{
		int temp = GetOwner()->GetAttack();
		temp = int(temp * GetDamage());
		tempP->ModifyHealth(temp, false);
	}
}
void CPrecisionStrike::Update(float fElapsedTime)
{
	m_fTimer -= fElapsedTime;
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	float fX = 0.0f;
	float fY = 0.0f;

	if(pDI->KeyDown(DIK_UPARROW) ||pDI->KeyDown(DIK_W)  )
		fY -= 100.0f * fElapsedTime;
	else if(pDI->KeyDown(DIK_DOWNARROW) || pDI->KeyDown(DIK_S) )
		fY += 100.0f * fElapsedTime;
	if(pDI->KeyDown(DIK_LEFTARROW) || pDI->KeyDown(DIK_A) )
		fX -= 100.0f * fElapsedTime;
	else if(pDI->KeyDown(DIK_RIGHTARROW) || pDI->KeyDown(DIK_D) )
		fX += 100.0f * fElapsedTime;

	m_fCursorX += fX;
	m_fCursorY += fY;


	if(pDI->KeyPressed(DIK_RETURN))
	{
		bool bSuccess = false;
		for(unsigned int i = 0; i < m_vTargets.size(); i++)
		{
			if(ScalarDistance(m_vTargets[i].fX + 16, m_vTargets[i].fY + 16, m_fCursorX, m_fCursorY) < 16.0f)
			{
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
		GetOwner()->EndTurn();
	}
}
void CPrecisionStrike::Render()
{
	RECT rBackground = {272,172,528,428};
	CSGD_Direct3D::GetInstance()->DrawRect(rBackground, D3DCOLOR_ARGB(200,255,218,185));
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rBackground, D3DCOLOR_XRGB(0,0,0),1);

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

	for(int i = 0; i < 8; i++)
	{
		TargetLocs nTemp;
		nTemp.fX = rand() % 240 + 280.0f;
		nTemp.fY = rand() % 240 + 180.0f;

		m_vTargets.push_back(nTemp);
	}

	m_fTimer = 5.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;
}