#pragma once
#include "../../Library9/Shader.h"

//------------------------------------------------------------------------/
//オブジェクトの色を決める
//ライトの方向、光の強さ、距離からオブジェクトの色を決定
//------------------------------------------------------------------------/

//--------------------------------------------------
//ディフューズマップクラス
//--------------------------------------------------
class DiffuseMap
{
public:

	void	Create();		//生成処理

	//シェーダの設定処理------------------------
	void	SetShaderParam();
	void	BeginPass();
	void	EndPass();
	void	Begin();
	void	End();

	//取得処理-------------------
	void	GetWorldMatrix(D3DXMATRIX* mat);
	void	GetViewMatrix(D3DXMATRIX* mat);
	void	GetProjMatrix(D3DXMATRIX* mat);
	void	GetLightDir(D3DXVECTOR3& dir);
	void	GetLightColor(D3DXVECTOR3& color);


private:
	D3DXHANDLE		worldHandle;		//ワールド行列ハンドル
	D3DXHANDLE		viewHandle;			//ビュー行列ハンドル
	D3DXHANDLE		projHandle;			//射影行列ハンドル
	D3DXHANDLE		lightDirHandle;		//ライト方向のハンドル
	D3DXHANDLE		lightColorHandle;	//ライトの色のハンドル
	D3DXHANDLE		texHandle;			//テクスチャハンドル
	D3DXHANDLE		technique;			//テクニック

	D3DXMATRIX			matWorld;		//ワールド行列
	D3DXMATRIX			matView;		//ビュー行列
	D3DXMATRIX			matProj;		//射影行列
	LPDIRECT3DTEXTURE9	diffuseTex;		//テクスチャ
	D3DXVECTOR3			lightDir;		//ライトの方向
	D3DXVECTOR3			lightColor;		//ライトの色

	Shader			shader;				//シェーダ
};