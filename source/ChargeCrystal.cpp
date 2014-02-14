#include "ChargeCrystal.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "BattleState.h"
#include "TutorialBattle.h"
#include "GamePlayState.h"
#include "Buff.h"

CChargeCrystal::CChargeCrystal(void)
{
	m_fMoveSpeed = 100.0f;
	m_fTimer = 2.0f;
	m_nSuccess = 0;
	m_nChargeImgID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_ChargeCrystal.png"));
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_Gem.png"));
	m_fRadius = CSGD_TextureManager::GetInstance()->GetTextureWidth(m_nChargeImgID) * 0.5f;
	m_fRotation = 0.0f;
	m_bFailed = false;
	m_fScale = 1.0f;
	m_fCursorX = 400.0f;
	m_fCursorY = 200.0f;
	m_bHeal = false;

}


CChargeCrystal::~CChargeCrystal(void)
{

}

void CChargeCrystal::Render()
{

	CSGD_TextureManager* pTM= CSGD_TextureManager::GetInstance();
	RECT rTemp = {0,0,128,128};

	pTM->Draw(m_nChargeImgID, int(400-64*m_fScale), int(200-64*m_fScale), m_fScale, m_fScale, &rTemp, 64*m_fScale,64*m_fScale,m_fRotation, D3DCOLOR_XRGB(255,255,255));
	RECT rGem = {0,0,16,16};
	pTM->Draw(m_nCursorImageID, int(m_fCursorX - 8), int(m_fCursorY - 8), 1.0f,1.0f,&rGem,8.0f,8.0f,-m_fRotation, D3DCOLOR_XRGB(255,255,255));
}

void CChargeCrystal::Update(float fElpasedTime)
{
	if(m_nSuccess < 3 && !m_bFailed)
	{
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
		float fX = 0.0f;
		float fY = 0.0f;
		m_fTimer -= fElpasedTime;
		m_fRotation += (10.0f * fElpasedTime);

		if(pDI->KeyDown(DIK_UPARROW) ||pDI->KeyDown(DIK_W)  )
			fY -= 100.0f * fElpasedTime;
		else if(pDI->KeyDown(DIK_DOWNARROW) || pDI->KeyDown(DIK_S) )
			fY += 100.0f * fElpasedTime;
		if(pDI->KeyDown(DIK_LEFTARROW) || pDI->KeyDown(DIK_A) )
			fX -= 100.0f * fElpasedTime;
		else if(pDI->KeyDown(DIK_RIGHTARROW) || pDI->KeyDown(DIK_D) )
			fX += 100.0f * fElpasedTime;

		if(m_fCursorX < 400)
			fX -= 50.0f * fElpasedTime;
		else
			fX += 50.0f * fElpasedTime;

		if(m_fCursorY < 200)
			fY -= 50.0f * fElpasedTime;
		else
			fY += 50.0f * fElpasedTime;

		m_fCursorX += fX;
		m_fCursorY += fY;

		if(m_fTimer < 0.0f)
		{
			if(ScalarDistance(400,200,m_fCursorX, m_fCursorY) < m_fRadius)
			{
				switch (m_nSuccess)
				{
				case 0:
					SetDamage(1.3f);
					m_fScale -= 0.1f;
					m_fRadius = CSGD_TextureManager::GetInstance()->GetTextureWidth(m_nChargeImgID) * 0.5f * m_fScale;
					m_fTimer = 1.5f;
					PlaySuccess();
					break;
				case 1:
					SetDamage(1.6f);
					m_fScale -= 0.1f;
					m_fRadius = CSGD_TextureManager::GetInstance()->GetTextureWidth(m_nChargeImgID) * 0.5f * m_fScale;
					m_fTimer = 1.0f;
					PlaySuccess();
					break;
				case 2:
					SetDamage(2.3f);
					PlayCrit();
					break;
				default:
					break;
				}
				m_nSuccess++;
			}
			else
			{
				m_bFailed = true;
				PlayFail();
			}
			if(m_nSuccess == 3 || m_bFailed)
			{
				switch (m_nSuccess)
				{
				case 0:
					GetOwner()->EndTurn();
					break;
				case 1:
					InstantiateSkill();
					break;
				case 2:
					InstantiateSkill();
					break;
				case 3:
					InstantiateSkill();
					break;
				default:
					break;
				}
			}
		}
	}
}

