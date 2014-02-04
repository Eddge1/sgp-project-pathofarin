#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"

CGameOverState::CGameOverState(void)
{
	m_music = -1;
	timer = 8.0f;
	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
}

CGameOverState::~CGameOverState(void)
{
	CGame::GetInstance()->ChangeState(nullptr);
}

CGameOverState* CGameOverState::GetInstance( void )
{
	static CGameOverState s_Instance;

	return &s_Instance;
}

void CGameOverState::Activate(void)
{
	m_music = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_DEATH.xwm"));
	CSGD_XAudio2::GetInstance()->MusicPlaySong(m_music, true);

}

void CGameOverState::Sleep(void)
{
	CSGD_XAudio2::GetInstance()->MusicUnloadSong(m_music);
}

void CGameOverState::Update(float fElapsedTime)
{
	timer -= fElapsedTime;
	if(timer <= 0.0f)
	{
		timer = 8.0f;
		CSGD_XAudio2::GetInstance()->MusicStopSong(m_music);
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	}
}

void CGameOverState::Render(void)
{
	CBitmapFont* temp = CGame::GetInstance()->GetFont();
	temp->Draw(_T("Game Over"), 300, 300, 1.0f, D3DCOLOR_XRGB(0,0,0));

}

bool CGameOverState::Input(void)
{
	return true;
}

