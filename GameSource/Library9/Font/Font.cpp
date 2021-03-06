#include "Font.h"

Font::Font() : pFont(NULL)
{

}

Font::~Font()
{
	Destory();
}

//tHgΜΆ¬
bool	Font::Create(LPCWSTR fontName, float width, float height)
{
	if (!LibFont::Create(fontName, width, height, &pFont))
	{
		return false;
	}
	return true;
}
bool	Font::Create(LPCSTR fontName, float width, float height)
{
	if (!LibFont::Create(fontName, width, height, &pFont))
	{
		return false;
	}
	return true;
}

//tHgΜjό
void	Font::Destory()
{
	if (pFont != NULL) { pFont->Release(); pFont = NULL; }
}

//tHgΜ`ζ
void	Font::Render(LPCWSTR string, Box2D box2D, D3DXCOLOR color)
{
	//\¦ΝΝΝRECT^
	RECT rc = {
		(LONG)box2D.x,
		(LONG)box2D.y,
		(LONG)box2D.x + (LONG)box2D.sizeX,
		(LONG)box2D.y + (LONG)box2D.sizeY
	};

	pFont->DrawTextW(
		NULL,
		string,		//`ζeLXg
		-1,			//SΔ\¦
		&rc,		//\¦ΝΝ
		DT_LEFT,	//ΆρΉ
		color		//F
	);
}
void	Font::Render(LPCSTR string, Box2D box2D, D3DXCOLOR color)
{
	//\¦ΝΝΝRECT^
	RECT rc = {
		(LONG)box2D.x,
		(LONG)box2D.y,
		(LONG)box2D.x + (LONG)box2D.sizeX,
		(LONG)box2D.y + (LONG)box2D.sizeY
	};

	pFont->DrawTextA(
		NULL,
		string,		//`ζeLXg
		-1,			//SΔ\¦
		&rc,		//\¦ΝΝ
		DT_LEFT,	//ΆρΉ
		color		//F
	);
}
