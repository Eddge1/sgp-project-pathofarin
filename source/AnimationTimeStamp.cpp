#include "AnimationTimeStamp.h"
#include "AnimationSystem.h"
CAnimationTimeStamp::CAnimationTimeStamp(void)
{
	m_nCurrFrame = 0;
	m_fTimeOnStamp = 0;
	m_bIsPaused = false;
}


CAnimationTimeStamp::~CAnimationTimeStamp(void)
{
}

void CAnimationTimeStamp::AdvanceCurrentFrame()
{
	if (m_bIsPaused == false)
	{
		m_nCurrFrame++;

		if (m_nCurrFrame >= (int)CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->GetSize())
		{
			if (CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->isLooping())
				m_nCurrFrame = 0;
			else
				m_nCurrFrame = CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->GetSize() - 1;
		}
	}
}

void CAnimationTimeStamp::SetAnimation(std::string szAnimName)
{
	if (m_szCurrentAnimation != szAnimName)
	{
		m_nCurrFrame = 0;
		m_szCurrentAnimation = szAnimName; 
		m_fTimeOnStamp = 0.0f;
	}
}