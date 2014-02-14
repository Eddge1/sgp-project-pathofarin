#include "Buff.h"

CBuff::CBuff(void)
{
	CSGD_EventSystem::GetInstance()->RegisterClient("HEAL", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("MEDITATE", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("COLLIDE", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("FLARE", this);
	CSGD_EventSystem::GetInstance()->RegisterClient("COMPLETE", this);
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
	if(pEvent->GetEventID() =="MEDITATE" && GetMini() != nullptr )
	{
		GetMini()->DoAttack();
		SetMasterGame(nullptr);
		SetCollided(true);
	}
	if(pEvent->GetEventID() =="COLLIDE" && GetMini() != nullptr && pEvent->GetSender() == this->GetAnimInfo())
	{
		SetReady(true);
		GetMini()->DoAttack();
		SetMasterGame(nullptr);
	}
	if (pEvent->GetEventID() == "FLARE" && GetMini() != nullptr && pEvent->GetSender() == this->GetAnimInfo())
	{
		SetReady(true);
	}
	if(pEvent->GetEventID() =="COMPLETE" && !GetCollided() && GetReady() && pEvent->GetSender() == this->GetAnimInfo())
	{
		SetCollided(true);
	}
}