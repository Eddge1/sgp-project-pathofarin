#include "Particle.h"


CParticle::CParticle(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("COLLIDE", this);
}


CParticle::~CParticle(void)
{
}

void CParticle::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "COLLIDE" && GetCollided() == false)
	{
		SetCollided(true);
	}
}