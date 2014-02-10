#include "Projectile.h"


CProjectile::CProjectile(void)
{
	m_pTarget = nullptr;
	m_pMaster = nullptr;
	m_bCollided = false;
}


CProjectile::~CProjectile(void)
{
	SetTarget(nullptr);
	m_pMaster = nullptr;
}
void CProjectile::Update(float fElapsedTime)
{
	SetVelX(0);
	SetVelY(0);
	if(m_pTarget != nullptr)
	{
		if(m_pTarget->GetPosX() < GetPosX())
			SetVelX(-300);
		else
			SetVelX(300);

		if(GetPosY() < m_pTarget->GetPosY() - 10 || GetPosY() > m_pTarget->GetPosY() + 10 )
		{
			if(m_pTarget->GetPosY() < GetPosY())
				SetVelY(-100);
			else
				SetVelY(100);
		}
	}

	CEntity::Update(fElapsedTime);
	if(m_pTarget != nullptr)
	{
		RECT rTemp = {};

		if(IntersectRect(&rTemp, &GetCollisionRect(), &(m_pTarget->GetCollisionRect())))
		{
			if(m_pMaster != nullptr)
			{	
				m_bCollided = true;
				m_pMaster->DoAttack();
			}
		}
	}
}

void CProjectile::SetTarget(CUnits* pUnit)
{
	if(m_pTarget != nullptr)
		m_pTarget->Release();
	m_pTarget = pUnit;
	if(m_pTarget != nullptr)
		m_pTarget->AddRef();
}