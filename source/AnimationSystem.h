#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <map>

class CAnimation;
class CAnimationTimeStamp;

class CAnimationSystem
{
	std::map<std::string, CAnimation> loadedAnimation;

	// Static pointer to the singleton object
	static CAnimationSystem* s_pInstance;

public:
	CAnimationSystem(void);
	virtual ~CAnimationSystem(void);

	// Singleton accessors:
	static CAnimationSystem* GetInstance( void );
	static void DeleteInstance( void );

	//Mutator: 
	void LoadAnimations(std::string filePath);

	void Render(CAnimationTimeStamp &aTimeStamp, float fPosX, float fPosY, float fScale, DWORD dwColor);

	void Update(CAnimationTimeStamp &aTimeStamp, float fElapsedTime);
};

