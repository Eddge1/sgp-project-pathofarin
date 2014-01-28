#include "PlayerUnit.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "BattleState.h"
#include "Player.h"

CPlayerUnit::CPlayerUnit(void)
{
	SetType(OBJ_PLAYER_UNIT);
	m_bInSubMenu = false;
	m_bSkillSelected = false;
	m_bCasting = false;
	m_nMenuSelect = 0;
	m_nSkillSelect = 0;
	m_pPlayer = nullptr;
}

CPlayerUnit::~CPlayerUnit(void)
{
	for(unsigned int i =0; i < m_vCommands.size(); i++)
	{
		delete m_vCommands[i];
		m_vCommands[i] = nullptr;
	}
	m_vCommands.clear();
	SetOwner(nullptr);
}

void CPlayerUnit::HandleEvent( const CEvent* pEvent )
{

}

CCommands* CPlayerUnit::GetSkill(int nID)
{
	if(nID >= (int)m_vCommands.size())
		return nullptr;

	return m_vCommands[nID];
}

void CPlayerUnit::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(GetTurn() )
	{
		if(m_bCasting == false)
		{
			if(m_bSkillSelected == false)
			{
				if(m_bInSubMenu)
				{
					if(pDI->KeyPressed(DIK_W))
					{
						m_nSkillSelect--;
						if(m_nSkillSelect < 0)
							m_nSkillSelect = (int)m_vCommands[m_nMenuSelect]->GetCommands()->size() - 1;
					}
					else if(pDI->KeyPressed(DIK_S))
					{
						m_nSkillSelect++;
						if(m_nSkillSelect >= (int)m_vCommands[m_nMenuSelect]->GetCommands()->size())
							m_nSkillSelect = 0;
					}
				}
				else
				{
					if(pDI->KeyPressed(DIK_W))
					{
						m_nMenuSelect--;
						if(m_nMenuSelect < 0)
							m_nMenuSelect = (int)m_vCommands.size() - 1;
					}
					else if(pDI->KeyPressed(DIK_S))
					{
						m_nMenuSelect++;
						if(m_nMenuSelect >= (int)m_vCommands.size())
							m_nMenuSelect = 0;
					}
				}
				if(pDI->KeyPressed(DIK_RETURN))
				{
					if(m_bInSubMenu)
						m_bSkillSelected = true;
					else
					{
						if(m_vCommands[m_nMenuSelect]->GetIsGame())
							m_bSkillSelected = true;
						else
							m_bInSubMenu = true;
					}
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
				{
					if(m_bInSubMenu == true)
						m_bInSubMenu = false;
				}
			}
			else
			{
				if(pDI->KeyPressed(DIK_RETURN))
				{
					m_bCasting = true;
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
					m_bSkillSelected = false;
			}
		}
		else
		{
			if(m_bInSubMenu)
			{

			}
			else
			{
				m_vCommands[m_nMenuSelect]->GetMiniGame()->SetOwner(this);
				m_vCommands[m_nMenuSelect]->GetMiniGame()->Update(fElapsedTime);
				m_vCommands[m_nMenuSelect]->GetMiniGame()->Render();
			}

		}
	}
}

void CPlayerUnit::EndTurn()
{
	if(m_bInSubMenu)
	{


	}
	else
	{
		m_vCommands[m_nMenuSelect]->GetMiniGame()->SetOwner(nullptr);
		m_vCommands[m_nMenuSelect]->GetMiniGame()->ResetSkill();
	}

	SetTurn(false);
	m_bSkillSelected = false;
	m_bInSubMenu = false;
	m_bCasting = false;
}

void CPlayerUnit::SetOwner(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

