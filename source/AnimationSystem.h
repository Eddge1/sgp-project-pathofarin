#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <map>

class CAnimation;
class CAnimationTimeStamp;

class CAnimationSystem
{
	std::map<std::string, CAnimation> loadedAnimation;

public:
	CAnimationSystem(void);
	virtual ~CAnimationSystem(void);

	//Mutator: 
	void LoadAnimations(std::string filePath);

	void Render(CAnimationTimeStamp &aTimeStamp, float fPosX, float fPosY, float fScale, DWORD dwColor);

	void Update(CAnimationTimeStamp &aTimeStamp, float fElapsedTime);
};

