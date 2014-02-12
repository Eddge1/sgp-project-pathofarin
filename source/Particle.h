#pragma once
#include "projectile.h"
class CParticle : public CProjectile
{
public:
	CParticle(void);
	virtual ~CParticle(void);
	virtual void Update(float fElapsedTime) {CEntity::Update(fElapsedTime);}
	virtual void HandleCollision(CObjects* col) {}
	virtual void HandleEvent( const CEvent* pEvent ) override;
};

