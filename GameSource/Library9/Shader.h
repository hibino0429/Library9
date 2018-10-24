#pragma once
#include "Function.h"


//------------------------------------------------------
//シェーダクラス
//------------------------------------------------------
class Shader
{
public:
	Shader();
	~Shader();

	bool	Load(LPCWSTR fileName);	//シェーダファイルの読み込み
	bool	Load(LPCSTR fileName);	//シェーダファイルの読み込み
	void	DeviceLost();			//シェーダデバイスを失った
	void	DeviceReset();			//シェーダデバイスの復元
	void	Set();					//シェーダの設定
	void	Render();				//シェーダの描画


	//テクニックの設定
	void	SetTechnique(const char* techniqueName);		//テクニック名の設定
	void	SetTechniqueParam(const char* tecName);			//テクニックのパラメータのセット

	//座標・マトリックスの設定
	void	SetMatrix(D3DXMATRIX* mat);
	void	SetVector(D3DXVECTOR4* vec);
	//座標・マトリックスの設定(ハンドル付き)
	void	SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat);
	void	SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec);

	//シェーダのパラメータ設定
	D3DXHANDLE	GetParamTechnique(const char* technique);	//テクニックの設定
	D3DXHANDLE	GetParameterName(const char* shaderName);	//シェーダの変数の設定
	bool		SetParamTexture(const char* texName, LPDIRECT3DTEXTURE9 tex);	//テクスチャの設定

	//描画パスの開始
	void	BeginPass(UINT pass);
	void	EndPass();
	void	Begin(UINT* pass, DWORD flags);
	void	End();


	//頂点シェーダを与える
	LPDIRECT3DVERTEXSHADER9*	GetVertexShader();
	LPDIRECT3DPIXELSHADER9*		GetPixelShader();

	LPD3DXBUFFER				vertexShader;
	LPD3DXBUFFER				pixelShader;
	LPDIRECT3DVERTEXSHADER9		vertexHandler;		//バーテックスハンドラー
	LPDIRECT3DPIXELSHADER9		pixelHandler;		//ピクセルハンドラー


private:
	LPD3DXEFFECT	m_pEffect;		//シェーダのデバイス
	LPD3DXBUFFER	m_pErr;			//バッファ

	D3DXHANDLE		tecHandle;		//テクニックハンドル
};