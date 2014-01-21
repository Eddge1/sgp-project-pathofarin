#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Frame.h"

CAnimationSystem::CAnimationSystem(void)
{
	
}


CAnimationSystem::~CAnimationSystem(void)
{
}

void CAnimationSystem::LoadAnimations(std::string filePath)
{

}

void CAnimationSystem::Render(CAnimationTimeStamp &aTimeStamp, float fPosX, float fPosY, float fScale, DWORD dwColor)
{
	RECT rFrame = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetRenderRect();
	int nAnchorX = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetAnchorX();
	int nAnchorY = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetAnchorY();

	CSGD_TextureManager::GetInstance()->Draw(
		loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetImageID(), 
		fPosX - (nAnchorX * fScale),
		fPosY - (nAnchorY * fScale), 
		fScale, fScale, &rFrame, 
		0.0f, 0.0f, 0.0f, dwColor);
}