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


void CBitmapFont::Initialize(void)
{
	WIN32_FIND_DATA fileSearch;
	HANDLE hFile;
	WCHAR cDirectory[] = L"assets/Fonts/*.fnt";
	hFile = FindFirstFile(cDirectory,&fileSearch);

	do
	{
		char cFile[128] = "assets/Fonts/";
		for(int i = 0; i < 128; i++)
		{
			cFile[i + 13] = char(fileSearch.cFileName[i]);
			if(fileSearch.cFileName[i] == '\0')
				break;
		}
		std::string szTemp = FontParser(cFile);
		TCHAR temp[32];
		for(unsigned int i = 0; i <= m_mFonts[szTemp]->m_Font.m_szFileName.size(); i++)
		{
			if(i < m_mFonts[szTemp]->m_Font.m_szFileName.size())
				temp[i] = m_mFonts[szTemp]->m_Font.m_szFileName[i];
			else
				temp[i] = '\0';
		}
		m_mFonts[szTemp]->m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(temp, D3DCOLOR_XRGB(0, 0, 0));

		m_mFonts[szTemp]->m_nMaxCharWidth = 0;
		m_mFonts[szTemp]->m_nMaxCharHeight = 0;

		for (int i = 0; i < 256; i++)
		{
			if (m_mFonts[szTemp]->m_nMaxCharWidth < m_mFonts[szTemp]->m_Font.Chars[i].m_nWidth)
				m_mFonts[szTemp]->m_nMaxCharWidth = m_mFonts[szTemp]->m_Font.Chars[i].m_nWidth;

			if (m_mFonts[szTemp]->m_nMaxCharHeight < m_mFonts[szTemp]->m_Font.Chars[i].m_nHeight)
				m_mFonts[szTemp]->m_nMaxCharHeight = m_mFonts[szTemp]->m_Font.Chars[i].m_nHeight;
		}
	}while(FindNextFile(hFile, &fileSearch));

}



void CBitmapFont::Shutdown()
{
	//CSGD_TextureManager::GetInstance()->UnloadTexture( m_nImageID );
	//m_nImageID = -1;
	for(auto i = m_mFonts.begin(); i != m_mFonts.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_mFonts.clear();
}

std::string CBitmapFont::FontParser(char* filePath)
{
	CharSet set;

	TiXmlDocument doc;
	if (doc.LoadFile(filePath) == false)
		return "";

	TiXmlElement *pRoot = doc.RootElement();
	if (pRoot == nullptr)
		return "";

	TiXmlElement *pData = pRoot->FirstChildElement("info");
	std::string szFontName;
	szFontName = pData->Attribute("face");
	m_mFonts[szFontName] = new CBitmapFont();
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
	m_mFonts[szFontName]->m_Font = set;
	m_mFonts[szFontName]->m_Font.m_szFontName = szFontName;

	return szFontName;
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

CBitmapFont* CBitmapFont::GetFont(std::string szFont)
{
	if(szFont == "")
		return nullptr;

	for(auto i = m_mFonts.begin(); i != m_mFonts.end(); i++)
	{
		if(i->second->m_Font.m_szFontName == szFont)
			return i->second;
	}
	return nullptr;

}