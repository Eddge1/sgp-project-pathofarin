#include "Animation.h"
#include "Frame.h"

CAnimation::CAnimation(void)
{
	int m_nImageID = -1;
	bool m_bLooping = false;
}


CAnimation::~CAnimation(void)
{
	for (unsigned int i = 0; i < m_vFrames.size(); i++)
	{
		delete m_vFrames[i];
		m_vFrames[i] = nullptr;
	}
	m_vFrames.clear();
}
