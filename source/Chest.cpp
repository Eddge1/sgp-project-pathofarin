#include "Chest.h"
#include "GamePlayState.h"
#include "AnimationSystem.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"



CChest::CChest(void)
{
	m_bOpened = false;
	m_szBroadCast = "";
	m_bCollided = false;
	CSGD_EventSystem::GetInstance()->RegisterClient("GIVE_ITEM", this);
	SetType(OBJ_CHEST);
	SetRender(true);
	SetActive(true);
	m_nSound = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/General/POA_Chest_Open.wav"));
}


CChest::~CChest(void)
{
}

void CChest::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "GIVE_ITEM")
	{
		if(m_szBroadCast != "" && m_bOpened == false && m_bCollided)
		{
			CSGD_EventSystem::GetInstance()->SendEventNow(m_szBroadCast.c_str(), &(m_vItems));
			m_bOpened = true;
		}
	}
}

void CChest::AddConsumableItem(CItem* input, int nAmount, float fChance)
{
	if(input == nullptr)
		return;
	if(m_vItems[input->GetName()].Item != nullptr)
	{
		m_vItems[input->GetName()].Owned += nAmount;
		if(m_vItems[input->GetName()].Owned > 9)
			m_vItems[input->GetName()].Owned = 9;
		m_vItems[input->GetName()].DropChance = fChance;
	}
	else
	{
		m_vItems[input->GetName()].Item = input;
		m_vItems[input->GetName()].Owned += nAmount;
		m_vItems[input->GetName()].DropChance = fChance;
	}
}

void CChest::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER)
	{
		if(m_bCollided == false)
		{
			m_bCollided = true;
			this->GetAnimInfo()->SetAnimation("Chest_Opening");
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSound);
		}
	}

}

RECT CChest::GetCollisionRect()
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

void CChest::Update(float fElapsedTime)

{
	CAnimationSystem::GetInstance()->Update(GetAnimInfo(), fElapsedTime);

}