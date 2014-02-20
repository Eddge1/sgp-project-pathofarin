#include "SteadyShot.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "BattleState.h"
#include "TutorialBattle.h"
#include "GamePlayState.h"
CSteadyShot::CSteadyShot(void)
{
	m_fMoveSpeed = 50.0f;
	m_fTimer = 4.0f;
	m_fRadius = 128.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;
	m_bCompleted = false;

	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_Target.png"));
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_Cross.png"));
}


CSteadyShot::~CSteadyShot(void)
{
}

void CSteadyShot::DoAttack(void) 
{
	CUnits* tempP;

	if(!GetTutorial())
		tempP = CBattleState::GetInstance()->GetCurrentTarget();
	else
		tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

	if(GetOwner() != nullptr)
	{
		int temp = GetOwner()->GetAttack();
		float fDamage = ScalarDistance(400.0f,300.0f,m_fCursorX, m_fCursorY);
		if(fDamage < 127.0f)
		{
			fDamage = (fDamage * -1 + 128.0f) / 128.0f;
			temp = int(temp * GetDamage() * fDamage);
			tempP->ModifyHealth(temp, false);
			if(!GetTutorial())
				GetOwner()->EndTurn();
			else
			{
				CTutorialBattle::GetInstance()->SetPlayerTurn(false);
				GetOwner()->EndTurn();
			}
		}
		else
			GetOwner()->EndTurn();
	}
}
void CSteadyShot::Update(float fElapsedTime)
{
	m_fTimer -= fElapsedTime;
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	float fX = 0.0f;
	float fY = 0.0f;

	if(pDI->KeyDown(DIK_UPARROW) ||pDI->KeyDown(DIK_W) || pDI->JoystickDPadDown(DIR_UP) || pDI->JoystickGetLStickDirDown(DIR_UP)  )
		fY -= 100.0f * fElapsedTime;
	else if(pDI->KeyDown(DIK_DOWNARROW) || pDI->KeyDown(DIK_S) || pDI->JoystickDPadDown(DIR_DOWN) || pDI->JoystickGetLStickDirDown(DIR_DOWN)  )
		fY += 100.0f * fElapsedTime;
	if(pDI->KeyDown(DIK_LEFTARROW) || pDI->KeyDown(DIK_A) || pDI->JoystickDPadDown(DIR_LEFT) || pDI->JoystickGetLStickDirDown(DIR_LEFT)  )
		fX -= 100.0f * fElapsedTime;
	else if(pDI->KeyDown(DIK_RIGHTARROW) || pDI->KeyDown(DIK_D) || pDI->JoystickDPadDown(DIR_RIGHT) || pDI->JoystickGetLStickDirDown(DIR_RIGHT)  )
		fX += 100.0f * fElapsedTime;

	if(m_fCursorX < 400)
		fX -= 50.0f * fElapsedTime;
	else
		fX += 50.0f * fElapsedTime;

	if(m_fCursorY < 300)
		fY -= 50.0f * fElapsedTime;
	else
		fY += 50.0f * fElapsedTime;

	m_fCursorX += fX;
	m_fCursorY += fY;


	if(m_fTimer <= 0 && !m_bCompleted)
	{
		m_bCompleted = true;
		DoAttack();
	}
}
void CSteadyShot::Render()
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	pTM->Draw(m_nImageID, 272, 172);
	pTM->Draw(m_nCursorImageID, int(m_fCursorX - 16), int(m_fCursorY-16));

	RECT rTimer = {272,140,long(272 + (256 * m_fTimer / 4.0f)),156};
	CSGD_Direct3D::GetInstance()->DrawRect(rTimer, D3DCOLOR_XRGB(0,255,255));
	rTimer.right = 528;
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rTimer, D3DCOLOR_XRGB(0,0,0), 1);

}
void CSteadyShot::ResetSkill()
{
	m_fMoveSpeed = 50.0f;
	m_fTimer = 4.0f;
	m_fRadius = 128.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 300.0f;
	m_bCompleted = false;
}