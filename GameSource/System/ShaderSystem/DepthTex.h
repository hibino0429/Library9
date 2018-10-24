#pragma once

#include "../../Library9/Light.h"
#include "../../Library9/Camera.h"
#include "../../Library9/Shader.h"


class Light;
class Camera;
//----------------------------------
//深度バッファテクスチャを作成する
//----------------------------------
class DepthTexture
{
public:
	DepthTexture();
	virtual ~DepthTexture();

	void	Create();

	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//パスを利用して描画
	void	Begin(UINT pass, DWORD flags);
	void	End();
	void	BeginPass();
	void	EndPass();

	void	SetEffectParam();


	void	GetLightInfo(Light* lightInfo);
	void	GetWorldMatrix(D3DXMATRIX* mat);
	void	GetLightViewMatrix(D3DXMATRIX* mat);
	void	GetLightProjMatrix(D3DXMATRIX* mat);
	void	SetCameraViewMatrix(D3DXMATRIX* mat);
	void	SetCameraProjMatrix(D3DXMATRIX* mat);

	void	GetCameraMatrix(Camera* camera);
	void	SetTexture(LPDIRECT3DTEXTURE9* tex);
	void	SetMaterialDiffuse(const D3DXVECTOR4& diffuse_);

private:

	D3DXMATRIX		world;
	D3DXMATRIX		cameraView;
	D3DXMATRIX		cameraProj;
	D3DXMATRIX		lightView;
	D3DXMATRIX		lightProj;

	D3DXVECTOR4		lightVec;
	D3DXVECTOR4		pos;
	D3DXVECTOR4		diffuse;

private:


	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 zSurface;
	LPDIRECT3DSURFACE9 stencilSurface;
	Shader			   shader;


	//エフェクトファイルで使用するデータ
	Light*				light;					//ライト

	D3DXHANDLE			worldHandle;			//ワールド行列
	D3DXHANDLE			cameraViewHandle;		//ビュー行列
	D3DXHANDLE			cameraProjHandle;		//射影行列
	D3DXHANDLE			lightViewHandle;		//ライトビュー行列
	D3DXHANDLE			lightProjHandle;		//ライト射影行列
	D3DXHANDLE			shadowMapTex;			//シャドウマップテクスチャハンドル
	D3DXHANDLE			diffuseHandle;			//マテリアル情報
	D3DXHANDLE			technique;
	
};

