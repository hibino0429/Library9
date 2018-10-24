#pragma once
#include "../../Library9/Shader.h"
#include "../../Library9/Function.h"


//----------------------------------
//Z値テクスチャクラス
//----------------------------------
class ZTexture
{
public:
	ZTexture();
	virtual ~ZTexture();


public:
	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	GetShader(Shader* shader);	//シェーダの取得

	void	SetViewMatrix(D3DXMATRIX* mat);	//ビュー行列の設定
	void	SetProjMatrix(D3DXMATRIX* mat);	//射影行列の設定
	void	SetWorldMatrix(D3DXMATRIX* mat);//ワールド行列の設定

	LPDIRECT3DTEXTURE9*	GetTexture();		//テクスチャ情報の取得
	LPDIRECT3DSURFACE9*	GetZSurface();		//Z値テクスチャサーフェイスの取得


	void	Begin();	//描画の開始
	void	End();		//描画の終了
	void	BeginPass();	//パスの開始の宣言
	void	EndPass();		//パスの終了の宣言

	void	SetEffectParam();	//パラメータの情報をエフェクトにセット
	

private:
	LPDIRECT3DTEXTURE9	zTexture;			//Z値テクスチャ
	LPDIRECT3DSURFACE9	zSurface;			//Z値テクスチャサーフェイス
	LPDIRECT3DSURFACE9	depthSurface;		//深度バッファサーフェイス
	LPDIRECT3DSURFACE9	deviceZSurface;		//デバイスのサーフェイス
	LPDIRECT3DSURFACE9	deviceDepthSurface;	//デバイスの深度サーフェイス

	Shader				zTexShader;		//Z値を算出するシェーダ

private:
	D3DXMATRIX			matWorld;	//ワールド変換行列
	D3DXMATRIX			matView;	//ビュー変換行列
	D3DXMATRIX			matProj;	//射影変換行列
	D3DXHANDLE			worldHandle;	//ワールド行列のハンドル
	D3DXHANDLE			viewHandle;		//ビュー行列のハンドル
	D3DXHANDLE			projHandle;		//射影行列のハンドル
	D3DXHANDLE			techniqueHandle;//テクニックのハンドル
};