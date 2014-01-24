#include "Skills.h"


CSkills::CSkills(void)
{
	SetType(OBJ_SKILL);
	SetTarget(nullptr);
}


CSkills::~CSkills(void)
{
	SetTarget(nullptr);
}

void CSkills::SetTarget(CObjects* pTarget)
{
	if(m_pTarget != nullptr)
		m_pTarget->Release();

	m_pTarget = pTarget;

	if(m_pTarget != nullptr)
		m_pTarget->AddRef();
}

void CSkills::Update(float fElapsedTime)
{



	CEntity::Update(fElapsedTime);
}

void CSkills::HandleEvent( const CEvent* pEvent )
{


}