#include "BattleState.h"
#include "Units.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "RenderManager.h"
#include "Game.h"
#include "PlayerUnit.h"
#include "EnemyUnit.h"
#include <sstream>
#include <algorithm>
using namespace std;

// GetInstance
CBattleState* CBattleState::GetInstance( void )
{
	static CBattleState s_Instance;

	return &s_Instance;
}

CBattleState::CBattleState(void)
{
	m_nTarget = 0;
	m_nTurn = 0;
}

CBattleState::~CBattleState(void)
{
	for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		m_vBattleUnits[i]->Release();

}

void CBattleState::Activate(void)
{
	m_pFont = CGame::GetInstance()->GetFont();

	// TEMP ENEMIES/Player

	m_eCurrentPhase = BP_INIT;


}

void CBattleState::Sleep(void)
{

}

bool CBattleState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_UP ) == true )
		GetNextTarget();
	else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_DOWN ) == true )
		GetPreviousTarget();

	return true;
}

void CBattleState::Update(float fElapsedTime)
{
	switch (m_eCurrentPhase)
	{
	case CBattleState::BP_INIT:
		Initialize();
		break;
	case CBattleState::BP_BATTLE:
		break;
	case CBattleState::BP_END:
		break;
	default:
		break;
	}
}

void CBattleState::Render(void)
{


	CSGD_TextureManager*	pTM	= CSGD_TextureManager::GetInstance();
	CSGD_Direct3D*			pD3D = CSGD_Direct3D::GetInstance();


	//Temp drawing the UI
	RECT Overlay = { 0, 478, 800, 600 };
	pD3D->DrawHollowRect(Overlay, D3DCOLOR_XRGB( 0,0,0 ));

	Overlay.left = 400 - 64;
	Overlay.right = Overlay.left + 128;

	pD3D->DrawHollowRect(Overlay, D3DCOLOR_XRGB( 0,0,0 ));

	// Printing out variables
	std::wostringstream woss;


	m_pFont->Draw(_T("HP:"), 660, 500, 0.8f, D3DCOLOR_XRGB(0, 0, 255));
	m_pFont->Draw(_T("AP:"), 660, 520, 0.8f, D3DCOLOR_XRGB(0, 0, 255));

	m_pFont->Draw(_T("This is the Battle State"), 15, 15, 1.0f, D3DCOLOR_XRGB(0, 0, 255));



	for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
	{
		if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
		{
			woss << m_vBattleUnits[i]->GetHealth();
			m_pFont->Draw( woss.str().c_str(), 700, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[i]->GetAbilityPoints();
			m_pFont->Draw( woss.str().c_str(), 700, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
		}


		RECT Player = { long(m_vBattleUnits[i]->GetPosX()), long(m_vBattleUnits[i]->GetPosY()), long(m_vBattleUnits[i]->GetPosX()) + 20, long(m_vBattleUnits[i]->GetPosY()) + 20 };
		pD3D->DrawHollowRect(Player, D3DCOLOR_XRGB( 0,0,0 ));


	}


	m_pFont->Draw(_T("HP:"), 10, 500, 0.8f, D3DCOLOR_XRGB(0, 0, 255));
	m_pFont->Draw(_T("AP:"), 10, 520, 0.8f, D3DCOLOR_XRGB(0, 0, 255));

	woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
	woss << m_vBattleUnits[m_nTarget]->GetHealth();
	m_pFont->Draw( woss.str().c_str(), 50, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
	woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
	woss << m_vBattleUnits[m_nTarget]->GetAbilityPoints();
	m_pFont->Draw( woss.str().c_str(), 50, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
	woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
	woss << m_vBattleUnits[m_nTarget]->GetName().c_str();
	m_pFont->Draw( woss.str().c_str(), 50, 480, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );

	RECT temp = { long(m_vBattleUnits[m_nTarget]->GetPosX() + 5),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 10),  long(m_vBattleUnits[m_nTarget]->GetPosX() + 10),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 5) };
	pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,0 ));


}

bool SortSpeed(CUnits *l, CUnits *r)
{
	return l->GetSpeed() > r->GetSpeed();
}


void CBattleState::Initialize(void)
{
	m_vBattleUnits.push_back(CreateTempPlayer());

	m_vBattleUnits.push_back(CreateTempEnemy("Enemy 1", 100.0f, 100.0f, 12, 50, 20));
	m_vBattleUnits.push_back(CreateTempEnemy("Enemy 2", 200.0f, 200.0f, 5, 90, 15));
	m_vBattleUnits.push_back(CreateTempEnemy("Enemy 3", 100.0f, 300.0f, 9, 200, 150));


	sort(m_vBattleUnits.begin(), m_vBattleUnits.end(), SortSpeed); 

	GetNextTarget();




	m_eCurrentPhase = BP_BATTLE;
}

void CBattleState::Battle(void)
{

}

void CBattleState::End(void)
{

}

CPlayerUnit* CBattleState::CreateTempPlayer(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	temp->SetMaxHealth(80);
	temp->SetMaxAP(50);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(1);
	temp->SetTurn();
	temp->SetType(OBJ_PLAYER_UNIT);
	return temp;
}

CEnemyUnit* CBattleState::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp)
{
	CEnemyUnit* temp = new CEnemyUnit;
	temp->SetMaxHealth(hp);
	temp->SetMaxAP(mp);
	temp->SetPosX(X);
	temp->SetPosY(Y);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(speed);
	temp->SetTurn();
	temp->SetName(input);

	return temp;
}

void CBattleState::GetNextTarget(void)
{
	if(m_vBattleUnits.size() <= 1)
		return;

	do 
	{
		m_nTarget++;
		if(unsigned int(m_nTarget) >= m_vBattleUnits.size())
			m_nTarget = 0;
	}
	while(m_vBattleUnits[m_nTarget]->GetType() == OBJ_PLAYER_UNIT);

}

void CBattleState::GetPreviousTarget(void)
{
	if(m_vBattleUnits.size() <= 1)
		return;

	do 
	{
		m_nTarget--;
		if(m_nTarget < 0)
			m_nTarget = m_vBattleUnits.size() - 1;
	}
	while(m_vBattleUnits[m_nTarget]->GetType() == OBJ_PLAYER_UNIT);

}




