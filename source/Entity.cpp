#include "Entity.h"
#include "AnimationSystem.h"
#include "GamePlayState.h"

CEntity::CEntity(void)
{
	SetType(OBJ_ENTITY);
	SetVelX(0);
	SetVelY(0);
	SetRender(true);
	SetActive(true);
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

RECT CEntity::GetCollisionRect()
{
	int nX = CGamePlayState::GetInstance()->GetWorldCamX();
	int nY = CGamePlayState::GetInstance()->GetWorldCamY();

	CAnimation* pTemp = CAnimationSystem::GetInstance()->GetAnimation(GetAnimInfo()->GetCurrentAnimation());
	CFrame* pFrame = pTemp->GetIndividualFrame(GetAnimInfo()->GetCurrentFrame());
	RECT rTemp = pFrame->GetCollisionRect();
	rTemp.left += long(GetPosX() - nX);
	rTemp.right += long(GetPosX() - nX);
	rTemp.top += long(GetPosY() - nY);
	rTemp.bottom += long(GetPosY() - nY);

	return rTemp;
}

RECT CEntity::GetCollisionRectNoCam()
{
	CAnimation* pTemp = CAnimationSystem::GetInstance()->GetAnimation(GetAnimInfo()->GetCurrentAnimation());
	CFrame* pFrame = pTemp->GetIndividualFrame(GetAnimInfo()->GetCurrentFrame());
	RECT rTemp = pFrame->GetCollisionRect();
	rTemp.left += long(GetPosX());
	rTemp.right += long(GetPosX());
	rTemp.top += long(GetPosY());
	rTemp.bottom += long(GetPosY());

	return rTemp;
}