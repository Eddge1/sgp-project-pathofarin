#include "RenderManager.h"
#include "ObjectManager.h"

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

		//Render Objects
		pOM->Render(i);
	};
}