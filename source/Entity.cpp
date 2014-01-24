#include "Entity.h"
#include "AnimationSystem.h"

CEntity::CEntity(void)
{
	SetType(OBJ_ENTITY);
	SetVelX(0);
	SetVelY(0);
}


CEntity::~CEntity(void)
{

}

void CEntity::Update(float fElapsedTime)
{
	SetPosX(GetPosX() + m_fVelX * fElapsedTime);
	SetPosY(GetPosY() + m_fVelY * fElapsedTime);

	CAnimationSystem::GetInstance()->Update(GetAnimInfo(), fElapsedTime);
}

void CEntity::HandleEvent( const CEvent* pEvent )
{

}