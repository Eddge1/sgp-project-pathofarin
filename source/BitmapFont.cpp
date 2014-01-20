#include "BitmapFont.h"

#include "SGD Wrappers\CSGD_TextureManager.h"
#include "TinyXML\tinyxml.h"

CharDescriptor::CharDescriptor()
{
	m_nX = 0;
	m_nY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nXOffset = 0;
	m_nYOffset = 0;
	m_nXAdvance = 0;
	m_nPage = 0;
}


CBitmapFont::CBitmapFont(void)
{

}


CBitmapFont::~CBitmapFont(void)
{
}


void CBitmapFont::Initialize(int nID)
{
	m_nImageID = nID;
}

void CBitmapFont::Shutdown()
{

}

CharSet CBitmapFont::FontParser(std::string filePath)
{
	CharSet set;

	TiXmlDocument doc;
	if (doc.LoadFile(filePath.c_str()) == false)
		return set;

	TiXmlElement *pRoot = doc.RootElement();
	if (pRoot == nullptr)
		return set;

	

	TiXmlElement *pFont = pRoot->FirstChildElement("common");
	if (pFont != nullptr)
	{
		pFont->Attribute("lineHeight", &set.m_nLineHeight);
		pFont->Attribute("base", &set.m_nBase);
		pFont->Attribute("scaleW", &set.m_nWidth);
		pFont->Attribute("scaleH", &set.m_nHeight);
		pFont->Attribute("pages", &set.m_nPages);
	}

	int count;
	pFont = pRoot->FirstChildElement("chars");
	if (pFont != nullptr)
	{
		pFont->Attribute("count", &count);
	}

	int charID;
	pFont = pRoot->FirstChildElement("char");
	for (int i = 0; i < count; i++)
	{
		pFont->Attribute("id", &charID);
		pFont->Attribute("x", &set.Chars[charID].m_nX);
		pFont->Attribute("y", &set.Chars[charID].m_nY);
		pFont->Attribute("width", &set.Chars[charID].m_nWidth);
		pFont->Attribute("height", &set.Chars[charID].m_nHeight);
		pFont->Attribute("xoffset", &set.Chars[charID].m_nXOffset);
		pFont->Attribute("yoffset", &set.Chars[charID].m_nYOffset);
		pFont->Attribute("xadvance", &set.Chars[charID].m_nXAdvance);
		pFont->Attribute("page", &set.Chars[charID].m_nPage);
	}

	return set;
}