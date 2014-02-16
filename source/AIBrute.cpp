#include "AIBrute.h"


CAIBrute::CAIBrute(void)
{
	m_bPrepare = false;
	m_bRaged = false;
	m_nTurns = 0;
	m_pTarget = nullptr;
}


CAIBrute::~CAIBrute(void)
{
}

void CAIBrute::Update(float fElapsedTime)
{
	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();

	if(GetOwner()->GetHealth() < GetOwner()->GetMaxHealth() / 3)
		m_bRaged = true;
	else
		m_bRaged = false;

	if(m_bPrepare)
	{
		GetOwner()->GetAnimInfo()->Pause(false);
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_pTarget = m_vBattleUnits[i];
				break;
			}
		}
		if(m_bRaged)
		{
			wostringstream woss;
			woss << "Raged";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget->ModifyHealth(GetOwner()->GetAttack() * 5, false);
		}
		else
			m_pTarget->ModifyHealth(GetOwner()->GetAttack() * 3, false);

		m_pTarget = nullptr;
		m_bPrepare = false;
		GetOwner()->EndTurn();
	}
	else
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_pTarget = m_vBattleUnits[i];
				break;
			}
		}

		if(m_pTarget->GetHealth() - GetOwner()->GetAttack() <= 5)
		{
			if(m_bRaged)
			{
				wostringstream woss;
				woss << "Raged";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget->ModifyHealth(GetOwner()->GetAttack(), false);
				m_pTarget = nullptr;
				GetOwner()->EndTurn();
			}
			else
			{
				GetMinigame()->SetOwner(GetOwner());
				GetMinigame()->Update(fElapsedTime);
			}

			m_pTarget = nullptr;

		}
		else if(m_pTarget->GetHealth() - GetOwner()->GetAttack() * 3 <= 5)
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			GetOwner()->GetAnimInfo()->Pause(true);
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			GetOwner()->EndTurn();
		}
		else if( rand()%101 > 70 )
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			GetOwner()->GetAnimInfo()->Pause(true);
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			GetOwner()->EndTurn();
		}
		else
		{
			if(m_bRaged)
			{
				wostringstream woss;
				woss << "Raged";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget->ModifyHealth(int(GetOwner()->GetAttack() * 1.5f), false);
				m_pTarget = nullptr;
				GetOwner()->EndTurn();
			}
			else
			{
				GetMinigame()->SetOwner(GetOwner());
				GetMinigame()->Update(fElapsedTime);
				m_pTarget = nullptr;
			}
		}


	}
}

void CAIBrute::Render(void)
{

}
