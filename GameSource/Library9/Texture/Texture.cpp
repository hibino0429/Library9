#include "Texture.h"

//コンストラクタ
Texture::Texture() : sprite(nullptr),texture(nullptr),backBufSurface(nullptr),backDepthSurface(nullptr),
surface(nullptr)
{
}

//デストラクタ
Texture::~Texture()
{
	Destroy();
}


//------------------------------------------------------------------/
//public:公開し、提供するメソッド
//------------------------------------------------------------------/
//画像のロード
void	Texture::Load(LPCWSTR fileName)
{
	LibTexture::Create(fileName, &texture);		//画像の生成
	LibTexture::CreateSprite(&sprite);			//スプライトの生成
	LoadSurface(fileName, nullptr, nullptr);	//サーフェイスに画像を読み込ませる
}
void	Texture::Load(LPCSTR fileName)
{
	LibTexture::Create(fileName, &texture);
	LibTexture::CreateSprite(&sprite);
	LoadSurface(fileName, nullptr, nullptr);	
}

//画像の破棄
void	Texture::Destroy()
{
	if (sprite != nullptr) { sprite->Release(); sprite = nullptr; }
	if (texture != nullptr) { texture->Release(); texture = nullptr; }
	if (backBufSurface != nullptr) { backBufSurface->Release(); backBufSurface = nullptr; }
	if (backDepthSurface != nullptr) { backDepthSurface->Release(); backDepthSurface = nullptr; }
}

//画像の描画
void	Texture::Render(Box2D draw, Box2D src, D3DXCOLOR color)
{
	RECT sr = {
		(LONG)src.x,
		(LONG)src.y,
		(LONG)src.x + (LONG)src.sizeX,
		(LONG)src.y + (LONG)src.sizeY
	};

	D3DXVECTOR3	pos = D3DXVECTOR3(draw.x, draw.y, 0);
	D3DXVECTOR3 center = D3DXVECTOR3(draw.sizeX, draw.sizeY, 0);


	//srcの大きさをdrawの大きさにする src/draw で倍率を取得
	//D3DXVECTOR2	scale;
	//scale.x = (float)src.sizeX / draw.sizeX * 2.0f;
	//scale.y = (float)src.sizeY / draw.sizeY * 2.0f;
	//D3DXVECTOR2	rotCenter(0, 0);
	//D3DXVECTOR2	drawPos(0, 0);

	////画像の表示する範囲をスケールで調整する
	//D3DXMATRIX	mWorld;
	//D3DXMatrixTransformation2D(&mWorld, nullptr, 0.0f, &scale, &rotCenter, 0.0f, &drawPos);
	D3DXVECTOR2		scale;
	scale.x = (float)src.sizeX / draw.sizeX * 2.0f;
	scale.y = (float)src.sizeY / draw.sizeY * 2.0f;
	D3DXMATRIX	matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1);
	

	//画像ソースの範囲を第二引数で指定する
	//
	if (SUCCEEDED(sprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		if (FAILED(sprite->Draw(
			texture,
			&sr,
			&center,
			&pos,
			color		//色の乗算
		)))
		{
			MessageBox(NULL, TEXT("画像の描画に失敗しました"), TEXT("Render"), MB_OK);
			return;
		}
	}
	sprite->End();
}



//------------------------------------------------------------------------------------------/
//private:公開せず、提供しないメソッド
//------------------------------------------------------------------------------------------/

//------------------------------------------------------------------
//画像の情報を取得し、サーフェイスに情報を読み込む
//------------------------------------------------------------------
bool	Texture::LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect)
{
	//1:画像情報の取得
	GetImageInfo(fileName);
	//2:サーフェイスの作成
	CreatePlainSurface();
	//3:サーフェイスに画像を読み込む
	if (!LoadSurfaceFromFile(
		surface,
		NULL,
		drawRect,
		fileName,
		srcRect,
		D3DX_FILTER_NONE,
		0, NULL
	))
	{
		MessageBox(NULL, TEXT("サーフェイルの読み込み失敗"), TEXT("LoadSurface"), MB_OK);
		return false;
	}
	return true;

}
bool	Texture::LoadSurface(LPCSTR fileName, const RECT* drawRect, const RECT* srcRect)
{
	//1:画像情報の取得
	GetImageInfo(fileName);
	//2:サーフェイスの作成
	CreatePlainSurface();
	//3:サーフェイスに画像を読み込む
	if (!LoadSurfaceFromFile(
		surface,
		NULL,
		drawRect,
		fileName,
		srcRect,
		D3DX_FILTER_NONE,
		0, NULL
	))
	{
		MessageBox(NULL, TEXT("サーフェイルの読み込み失敗"), TEXT("LoadSurface"), MB_OK);
		return false;
	}
	return true;

}

//------------------------------------------------------------------
//サーフェイスに画像ファイルを読み込む
//------------------------------------------------------------------
bool	Texture::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, 
									const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, 
									DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
{
	if (FAILED(D3DXLoadSurfaceFromFileW(
		surface,
		palette,
		rect,
		srcFile,
		srcRect,
		filter,
		colorKey,
		srcInfo
	)))
	{
		MessageBox(NULL, TEXT("サーフェイスに画像を読み込みできませんでした"), TEXT("LoadSurfaceFromFile"), MB_OK);
		return false;
	}
	return true;
}
bool	Texture::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette,
	const RECT* rect, LPCSTR srcFile, const RECT* srcRect,
	DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
{
	if (FAILED(D3DXLoadSurfaceFromFileA(
		surface,
		palette,
		rect,
		srcFile,
		srcRect,
		filter,
		colorKey,
		srcInfo
	)))
	{
		MessageBox(NULL, TEXT("サーフェイスに画像を読み込みできませんでした"), TEXT("LoadSurfaceFromFile"), MB_OK);
		return false;
	}
	return true;
}

//------------------------------------------------------------------
//画像ファイルのサイズをフォーマットを取得
//------------------------------------------------------------------
bool	Texture::GetImageInfo(LPCWSTR fileName)
{
	if (FAILED(D3DXGetImageInfoFromFileW(
		fileName,
		&imageInfo
	)))
	{
		MessageBox(NULL, TEXT("画像の情報を受け取れませんでした"), TEXT("GetImageInfo"), MB_OK);
		return false;
	}
	return true;
}
bool	Texture::GetImageInfo(LPCSTR fileName)
{
	if (FAILED(D3DXGetImageInfoFromFileA(
		fileName,
		&imageInfo
	)))
	{
		MessageBox(NULL, TEXT("画像の情報を受け取れませんでした"), TEXT("GetImageInfo"), MB_OK);
		return false;
	}
	return true;
}

//------------------------------------------------------------------
//画像のサーフェイスの取得
//------------------------------------------------------------------
//画像のサーフェイスの取得
bool	Texture::CreatePlainSurface()
{
	if (!LibTexture::CreatePlainSurface(&imageInfo, &surface)) { return false; }
	return true;
}

//------------------------------------------------------------------
//画像の回転・拡大縮小
//------------------------------------------------------------------
//画像の回転
void	Texture::Rotation(float angle)
{
	D3DXMATRIX	mRot;

	D3DXMatrixRotationY(&mRot, D3DXToRadian(angle));

	sprite->SetTransform(&mRot);
}

//画像の拡大
void	Texture::Scale(D3DXVECTOR2 scale)
{
	D3DXMATRIX	mScale;

	D3DXMatrixScaling(&mScale, scale.x, scale.y, 0);

	sprite->SetTransform(&mScale);
}