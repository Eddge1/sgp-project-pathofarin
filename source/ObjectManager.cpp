#include "ObjectManager.h"
#include "Objects.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

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


	ObjectVector temp = m_vObjects[nLayer];
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	for(unsigned int i = 0; i < temp.size(); i++)
	{
		float PosX = temp[i]->GetPosX() - WorldCamX;
		float PosY = temp[i]->GetPosY() - WorldCamY;
		RECT rTemp = {long(PosX), long(PosY), long(PosX + 10), long(PosY + 10)};
		pD3D->DrawRect(rTemp, D3DCOLOR_XRGB(0,0,0));
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
				return;

			}
			/*Temp to show Collision works*/
		}
	}


	m_bIterating = false;

}
