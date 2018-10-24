#pragma once
#include "../Function.h"


//----------------------------------------------------------------
//テクスチャクラス
//----------------------------------------------------------------
class Texture
{
public:

	Texture();
	~Texture();
	//提供するメソッド

	//読み込み処理
	//引数1:画像のファイルパス
	void	Load(LPCWSTR);
	void	Load(LPCSTR);

	//画像の破棄
	void	Destroy();

	//引数1:画像の位置・大きさ
	//引数2:ソースの画像の位置・大きさ
	//引数3:画像の色
	void	Render(Box2D, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));

private:
	//画像ファイルのサイズをフォーマットを取得
	bool	GetImageInfo(LPCWSTR fileName);
	bool	GetImageInfo(LPCSTR fileName);

	//サーフェイスに画像ファイルを読み込む
	bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
	bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);

	//サーフェイスに画像情報を読み込む
	bool	LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect);
	bool	LoadSurface(LPCSTR fileName, const RECT* drawRect, const RECT* srcRect);

	//サーフェイス処理
	bool	CreatePlainSurface();				//画像のサーフェイスを作成

	//画像の回転・拡大縮小
	void	Rotation(float angle);
	void	Scale(D3DXVECTOR2 scale);

private:

	LPD3DXSPRITE		sprite;				//スプライトの格納
	LPDIRECT3DTEXTURE9	texture;			//テクスチャの格納


	LPDIRECT3DSURFACE9	backBufSurface;		//レンダリングにセットされていたサーフェイス
	LPDIRECT3DSURFACE9	backDepthSurface;	//深度バッファサーフェイス


	LPDIRECT3DSURFACE9	surface;			//画像サーフェイス
	D3DXIMAGE_INFO		imageInfo;			//画像の情報


private:

	//一時格納
	D3DXVECTOR3			center;
	D3DXVECTOR3			position;
	D3DXCOLOR			color;
	RECT				rect;

	D3DXMATRIX			world;
};