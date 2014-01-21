#include "Frame.h"


CFrame::CFrame(void)
{
	m_nAnchorX = 0;
	m_nAnchorY = 0;
	m_fDuration = 0;
	m_rRender.left = 0;
	m_rRender.top = 0;
	m_rRender.right = 0;
	m_rRender.bottom = 0;
	m_rCollision.left = 0;
	m_rCollision.top = 0;
	m_rCollision.right = 0;
	m_rCollision.bottom = 0;
}


CFrame::~CFrame(void)
{
}
