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

void CAnimationSystem::Render(CAnimationTimeStamp &aTimeStamp, float fPosX, float fPosY)
{
	//Need ImageID
	//Need Position
	//Need RenderRect
	
	CSGD_TextureManager::GetInstance()->Draw(loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetImageID(), fPosX, fPosY, 1.0f, 1.0f, 
		&loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetRenderRect());
}