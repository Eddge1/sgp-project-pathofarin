#include "ProfileMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "MainMenuState.h"
#include "Game.h"
#include <sstream>
CProfileMenuState::CProfileMenuState(void)
{
	m_eCurrState = PS_SELECT;
	m_bLeft = false;
	m_fOffSetX = 0.0f;
}

CProfileMenuState::~CProfileMenuState(void)
{
}

CProfileMenuState* CProfileMenuState::GetInstance( void )
{
	static CProfileMenuState s_Instance;

	return &s_Instance;
}

void CProfileMenuState::Activate()
{
	if(LoadSaves() == false)
	{

	}
	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png")));
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));

	m_bLeft = false;
	m_fOffSetX = 0.0f;

	m_fPosY = 172.0f;
}

void CProfileMenuState::Sleep()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetBackgroundImg());
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetCursorIMG());
	CSGD_XAudio2::GetInstance()->SFXUnloadSound(GetSFXID());
	SetSFXID(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
}

bool CProfileMenuState::Input()
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY <= 0.0f)
	{
		if(pDI->KeyPressed(DIK_ESCAPE))
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		if(pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP))
		{
			if(GetCursorSelection() <= 0)
				SetCursorSelection(5);
			else
				SetCursorSelection(GetCursorSelection() - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN))
		{
			if(GetCursorSelection() >= 5)
				SetCursorSelection(0);
			else
				SetCursorSelection(GetCursorSelection() + 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			switch (GetCursorSelection())
			{
			case 0:
				if(m_eCurrState != PS_NEWGAME)
					m_eCurrState = PS_NEWGAME;
				else
					m_eCurrState = PS_SELECT;
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				return false;
			case 4:
				if(m_eCurrState != PS_DELETE)
					m_eCurrState = PS_DELETE;
				else
					m_eCurrState = PS_SELECT;
			case 5:
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			default:
				break;
			}
		}
		return true;
	}
	return true;
}

void CProfileMenuState::Update(float fElapsedTime )
{
	if(m_fPosY > 0)
	{
		m_fPosY -= 200 * fElapsedTime;
		return;
	}
	else
	{
		if(m_bLeft)
			m_fOffSetX -= (20 * fElapsedTime);
		else
			m_fOffSetX += (20 * fElapsedTime);

		if(m_fOffSetX >= 10.0f)
			m_bLeft = true;
		else if(m_fOffSetX <= 0.0f)
			m_bLeft = false;
	}

}

void CProfileMenuState::Render()
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT rLogo = {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),144,m_fPosY,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));
	if(m_fPosY <= 0.0f)
	{
		std::wostringstream woss;
		woss << "New Game\n\n\tSlot 1: " << " " << "\n\n\tSlot 2: " << " " << "\n\n\tSlot 3: " << " " << "\n\nDelete\nMain Menu";
		CGame::GetInstance()->GetFont()->Draw(woss.str().c_str(), 64, 272,1.0f, D3DCOLOR_XRGB(0,0,0));

		RECT rTemp = {0,0,16,32};
		switch(GetCursorSelection())
		{
		case 0:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 + m_fOffSetX, 278, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 1:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 176 + m_fOffSetX, 339, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 2:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 176 + m_fOffSetX, 400, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 3:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 176 + m_fOffSetX, 461, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 4:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 +m_fOffSetX, 522, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 5:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 + m_fOffSetX, 552, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		default:
			break;


		}
	}
}

bool CProfileMenuState::LoadSaves( void )
{

	return true;
}
