#include "ObjectManager.h"
#include "Objects.h"
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

void CObjectManager::Render(int nLayer)
{
	if(nLayer > m_vObjects.size())
		return;

	ObjectVector temp = m_vObjects[nLayer];
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	for(unsigned int i = 0; i < temp.size(); i++)
	{
		RECT rTemp = {long(temp[i]->GetPosX()), long(temp[i]->GetPosY()), long(temp[i]->GetPosX() + 10), long(temp[i]->GetPosY() + 10)};
		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));
	}
}
void CObjectManager::AddObject(CObjects* pObject, unsigned int unLayer)
{
	if(unLayer > m_vObjects.size())
		m_vObjects.resize(unLayer + 1);

	m_vObjects[unLayer].push_back( pObject );

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
				temp.erase(temp.begin() + j);
		}
	}

	m_vObjects.clear();

	m_bIterating = false;

}