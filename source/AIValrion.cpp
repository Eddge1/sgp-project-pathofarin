#include "AIValrion.h"


CAIValrion::CAIValrion(void)
{
	m_bPrepare = false;
	Cataclysm = false;
	once = true;
	m_nTurns = 0;
	m_nLifeDevoured = 0;
	m_nAttempts = 0;
	m_nRageCount = 0;
	m_nSincePrepare = 0;
}


CAIValrion::~CAIValrion(void)
{
}

void CAIValrion::Update(float fElapsedTime)
{
	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();


	if(m_nLifeDevoured >= 2 && once)
	{
		Cataclysm = true;
		once = false;
		m_nTurns = 3;
	}

	if(Cataclysm)
	{
		if(m_nTurns > 0)
		{
			wostringstream woss;
			woss << m_nTurns;
			woss << " Turn(s) until cataclysm:";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_nTurns--;
			m_pTarget = nullptr;
			m_bPrepare = false;
			GetOwner()->EndTurn();
			return;
		}
		else if(m_nTurns <= 1)
		{
			wostringstream woss;
			woss << "BEHOLD, THE CATACLYSM!";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
			{
				if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
				{
					m_pTarget = m_vBattleUnits[i];
					break;
				}
			}
			m_pTarget->ModifyHealth(9999999, false);
			m_pTarget = nullptr;
			m_bPrepare = false;
			GetOwner()->EndTurn();
			return;

		}
	}

	if(m_bPrepare)
	{
		if(GetOwner()->GetHealth() <= GetOwner()->GetMaxHealth() * 0.80f && m_nAttempts == 0)
		{
			for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
			{
				if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
				{
					m_pTarget = m_vBattleUnits[i];
					break;
				}
			}

			if(m_pTarget != nullptr)
			{
				wostringstream woss;
				woss << "Devoured";
				CBattleState::GetInstance()->AddFloatingText(m_pTarget->GetPosX(), m_pTarget->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget->ModifyHealth(m_pTarget->GetMaxHealth(), false);
				GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3, false);
				m_nLifeDevoured++;
				m_nAttempts++;
				m_pTarget = nullptr;
				m_bPrepare = false;
				m_nSincePrepare = 0;
				GetOwner()->EndTurn();
				return;
			}
			else
			{
				m_nAttempts++;
				m_nRageCount++;
				wostringstream woss;
				woss << "Raged";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget = nullptr;
				m_bPrepare = false;
				m_nSincePrepare = 0;
				GetOwner()->EndTurn();
				return;
			}
		}
		else if(GetOwner()->GetHealth() <= GetOwner()->GetMaxHealth() * 0.40f && m_nAttempts == 1)
		{
			for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
			{
				if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
				{
					m_pTarget = m_vBattleUnits[i];
					break;
				}
			}

			if(m_pTarget != nullptr)
			{
				wostringstream woss;
				woss << "Devoured";
				CBattleState::GetInstance()->AddFloatingText(m_pTarget->GetPosX(), m_pTarget->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget->ModifyHealth(m_pTarget->GetMaxHealth(), false);
				GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3, false);
				m_nLifeDevoured++;
				m_nAttempts++;
				m_pTarget = nullptr;
				m_bPrepare = false;
				m_nSincePrepare = 0;
				GetOwner()->EndTurn();
				return;
			}
			else
			{
				m_nAttempts++;
				m_nRageCount++;
				wostringstream woss;
				woss << "Raged";
				CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
				m_pTarget = nullptr;
				m_bPrepare = false;
				m_nSincePrepare = 0;
				GetOwner()->EndTurn();
				return;
			}
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
			m_pTarget->ModifyHealth(GetOwner()->GetAttack() * 4 * (m_nRageCount + 1), false);
			wostringstream woss;
			woss << "Power Attack";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			m_bPrepare = false;
			m_nSincePrepare = 0;
			GetOwner()->EndTurn();
			return;


		}
	}
	else
	{
		if(rand()%100 + 1 > 75)
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			m_nSincePrepare = 0;
			GetOwner()->EndTurn();
		}
		else if(m_nSincePrepare >= 2)
		{
			m_bPrepare = true;
			wostringstream woss;
			woss << "Prepare";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			m_nSincePrepare = 0;
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
			m_pTarget->ModifyHealth(GetOwner()->GetAttack() * 2 * (m_nRageCount + 1), false);
			wostringstream woss;
			woss << "Fear me!";
			CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
			m_pTarget = nullptr;
			m_bPrepare = false;
			m_nSincePrepare++;
			GetOwner()->EndTurn();
		}

	}

}

void CAIValrion::Render(void)
{

}