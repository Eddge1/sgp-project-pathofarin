#include "ObjectManager.h"
#include "Objects.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "AnimationSystem.h"
#include "AnimationTimeStamp.h"
#include "Animation.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
CObjectManager::CObjectManager(void)
{
	m_bIterating = false;
}

CObjectManager* CObjectManager::GetInstance()
{
	static CObjectManager s_Instance;
	return &s_Instance;
}

CObjectManager::~CObjectManager(void)
{
}

void CObjectManager::Update(float fElapsedTime)
{
	for(unsigned int i = 0; i < m_vObjects.size(); i++)
	{
		ObjectVector temp = m_vObjects[i];
		for(unsigned int j = 0; j < temp.size(); j++)
		{
			temp[j]->Update(fElapsedTime);
		}
	}
}

void CObjectManager::Render(unsigned int nLayer)
{
	if(nLayer > m_vObjects.size() - 1)
		return;

	int WorldCamX = CGamePlayState::GetInstance()->GetWorldCamX();
	int WorldCamY = CGamePlayState::GetInstance()->GetWorldCamY();
	int nImageID = -1;
	ObjectVector temp = m_vObjects[nLayer];
	CAnimation* pAnim; 

	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();

	for(unsigned int i = 0; i < temp.size(); i++)
	{
		pAnim = CAnimationSystem::GetInstance()->GetAnimation(temp[i]->GetAnimInfo()->GetCurrentAnimation());
		nImageID = pAnim->GetImageID();
		float PosX = temp[i]->GetPosX() - WorldCamX;
		float PosY = temp[i]->GetPosY() - WorldCamY;
		if (nImageID != -1)
		{
			CAnimationSystem::GetInstance()->Render(temp[i]->GetAnimInfo(), PosX, PosY, 2.0f, D3DCOLOR_XRGB(255, 255, 255));
			//pTM->Draw(nImageID, PosX, PosY, 2.0f, 2.0f, &(pAnim->GetIndividualFrame(temp[i]->GetAnimInfo()->GetCurrentFrame())->GetRenderRect()));
		}
	}

}
void CObjectManager::AddObject(CObjects* pObject, unsigned int unLayer)
{
	if(unLayer > m_vObjects.size())
		m_vObjects.resize(unLayer + 1);

	m_vObjects[unLayer].push_back( pObject );
	pObject->AddRef();
}
void CObjectManager::RemoveObject(CObjects* pObject)
{
	for(unsigned int i = 0; i < m_vObjects.size(); i++)
	{
		ObjectVector temp = m_vObjects[i];
		for(unsigned int j = 0; j < temp.size(); j++)
		{
			if(temp[j] == pObject)
			{
				temp[j]->Release();
				temp.erase(temp.begin() + j);
				return;
			}
		}
	}

}

void CObjectManager::RemoveAll()
{

	m_bIterating = true;

	for(unsigned int i = 0; i < m_vObjects.size(); i++)
	{
		ObjectVector temp = m_vObjects[i];
		for(int j = temp.size() - 1; j >= 0; j--)
		{
			temp[j]->Release();
			temp.erase(temp.begin() + j);
		}
	}

	m_vObjects.clear();

	m_bIterating = false;

}

void CObjectManager::HandleCollision(unsigned int unLayer1, unsigned int unLayer2)
{
	if(unLayer1 > m_vObjects.size() -1 || unLayer2 > m_vObjects.size() - 1)
		return;
	m_bIterating = true;

	ObjectVector Collision1 = m_vObjects[unLayer1];
	ObjectVector Collision2 = m_vObjects[unLayer2];

	for(unsigned int i = 0; i < Collision1.size(); i++)
	{
		for(unsigned int j = 0; j < Collision2.size(); j++)
		{
			/*Temp to show Collision works*/
			RECT rTemp1 = {long(Collision1[i]->GetPosX()), long(Collision1[i]->GetPosY()),long( Collision1[i]->GetPosX()+ 10), long(Collision1[i]->GetPosY() + 10)};
			RECT rTemp2 = {long(Collision2[j]->GetPosX()), long(Collision2[j]->GetPosY()),long( Collision2[j]->GetPosX()+ 10), long(Collision2[j]->GetPosY() + 10)};
			RECT rTempReturn = {};
			if(IntersectRect(&rTempReturn, &rTemp1, &rTemp2))
			{
				Collision1[i]->HandleCollision(Collision2[j]);
			}
			/*Temp to show Collision works*/
		}
	}


	m_bIterating = false;

}
