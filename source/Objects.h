#pragma once
#include "../SGD Wrappers/IListener.h"
#include <string>
#include "AnimationTimeStamp.h"

enum ObjectType {OBJ_UNDEFINE, OBJ_ENTITY, OBJ_PLAYER, OBJ_NPC, OBJ_SKILL, OBJ_PLAYER_UNIT, OBJ_ENEMY_UNIT, OBJECT_UNIT};
class CObjects : public IListener
{

	ObjectType m_eType; 
	float m_fPosX;
	float m_fPosY;
	bool m_bActive;
	bool m_bRender;
	unsigned int m_unRef;
	CAnimationTimeStamp* m_aAnimationTimeInfo;

public:

	CObjects(void);
	virtual ~CObjects(void);

	float GetPosX	(void)									{return m_fPosX;}
	float GetPosY	(void)									{return m_fPosY;}
	bool  GetRender (void)									{return m_bRender;}
	bool  GetActive (void)									{return m_bActive;}
	CAnimationTimeStamp* GetAnimInfo()						{return m_aAnimationTimeInfo;}
	void SetPosX	(float fPos)							{m_fPosX = fPos;}
	void SetPosY	(float fPos)							{m_fPosY = fPos;}
	void SetRender  (bool bRender)							{m_bRender = bRender;}
	void SetActive  (bool bActive)							{m_bActive = bActive;}

	virtual ObjectType GetType(void)	final				{return m_eType;}
	virtual void AddRef()				final				{m_unRef++;}

	virtual void Release() final;
	void SetType(ObjectType eType)							{m_eType = eType;}

	virtual void Update(float fElapsedTime);
	virtual void HandleCollision(CObjects* col);
	virtual void HandleEvent( const CEvent* pEvent ) override;

};

