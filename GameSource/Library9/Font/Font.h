#pragma once
#include "../Function.h"


//----------------------------------------------------------------------
//フォントクラス
//----------------------------------------------------------------------
class Font
{
public:

	Font();
	~Font();

public:
	//フォントの生成
	//引数1:フォント名
	//引数2:幅
	//引数3:高さ
	bool	Create(LPCWSTR, float, float);
	bool	Create(LPCSTR, float, float);
	//フォントの解放
	void	Destory();

	//フォントの描画
	//引数1:文字列
	//引数2:表示範囲
	//引数3:色
	void	Render(LPCWSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));
	void	Render(LPCSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));
private:
	LPD3DXFONT		pFont;	//フォントオブジェクト
};