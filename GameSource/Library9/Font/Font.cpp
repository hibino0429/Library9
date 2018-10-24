#include "Font.h"

Font::Font() : pFont(NULL)
{

}

Font::~Font()
{
	Destory();
}

//フォントの生成
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

//フォントの破棄
void	Font::Destory()
{
	if (pFont != NULL) { pFont->Release(); pFont = NULL; }
}

//フォントの描画
void	Font::Render(LPCWSTR string, Box2D box2D, D3DXCOLOR color)
{
	//表示範囲はRECT型
	RECT rc = {
		(LONG)box2D.x,
		(LONG)box2D.y,
		(LONG)box2D.x + (LONG)box2D.sizeX,
		(LONG)box2D.y + (LONG)box2D.sizeY
	};

	pFont->DrawTextW(
		NULL,
		string,		//描画テキスト
		-1,			//全て表示
		&rc,		//表示範囲
		DT_LEFT,	//左寄せ
		color		//色
	);
}
void	Font::Render(LPCSTR string, Box2D box2D, D3DXCOLOR color)
{
	//表示範囲はRECT型
	RECT rc = {
		(LONG)box2D.x,
		(LONG)box2D.y,
		(LONG)box2D.x + (LONG)box2D.sizeX,
		(LONG)box2D.y + (LONG)box2D.sizeY
	};

	pFont->DrawTextA(
		NULL,
		string,		//描画テキスト
		-1,			//全て表示
		&rc,		//表示範囲
		DT_LEFT,	//左寄せ
		color		//色
	);
}
