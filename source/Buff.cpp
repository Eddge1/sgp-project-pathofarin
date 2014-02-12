#include "Buff.h"

CBuff::CBuff(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("HEAL", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("MEDITATE", this);
}

CBuff::~CBuff(void)
{
}
void CBuff::Update(float fElapsedTime)
{
	CEntity::Update(fElapsedTime);
}

void CBuff::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() =="HEAL" && GetMini() != nullptr)
	{
		GetMini()->DoAttack();
		SetMasterGame(nullptr);
		SetCollided(true);
	}
	if(pEvent->GetEventID() =="MEDITATE" && GetMini() != nullptr)
	{
		GetMini()->DoAttack();
		SetMasterGame(nullptr);
		SetCollided(true);
	}
}