#include "Entity.h"


CEntity::CEntity(void)
{
	SetType(OBJ_ENTITY);
}


CEntity::~CEntity(void)
{

}

void CEntity::Update(float fElapsedTime)
{
	SetPosX(GetPosX() + m_fVelX * fElapsedTime);
	SetPosY(GetPosY() + m_fVelY * fElapsedTime);
}