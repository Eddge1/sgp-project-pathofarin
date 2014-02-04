#include "AIController.h"


CAIController::CAIController(void)
{
	m_pMiniGame = nullptr;
}


CAIController::~CAIController(void)
{
	delete m_pMiniGame;
}

void CAIController::Update(float fElaspedTime)
{
	m_pMiniGame->SetOwner(m_pOwner);
	m_pMiniGame->Update(fElaspedTime);
	m_pOwner->EndTurn();

}

void CAIController::Render(void)
{

}