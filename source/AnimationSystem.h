#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <map>
#include "Animation.h"

class CAnimationTimeStamp;

class CAnimationSystem
{
	std::map<std::string, CAnimation*> loadedAnimation;

	// Static pointer to the singleton object
	static CAnimationSystem* s_pInstance;
	bool m_bEventThrown;
	
public:
	CAnimationSystem(void);
	virtual ~CAnimationSystem(void);

	// Singleton accessors:
	static CAnimationSystem* GetInstance( void );
	static void DeleteInstance( void );

	CAnimation* GetAnimation(std::string szName) { return loadedAnimation[szName]; }
	bool IsEventThrown() { return m_bEventThrown; }
	//Mutator: 
	void LoadAnimations(void);
	void EventIsThrown(bool bEventThrow) { m_bEventThrown = bEventThrow; }


	void Render(CAnimationTimeStamp* aTimeStamp, float fPosX, float fPosY, float fScaleX, float fScaleY, DWORD dwColor);
	void Update(CAnimationTimeStamp* aTimeStamp, float fElapsedTime);
};

