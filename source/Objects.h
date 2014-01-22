#pragma once
enum ObjectType {OBJ_UNDEFINE, OBJ_ENTITY, OBJ_PLAYER, OBJ_NPC, OBJ_SKILL, OBJ_PLAYER_UNIT, OBJ_ENEMY_UNIT, OBJECT_UNIT};





class CObjects
{

	ObjectType m_eType; 
	float m_fPosX;
	float m_fPosY;
	bool m_bActive;
	bool m_bRender;
	unsigned int m_unRef;

public:



	CObjects(void);
	virtual ~CObjects(void);

	float GetPosX	(void)									{return m_fPosX;}
	float GetPosY	(void)									{return m_fPosY;}

	void SetPosX	(float fPos)							{m_fPosX = fPos;}
	void SetPosY	(float fPos)							{m_fPosY = fPos;}

	virtual ObjectType GetType(void)	final				{return m_eType;}
	virtual void AddRef()				final				{m_unRef++;}


	virtual void Release() final;
	void SetType(ObjectType eType)							{m_eType = eType;}

	virtual void Update(float fElapsedTime);
	virtual void HandleCollision(CObjects* col);



};

