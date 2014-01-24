#include "BitmapFont.h"

#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\TinyXML\tinyxml.h"

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


void CBitmapFont::Initialize(std::string filePath)
{
	m_Font = FontParser(filePath);
	TCHAR temp[32];
	for(unsigned int i = 0; i <= m_Font.m_szFileName.size(); i++)
	{
		if(i < m_Font.m_szFileName.size())
			temp[i] = m_Font.m_szFileName[i];
		else
			temp[i] = '\0';
	}
	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(temp, D3DCOLOR_XRGB(0, 0, 0));

	m_nMaxCharWidth = 0;
	m_nMaxCharHeight = 0;

	for (int i = 0; i < 256; i++)
	{
		if (m_nMaxCharWidth < m_Font.Chars[i].m_nWidth)
			m_nMaxCharWidth = m_Font.Chars[i].m_nWidth;

		if (m_nMaxCharHeight < m_Font.Chars[i].m_nHeight)
			m_nMaxCharHeight = m_Font.Chars[i].m_nHeight;
	}

}



void CBitmapFont::Shutdown()
{
	//CSGD_TextureManager::GetInstance()->UnloadTexture( m_nImageID );
	//m_nImageID = -1;
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

	std::string szFile = "assets/Fonts/";
	pFont = pRoot->FirstChildElement("pages");
	if (pFont != nullptr)
	{
		pFont = pFont->FirstChildElement("page");
		if(pFont != nullptr)
		{
			szFile += pFont->Attribute("file");
		}
	}

	set.m_szFileName = szFile;

	int count;
	pFont = pRoot->FirstChildElement("chars");
	if (pFont != nullptr)
	{
		pFont->Attribute("count", &count);
	}

	int charID;
	pFont = pFont->FirstChildElement("char");
	for (int i = 0; i < count; i++)
	{
		if (pFont != nullptr)
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
			pFont = pFont->NextSiblingElement("char");
		}
	}

	return set;
}

void CBitmapFont::Draw(const TCHAR* szOutput, int nX, int nY, float fScale, DWORD dwColor) const
{
	int nColStart = nX;

	for (int i = 0; szOutput[i]; i++)
	{
		TCHAR ch = szOutput[i];

		if (ch == _T('\n'))
		{
			nY += (int)(m_nMaxCharHeight * fScale);
			nX = nColStart;
			continue;
		}
		else if (ch == _T('\t'))
		{
			int diff = (int)((nX - nColStart) / (m_nMaxCharWidth * fScale));

			int tab = 4 - (diff % 4);

			nX += (int)(tab * m_nMaxCharWidth * fScale);
			continue;
		}
		else
		{
			RECT rChar = { };

			rChar.left = m_Font.Chars[szOutput[i]].m_nX;
			rChar.top = m_Font.Chars[szOutput[i]].m_nY;

			rChar.right = rChar.left + m_Font.Chars[szOutput[i]].m_nWidth;
			rChar.bottom = rChar.top + m_Font.Chars[szOutput[i]].m_nHeight;

			CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nX + (int)(m_Font.Chars[szOutput[i]].m_nXOffset * fScale), nY + (int)(m_Font.Chars[szOutput[i]].m_nYOffset * fScale), fScale, fScale, &rChar, 0.0f, 0.0f, 0.0f, dwColor);


			nX += (int)(m_Font.Chars[szOutput[i]].m_nXAdvance * fScale);
		}

	}
}