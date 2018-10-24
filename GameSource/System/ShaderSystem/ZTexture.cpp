#include "ZTexture.h"



//コンストラクタ
ZTexture::ZTexture() : zTexture(nullptr), zSurface(nullptr), depthSurface(nullptr),
deviceZSurface(nullptr), deviceDepthSurface(nullptr)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	worldHandle = nullptr;
	viewHandle = nullptr;
	projHandle = nullptr;
	techniqueHandle = nullptr;
}

//デストラクタ
ZTexture::~ZTexture()
{
	SAFE_RELEASE(zTexture);
	SAFE_RELEASE(zSurface);
	SAFE_RELEASE(depthSurface);
	SAFE_RELEASE(deviceZSurface);
	SAFE_RELEASE(deviceDepthSurface);
}



//初期化処理
void	ZTexture::Initialize()
{
	//エフェクトファイルを読み込む
	if (!zTexShader.Load("./data/Shader/zTexCreator.fx"))
	{
		MessageBoxA(NULL, "読み込み失敗", "zTexShader.Load", MB_OK);
		return;
	}
	
	//エフェクトハンドルの取得
	worldHandle = zTexShader.GetParameterName("matWorld");
	viewHandle = zTexShader.GetParameterName("matView");
	projHandle = zTexShader.GetParameterName("matProj");
	techniqueHandle = zTexShader.GetParameterName("ZValueShader");

	//Z値テクスチャの生成
	UINT width = 1024, height = 1024;
	LibDGD::CreateTexture(width, height, &zTexture);
	//Z値テクスチャのサーフェイスの取得
	//LibDGD::GetSurfaceLevel(0,&zTexture, &zSurface);
	zTexture->GetSurfaceLevel(0, &zSurface);

	//描画デバイスに定義されているバッファの能力を取得
	LPDIRECT3DSURFACE9	pSurface;
	LibDGD::GetDepthStencilSurface(&pSurface);
	D3DSURFACE_DESC surfDesc;
	pSurface->GetDesc(&surfDesc);
	pSurface->Release();

	//独自深度バッファを作成
	//LibDGD::CreateDepthStencilSurface(width, height, &depthSurface);
	LibDGD::CreateDepthStencilSurface(width, height,
		surfDesc.Format, surfDesc.MultiSampleType, surfDesc.MultiSampleQuality,
		&depthSurface);

}

//解放処理
void	ZTexture::Finalize()
{

}

//更新処理
void	ZTexture::UpDate()
{

}

//描画処理
void	ZTexture::Render()
{

}


//ビュー行列の設定
void	ZTexture::SetViewMatrix(D3DXMATRIX* mat)
{
	matView = *mat;
}

//射影行列の設定
void	ZTexture::SetProjMatrix(D3DXMATRIX* mat)
{
	matProj = *mat;
}

//ワールド行列の設定
void	ZTexture::SetWorldMatrix(D3DXMATRIX* mat)
{
	matWorld = *mat;
}

//テクスチャの情報の取得
LPDIRECT3DTEXTURE9* ZTexture::GetTexture()
{
	return &zTexture;
}

LPDIRECT3DSURFACE9*	ZTexture::GetZSurface()
{	
	return &zSurface;
}


//描画の開始
void	ZTexture::Begin()
{
	//デバイスのバッファを一時保存
	LibDGD::GetRenderTarget(0, &deviceZSurface);
	LibDGD::GetDepthStencilSurface(&deviceDepthSurface);

	//デバイスにZ値テクスチャサーフェイスと深度バッファの設定
	LibDGD::SetRenderTarget(0, &zSurface);
	LibDGD::SetDepthStencilSurface(&depthSurface);

	//各サーフェイスの初期化
	LibDGD::ViewAndStencilClear();

	//シェーダのテクニックを設定
	techniqueHandle = zTexShader.GetParamTechnique("ZValueShader");
	zTexShader.SetTechnique(techniqueHandle);

	//シェーダの開始
	UINT tmp ;
	zTexShader.Begin(&tmp, 0);
}

//描画の終了
void	ZTexture::End()
{
	zTexShader.End();


	//デバイスをもとのサーフェイスに戻す
	LibDGD::SetRenderTarget(0, &deviceZSurface);
	LibDGD::SetDepthStencilSurface(&deviceDepthSurface);

	deviceZSurface = nullptr;
	deviceDepthSurface = nullptr;

	//固定機能に戻す
	//LibDGD::SetVertexShader(nullptr);
	//LibDGD::SetPixelShader(nullptr);
}

//パスの開始の宣言
void	ZTexture::BeginPass()
{
	zTexShader.BeginPass(0);	//Z値計算は１パス
}

//パスの終了の宣言
void	ZTexture::EndPass()
{
	zTexShader.EndPass();
}

//パラメータの情報をエフェクトにセット
void	ZTexture::SetEffectParam()
{
	zTexShader.SetMatrix(worldHandle,&matWorld);
	zTexShader.SetMatrix(viewHandle, &matView);
	zTexShader.SetMatrix(projHandle, &matProj);
}


//シェーダの取得
void	ZTexture::GetShader(Shader* shader)
{
	zTexShader = *shader;
}