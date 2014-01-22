#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Frame.h"
#include "..\TinyXML\tinyxml.h"


CAnimationSystem::CAnimationSystem(void)
{
	
}


CAnimationSystem::~CAnimationSystem(void)
{
}

void CAnimationSystem::LoadAnimations(std::string filePath)
{
	TiXmlDocument doc;

	if (doc.LoadFile(filePath.c_str()) == false)
		return;

	TiXmlElement* pRoot = doc.RootElement();
	if (pRoot == nullptr)
		return;

	std::string szTempName;

	TiXmlElement* pAnim = pRoot->FirstChildElement("Animation_Data");
	if (pAnim != nullptr)
	{
		pAnim = pAnim->FirstChildElement("Animation_Info");
		if (pAnim != nullptr)
		{
			szTempName = pAnim->Attribute("Name");
			loadedAnimation[szTempName].SetLooping(pAnim->Attribute("repeat"));
			
			pAnim = pAnim->FirstChildElement("Frame_Data");
			if (pAnim != nullptr)
			{
				pAnim = pAnim->FirstChildElement("Render");
				if (pAnim != nullptr)
				{
					RECT rTempRect = { };
					pAnim->Attribute("posX", (int*)rTempRect.left);
					pAnim->Attribute("posY", (int*)rTempRect.top);
					pAnim->Attribute("anchorX"); //Make sure to Finish this thing
					pAnim->Attribute("anchorY");
					pAnim->Attribute("Width", (int*)rTempRect.right);
					pAnim->Attribute("Height", (int*)rTempRect.bottom);
				}
			}
		}
	}

}

void CAnimationSystem::Render(CAnimationTimeStamp &aTimeStamp, float fPosX, float fPosY, float fScale, DWORD dwColor)
{
	RECT rFrame = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetRenderRect();
	int nAnchorX = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetAnchorX();
	int nAnchorY = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetAnchorY();

	CSGD_TextureManager::GetInstance()->Draw(
		loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetImageID(), 
		(int)(fPosX - (nAnchorX * fScale)),
		(int)(fPosY - (nAnchorY * fScale)), 
		fScale, fScale, &rFrame, 
		0.0f, 0.0f, 0.0f, dwColor);
}

void CAnimationSystem::Update(CAnimationTimeStamp &aTimeStamp, float fElapsedTime)
{
	//if elapsed time is greater than or equal to the duration of the frame, advance the animation by one frame
	float fDuration = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetDuration();

	if (fElapsedTime > fDuration)
		aTimeStamp.AdvanceCurrentFrame();
}