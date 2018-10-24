#pragma once

#include <d3dx9.h>
#include <d3d9.h>

#pragma comment( lib, "d3d9.lib" )
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

//DirectX Graphics Device
class DGD
{

	//シングルトンクラスにする
	//1:DGDを生成するメソッドの作成
	//2:DGDの処理の作成
	//3:protected のコンストラクタ
	//4:private の自己クラスのポインタ

public:
	static	DGD*	Instance();	//DGD生成メソッド
	//処理

protected:
	DGD();

private:
	

	static DGD*		instance;


public:

	//デバイスの初期化
	HRESULT		DeviceInit(HWND, BOOL, int, int);

	//デバイスの解放
	void		DeviceFinal();


public:

	//デバイスの機能
	////
	bool	ViewAndStencilClear();	//ビューポートと深度バッファのクリア
	bool	ZBufClear();			//Zバッファのクリア

	bool	BeginRender();
	void	EndRender();
	void	PresentRender();


	////
	//頂点バッファの作成
	HRESULT	CreateVertexBuf(UINT, DWORD, IDirect3DVertexBuffer9**);
	//頂点バッファの描画を行うバッファを指定
	void	SetVertexBufRender(UINT, IDirect3DVertexBuffer9*, UINT, UINT);
	//頂点のFVFフォーマットの設定
	void	SetVertexFVF(DWORD);
	//頂点の描画
	void	VertexRender(D3DPRIMITIVETYPE, UINT, UINT);
	//頂点に張り付けるテクスチャのセット
	void	SetVertexTexture(DWORD, LPDIRECT3DTEXTURE9);
	//頂点のデコレーションを作成
	bool	CreateVertexDecration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl);

	////
	//レンダリングステートパラメータ
	void	CullMode(bool);		//三角形の背面を描画するか
	void	ZEnable(bool);		//Z比較するか
	void	DitherEnable(bool);	//ディザリング(高品質描画)するか
	void	LightMode(bool);	//ライトを影響させるか

	//レンダリングパイプラインにセット
	void	SetRenderState(D3DRENDERSTATETYPE, DWORD);

	//テクスチャステージの設定
	void	SetTextureStageState(DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);

	//テクスチャラッピングモード
	void	SetSamplerState(DWORD, D3DSAMPLERSTATETYPE, DWORD);


	////
	//マトリックスをレンダリングパイプラインに設定
	void	SetMatrixToRender(D3DTRANSFORMSTATETYPE, D3DXMATRIX*);

	////
	//ビューポートの設定
	bool	SetViewPort(D3DVIEWPORT9*);


	////
	//ライト
	void	SetLight(int num, D3DLIGHT9*);	//ライトをレンダリングへ追加
	void	LightEnable(int num, bool use);	//ライトを使うか

	//画像の読み込み
	bool	CretateTexture(LPCWSTR, LPDIRECT3DTEXTURE9*);
	bool	CretateTexture(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex);
	//画像の読み込みEx
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);
	bool	CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);


	//スプライトの生成
	bool	CreateSprite(LPD3DXSPRITE*);

	//仮
	//サーフェイスの作成
	bool	CreateOffScreenPlainSurface(UINT, UINT, D3DPOOL, IDirect3DSurface9**, HANDLE*);
	
	//サーフェイスの描画
	void	SurfaceRender(IDirect3DSurface9*,const RECT*,IDirect3DSurface9*,const POINT*);

	//仮
	//バックバッファのサーフェイス
	void	GetRenderTarget(DWORD,LPDIRECT3DSURFACE9*);
	//ステンシルバッファの取得
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9*);
	//テクスチャの作成
	bool	TextureCreate(LPDIRECT3DTEXTURE9* tex,UINT width,UINT height);
	//ステンシルバッファの作成
	bool	StencilBufCreate(LPDIRECT3DSURFACE9* surface,UINT width,UINT height);
	bool	StencilBufCreate(LPDIRECT3DSURFACE9* surf, UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality);

	//ステンシルバッファの設定
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9*);
	//サーフェイスをセットする
	void	SetRenderTarget(DWORD, LPDIRECT3DSURFACE9*);

	//フォントの生成
	bool	CreateFont2D(float, float, UINT, UINT, bool, UINT, DWORD, DWORD, DWORD, LPCWSTR, LPD3DXFONT*);
	bool	CreateFont2DA(float, float, UINT, UINT, bool, UINT, DWORD, DWORD, DWORD, LPCSTR, LPD3DXFONT*);

	//モデルの読み込み
	bool	LoadModel(LPCWSTR, LPD3DXBUFFER*, DWORD*, LPD3DXMESH*);
	bool	LoadModel(LPCSTR, LPD3DXBUFFER*, DWORD*, LPD3DXMESH*);

	//マテリアルのセット
	void	SetMaterial(D3DMATERIAL9*);


	//--------------------------
	//シェーダ関連処理
	//--------------------------
	bool	LoadEffectFile(LPCWSTR fileName,LPD3DXEFFECT* pEffect,LPD3DXBUFFER pErr);
	bool	LoadEffectFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	bool	CreateVertexShader(LPD3DXBUFFER pShader,DWORD*,LPDIRECT3DVERTEXSHADER9*);
	bool	CreatePixelShader(LPD3DXBUFFER pShader,DWORD*,LPDIRECT3DPIXELSHADER9*);
	bool	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader);
	bool	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader);
public:

	D3DXMATRIX	world;

private:
	public:
	//デバイス
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DPRESENT_PARAMETERS	m_D3DPP;

};