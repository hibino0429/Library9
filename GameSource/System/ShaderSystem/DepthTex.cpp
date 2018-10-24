#include "DepthTex.h"


//-----------------------------------------------------
//DepthTextureクラス
//-----------------------------------------------------

//コンストラクタ
DepthTexture::DepthTexture() : texture(nullptr),zSurface(nullptr),stencilSurface(nullptr)
{

}
DepthTexture::~DepthTexture()
{
	if (texture != nullptr) { texture->Release(); texture = nullptr; }
	if (zSurface != nullptr) { zSurface->Release(); zSurface = nullptr; }
	if (stencilSurface != nullptr) { stencilSurface->Release(); stencilSurface = nullptr; }
}


//生成処理
void	DepthTexture::Create()
{
	//深度バッファの幅と高さの計算
	UINT width, height;
	LPDIRECT3DSURFACE9 surface;
	D3DSURFACE_DESC surDesc;

	//深度バッファのサーフェイスを取得
	LibDGD::GetDepthStencilSurface(&surface);
	surface->GetDesc(&surDesc);		//サーフェイス情報の取得
	width = surDesc.Width;
	height = surDesc.Height;
	if (surface != nullptr) { surface->Release(); surface = nullptr; }

	//z値テクスチャを生成
	LibDGD::CreateTexture(width, height, &texture);

	//サーフェイスレベルの取得
	LibDGD::GetSurfaceLevel(0, &texture,&zSurface);

	//Z値レンダリング用
	//深度バッファの生成
	LibDGD::CreateDepthStencilSurface(
		width, height, &zSurface
	);

	LibDGD::CreateDepthStencilSurface(width, height, &stencilSurface);

}


//初期化処理
void	DepthTexture::Initialize()
{
	//シェーダの読み込む
	if (!shader.Load("./data/Shader/DepthShadow.fx"))
	{
		MessageBoxA(NULL, "シェーダのファイル読み込み失敗", "DepthShadow.fx", MB_OK);
		return;
	}

	//シェーダハンドルのセット
	worldHandle = shader.GetParameterName("matWorld");
	cameraViewHandle = shader.GetParameterName("cameraView");
	cameraProjHandle = shader.GetParameterName("cameraProj");
	lightViewHandle = shader.GetParameterName("lightView");
	lightProjHandle = shader.GetParameterName("lightProj");
	shadowMapTex = shader.GetParameterName("shadowTex");
	diffuseHandle = shader.GetParameterName("diffuse");
	technique = shader.GetParamTechnique("DepthShadowShader");

}

//解放処理
void	DepthTexture::Finalize()
{

}

//更新処理
void	DepthTexture::UpDate()
{

}

//描画処理
void	DepthTexture::Render()
{
	LPDIRECT3DSURFACE9 backSurface;	//深度バッファ
	LPDIRECT3DSURFACE9 zSurface;	//Zバッファ
	LibDGD::GetRenderTarget(0, &backSurface);
	LibDGD::GetRenderTarget(0, &zSurface);

	//エフェクトにデータを渡す
	D3DXMATRIX world;	//取得しておく
	
	D3DXMatrixIdentity(&world);
	world = world * cameraView * cameraProj;	//ワールドビュー射影行列
	
	D3DXMATRIX lightWV, lightWP;
	lightWV = light->PassWorldMatrix() * cameraView;
	lightWP = light->PassWorldMatrix() * cameraProj;

	worldHandle = shader.GetParameterName("matWorld");
	shader.SetMatrix(worldHandle, &world);

	cameraViewHandle = shader.GetParameterName("cameraView");
	shader.SetMatrix(cameraViewHandle, &cameraView);

	cameraProjHandle = shader.GetParameterName("cameraProj");
	shader.SetMatrix(cameraProjHandle, &cameraProj);

	lightViewHandle = shader.GetParameterName("lightView");
	shader.SetMatrix(lightViewHandle, &lightWV);

	lightProjHandle = shader.GetParameterName("lightProj");
	shader.SetMatrix(lightProjHandle, &lightWP);

	diffuseHandle = shader.GetParameterName("diffuse");
	shader.SetVector(diffuseHandle, &diffuse);

	//テクニックの設定
	shader.SetTechnique("DepthShadowShader");
}


//かめらのマトリックスを取得し、設定する
void	DepthTexture::GetCameraMatrix(Camera* camera)
{
	cameraView = camera->PassViewMatrix();
	cameraProj = camera->PassProjMatrix();
}

//----------------------------------------------
//取得処理
//----------------------------------------------


//描画対象オブジェクトのワールド変換行列の取得
void	DepthTexture::GetWorldMatrix(D3DXMATRIX* mat)
{
	world = *mat;
}

//ライトの情報を取得
void	DepthTexture::GetLightInfo(Light* lightInfo)
{
	light = lightInfo;
}
//ライトのビュー・射影行列のセット
void	DepthTexture::GetLightViewMatrix(D3DXMATRIX* mat)
{
	lightView = *mat;
}
void	DepthTexture::GetLightProjMatrix(D3DXMATRIX* mat)
{
	lightProj = *mat;
}
//カメラのビュー・射影行列のセット
void	DepthTexture::SetCameraViewMatrix(D3DXMATRIX* mat)
{
	cameraView = *mat;
}
void	DepthTexture::SetCameraProjMatrix(D3DXMATRIX* mat)
{
	cameraProj = *mat;
}


//テクスチャのセット
void	DepthTexture::SetTexture(LPDIRECT3DTEXTURE9* tex)
{
	texture = *tex;
}

//マテリアルカラーの設定
void	DepthTexture::SetMaterialDiffuse(const D3DXVECTOR4& diffuse_)
{
	diffuse = diffuse_;
}

//-----------------------------------------------
//エフェクト描画の開始
void	DepthTexture::Begin(UINT pass,DWORD flags)
{
	LibDGD::ViewAndStencilClear();

	//テクニックのセット
	shader.SetTechnique(technique);
	
	UINT Pass ;
	shader.Begin(&Pass, flags);

}

void	DepthTexture::End()
{
	shader.End();

	//LibDGD::SetVertexShader(nullptr);
	//LibDGD::SetPixelShader(nullptr);
}


void	DepthTexture::BeginPass()
{
	shader.BeginPass(0);	//パスは１つのみ
}

void	DepthTexture::EndPass()
{
	shader.EndPass();
}


//パラメータの情報をエフェクトにセット
void	DepthTexture::SetEffectParam()
{
	shader.SetMatrix(worldHandle, &world);
	shader.SetMatrix(cameraViewHandle, &cameraView);
	shader.SetMatrix(cameraProjHandle, &cameraProj);
	shader.SetMatrix(lightViewHandle, &lightView);
	shader.SetMatrix(lightProjHandle, &lightProj);
	shader.SetVector(diffuseHandle, &diffuse);
	shader.SetParamTexture(shadowMapTex, texture);
}