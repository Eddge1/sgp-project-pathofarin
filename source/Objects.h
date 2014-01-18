#pragma once
class CObjects
{
	float m_fPosX;
	float m_fPosY;

public:
	CObjects(void);
	virtual ~CObjects(void);
	
	float GetPosX	(void)			{return m_fPosX;}
	float GetPosY	(void)			{return m_fPosY;}

	void SetPosX	(float fPos)	{m_fPosX = fPos;}
	void SetPosY	(float fPos)	{m_fPosY = fPos;}

	void Update(float fElapsedTime);
};

