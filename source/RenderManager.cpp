#include "RenderManager.h"
#include "ObjectManager.h"
#include "World.h"
#include "GamePlayState.h"

CRenderManager::CRenderManager(void)
{
}


CRenderManager::~CRenderManager(void)
{
}


void CRenderManager::Render()
{
	CObjectManager* pOM = CObjectManager::GetInstance();
	for(int i = 0; i < 10; i++)
	{
		//Render Ground
		CGamePlayState::GetInstance()->GetWorld()->Render(i);


		//Render Objects
		pOM->Render(i);
	};
}