void CChargeCrystal::ResetSkill()
{
	m_fRotation = 0.0f;
	m_fMoveSpeed = 100.0f;
	m_fTimer = 2.0f;
	m_nSuccess = 0;
	m_fRadius = CSGD_TextureManager::GetInstance()->GetTextureWidth(m_nChargeImgID) * 0.5f;
	m_fScale = 1.0f;
	SetDamage(0);
	m_bFailed = false;
	m_fCursorX = 400.0f;
	m_fCursorY = 200.0f;

}

void CChargeCrystal::InstantiateSkill()
{
	CProjectile* pTemp = GetSkill();
	if(pTemp != nullptr)
	{
		CUnits* tempP;
		if(DamageSkill())
		{
			tempP = CBattleState::GetInstance()->GetCurrentTarget();
			CProjectile* pNewProjectile = new CProjectile();
			pNewProjectile->SetMasterGame(this);
			pNewProjectile->SetTarget(tempP);
			pNewProjectile->GetAnimInfo()->SetAnimation(pTemp->GetAnimInfo()->GetCurrentAnimation());
			pNewProjectile->SetPosX(CGamePlayState::GetInstance()->GetPlayerUnit()->GetPosX());
			pNewProjectile->SetPosY(CGamePlayState::GetInstance()->GetPlayerUnit()->GetPosY());
			pTemp->PlaySFX();
			CBattleState::GetInstance()->AddSkill(pNewProjectile);
		}
		else
		{
			tempP = GetOwner();
			CBuff* pBuff = new CBuff();
			pBuff->SetMasterGame(this);
			pBuff->SetTarget(tempP);
			pBuff->GetAnimInfo()->SetAnimation(pTemp->GetAnimInfo()->GetCurrentAnimation());
			pBuff->SetPosX(CGamePlayState::GetInstance()->GetPlayerUnit()->GetPosX());
			pBuff->SetPosY(CGamePlayState::GetInstance()->GetPlayerUnit()->GetPosY());
			pTemp->PlaySFX();
			CBattleState::GetInstance()->AddSkill(pBuff);
			pBuff->Release();
		}

	}
}

void CChargeCrystal::DoAttack(void)
{
	if(DamageSkill())
	{
		CUnits* tempP;
		switch (m_nSuccess)
		{
		case 0:
			GetOwner()->EndTurn();
			break;
		case 1:
			if(!GetTutorial())
				tempP = CBattleState::GetInstance()->GetCurrentTarget();
			else
				tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

			if(GetOwner() != nullptr)
			{
				int temp = GetOwner()->GetAttack();
				tempP->ModifyHealth(int(temp * GetDamage()), false);
			}
			GetOwner()->EndTurn();
			break;
		case 2:
			if(!GetTutorial())
				tempP = CBattleState::GetInstance()->GetCurrentTarget();
			else
				tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

			if(GetOwner() != nullptr)
			{
				int temp = GetOwner()->GetAttack();
				tempP->ModifyHealth(int(temp * GetDamage()), false);
			}
			GetOwner()->EndTurn();
			break;
		case 3:
			if(!GetTutorial())
				tempP = CBattleState::GetInstance()->GetCurrentTarget();
			else
				tempP = CTutorialBattle::GetInstance()->GetCurrentTarget();

			if(GetOwner() != nullptr)
			{
				int temp = GetOwner()->GetAttack();
				tempP->ModifyHealth(int(temp * GetDamage()), true);
			}
			GetOwner()->EndTurn();
			break;
		default:
			break;
		}
	}
	else
	{
		if(m_bHeal)
		{
			switch (m_nSuccess)
			{
			case 0:
				GetOwner()->EndTurn();
				break;
			case 1:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyHealth(-int(temp * GetDamage()), false);
					GetOwner()->EndTurn();
				}
				break;
			case 2:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyHealth(-int(temp * GetDamage()), false);
					GetOwner()->EndTurn();
				}
				break;
			case 3:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyHealth(-int(temp * GetDamage()), true);
					GetOwner()->EndTurn();
				}
				break;
			default:
				break;
			}
		}
		else
		{
			switch (m_nSuccess)
			{
			case 0:
				GetOwner()->EndTurn();
				break;
			case 1:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyAP(-int(temp * GetDamage()));
					GetOwner()->EndTurn();
				}
				break;
			case 2:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyAP(-int(temp * GetDamage()));
					GetOwner()->EndTurn();
				}
				break;
			case 3:
				if(GetOwner() != nullptr)
				{
					int temp = GetOwner()->GetAttack();
					GetOwner()->ModifyAP(-int(temp * GetDamage()));
					GetOwner()->EndTurn();
				}
				break;
			default:
				break;
			}


		}
	}
}