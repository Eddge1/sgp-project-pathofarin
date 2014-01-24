#include "AnimationTimeStamp.h"
#include "AnimationSystem.h"
CAnimationTimeStamp::CAnimationTimeStamp(void)
{
	m_nCurrFrame = 0;
	m_fTimeOnStamp = 0;
}


CAnimationTimeStamp::~CAnimationTimeStamp(void)
{
}

void CAnimationTimeStamp::AdvanceCurrentFrame()
{
	m_nCurrFrame++;

	if (m_nCurrFrame >= CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->GetSize())
	{
		if (CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->isLooping())
			m_nCurrFrame = 0;
		else
			m_nCurrFrame = CAnimationSystem::GetInstance()->GetAnimation(m_szCurrentAnimation)->GetSize() - 1;
	}
}