#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Frame.h"
#include "..\TinyXML\tinyxml.h"

CAnimationSystem* CAnimationSystem::s_pInstance = nullptr;

// GetInstance
CAnimationSystem* CAnimationSystem::GetInstance( void ) // Remember these are static.
{
	// Allocate the static pointer if necessary
	if( s_pInstance == nullptr )
		s_pInstance = new CAnimationSystem;

	// Return the singleton
	return s_pInstance;
}

// DeleteInstance
void CAnimationSystem::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


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
	int nFrames;

	TiXmlElement* pAnim = pRoot->FirstChildElement("Animation_Data");
	if (pAnim != nullptr)
	{
		pAnim = pAnim->FirstChildElement("Animation_Info");
		if (pAnim != nullptr)
		{
			szTempName = pAnim->Attribute("Name");
			pAnim->Attribute("Frames", &nFrames);

			int nRepeatValue;
			pAnim->Attribute("repeat", &nRepeatValue);
			if (nRepeatValue == 0)
				loadedAnimation[szTempName].SetLooping(false);
			else
				loadedAnimation[szTempName].SetLooping(true);


			pAnim = pAnim->FirstChildElement("Frame_Data");
			if (pAnim != nullptr)
			{
				pAnim = pAnim->FirstChildElement("Render");

				for (int i = 0; i < nFrames; i++)
				{
					if (pAnim != nullptr)
					{
						RECT rTempRenderRect = { };
						int nAnchorX, nAnchorY;
						pAnim->Attribute("posX", (int*)rTempRenderRect.left);
						pAnim->Attribute("posY", (int*)rTempRenderRect.top);
						pAnim->Attribute("Width", (int*)rTempRenderRect.right);
						pAnim->Attribute("Height", (int*)rTempRenderRect.bottom);
						pAnim->Attribute("anchorX", &nAnchorX);
						pAnim->Attribute("anchorY", &nAnchorY);

						pAnim = pAnim->NextSiblingElement("ActiveCollision");
						RECT rTempCollisionRect = { };
						if (pAnim != nullptr)
						{
							
							pAnim->Attribute("posX", (int*)rTempCollisionRect.left);
							pAnim->Attribute("posY", (int*)rTempCollisionRect.top);
							pAnim->Attribute("Width", (int*)rTempCollisionRect.right);
							pAnim->Attribute("height", (int*)rTempCollisionRect.bottom);
						}
						CFrame temp;
						temp.SetRenderRect(rTempRenderRect);
						temp.SetAnchor(nAnchorX, nAnchorY);
						temp.SetCollisionRect(rTempCollisionRect);
						loadedAnimation[szTempName].GetFrames().push_back(temp);

						pAnim = pAnim->NextSiblingElement("Render");
					}
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
	float fDuration = loadedAnimation[aTimeStamp.GetCurrentAnimation()].GetFrames()[aTimeStamp.GetCurrentFrame()].GetDuration();

	if (fElapsedTime > fDuration)
		aTimeStamp.AdvanceCurrentFrame();
}