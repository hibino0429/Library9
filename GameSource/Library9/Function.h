#pragma once
#include "DGD.h"
#include "../Library9/Collision/Box.h"

#define DELETE_SAFE_ARRAY(me) {if(me){delete[] (me); (me) = NULL;}}
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = NULL;} }
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] (p); (p) = NULL;} }
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = NULL;} }

//----------------------------------------------------------------
//機能群
//----------------------------------------------------------------
class Box2D;


//----------------------------------------------------------------------------
//画像
//----------------------------------------------------------------------------
namespace Texture2
{
	class Image
	{
	public:

		Image();
		~Image();

		//提供するメソッド

		//読み込み処理
		//引数1:画像のファイルパス
		void	LoadTexture(LPCWSTR);
		void	LoadTexture(LPCSTR);
		//画像の破棄
		void	Destroy();
		

		//引数1:画像の位置・大きさ
		//引数2:ソースの画像の位置・大きさ
		//引数3:画像の色
		void	Render(Box2D, Box2D, D3DXCOLOR = D3DXCOLOR(1,1,1,1));


	private:

		void	SetCenter(D3DXVECTOR3);		
		void	SetPosition(D3DXVECTOR3);
		void	SetRect(Box2D);
		void	SetColor(D3DXCOLOR);		


		//スプライト処理
		void	CreateSprite();					//スプライトの作成

		//サーフェイス処理
		void	CreateSurface(UINT, UINT);		//サーフェイスの作成
		void	RenderSurface(IDirect3DSurface9*, const RECT*, IDirect3DSurface9*, const POINT*);		//サーフェイスの描画
		bool	GetSurfaceLevel(UINT);			//テクスチャからサーフェイルを取得

		//バックバッファ・ステンシルバッファ処理
		void	GetRenderTarget(UINT);				//バックバッファのサーフェイスの取得
		void	GetDepthStencilSurface();			//ステンシルバッファの取得
		void	CreateStencilSurface(UINT, UINT);	//ステンシルバッファの生成


		bool	GetImageInfo(LPCWSTR fileName);		//画像ファイルのサイズをフォーマットを取得
		bool	GetImageInfo(LPCTSTR fileName);
		bool	CreatePlainSurface();				//画像のサーフェイスを作成
		
		//サーフェイスに画像ファイルを読み込む
		bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
		bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCTSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
		bool	LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect);
		bool	LoadSurface(LPCTSTR fileName, const RECT* drawRect, const RECT* srcRect);

		void	Rotation(float angle);
		void	Scale(D3DXVECTOR2 scale);
	
	private:

		LPD3DXSPRITE		m_pSprite;			//スプライトの格納
		LPDIRECT3DTEXTURE9	m_pTexture;			//テクスチャの格納


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
}


//-------------------------------------------------------------------------------
//フォント
//-------------------------------------------------------------------------------
namespace Text
{
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
		bool	Create(LPCWSTR,float,float);
		bool	Create(LPCSTR, float, float);
		//フォントの解放
		void	Destory();

		//フォントの描画
		//引数1:文字列
		//引数2:表示範囲
		//引数3:色
		void	Render(LPCWSTR,Box2D,D3DXCOLOR = D3DXCOLOR(1,1,1,1));
		void	Render(LPCSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1,1,1,1));
	private:
		LPD3DXFONT		pFont;	//フォントオブジェクト
	};
}


//--------------------------------------------------------------------------------
//Xファイル(モデル)
//--------------------------------------------------------------------------------
namespace XFile
{
	class ModelX
	{
	public:
		ModelX();
		~ModelX();

		//関数処理

		//引数1:モデルのファイルパス
		bool		Load(LPCWSTR);		//モデルの読み込み
		bool		Load(LPCSTR);		
		void		Erase();			//モデルの解放
		void		Render();			//モデルの描画

		bool		BoundingBox();		//モデルのあたり判定



	private:
		//Xファイル情報
		LPD3DXMESH			m_pMesh;		//メッシュのインターフェイス
		LPD3DXBUFFER		m_pMtrlBuf;		//メッシュのマテリアル
		DWORD				m_MtrlNum;		//マテリアルの数

	public:
		LPDIRECT3DTEXTURE9*	m_texture;		//テクスチャ情報

	public:
		D3DXVECTOR3			pos;
		D3DXVECTOR3			angle;
		D3DXVECTOR3			size;
		D3DXVECTOR3			minB;
		D3DXVECTOR3			maxB;

		static int modelNum;

	};
}

//////////////////////////////////////////////////////////////////////////

//フォントの処理
namespace LibFont
{
	bool	Create(LPCWSTR, float, float,LPD3DXFONT*);
	bool	Create(LPCSTR, float, float,LPD3DXFONT*);
}

//テクスチャの処理
namespace LibTexture
{
	//画像の生成処理
	void	Create(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex);
	void	Create(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex);

	//スプライトの作成
	void	CreateSprite(LPD3DXSPRITE* sprite);

	//画像のサーフェイスの取得
	bool	CreatePlainSurface(D3DXIMAGE_INFO* imageInfo,LPDIRECT3DSURFACE9* surface);

	//サーフェイスの描画
	void	RenderSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint);

	//サーフェイスの作成
	void	CreateSurface(UINT width, UINT height, LPDIRECT3DSURFACE9* backBufSurface);

	//テクスチャからサーフェイスを取得
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex, LPDIRECT3DSURFACE9* surface);
}

//XModel専用の関数群
namespace LibModel
{
	//モデルのロード処理
	void	Load(LPCWSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh);
	void	Load(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh);

	void	SetMaterial(D3DMATERIAL9* material);

}

//Shaderの処理
namespace LibShader
{
	bool	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	bool	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
}

//Matrixの処理
namespace LibMatrix
{
	void	SetMatrix(D3DTRANSFORMSTATETYPE type, D3DXMATRIX* mat);
}


//----------------------------------------------------------------------------------
//頂点バッファ
//XXX:機能改善の必要がある
//----------------------------------------------------------------------------------
namespace VertexBuf
{
	//ビルボード
	class Billboard
	{
	public:

		Billboard();
		~Billboard();

		//ビルボードの生成
		bool	Create();

		//頂点バッファの中身を埋める
		void	SetVertex();

		//頂点1つの設定
		//void	SetVertex(int number, D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXCOLOR color);

		//ビルボードの破棄
		void	Destroy();

		//ビルボードの描画
		void	Render();
		

		//テクスチャ画像の読み込み
		bool	LoadVertexTex(LPCWSTR);

		bool	LoadVertexTexA(LPCSTR);

		void	SetMatrix();			//マトリックスのセット
		//void	ReceiveViewMatrix(D3DXVECTOR3&,D3DXVECTOR3&,D3DXVECTOR3&);	//ビューマトリックスを受け取る

	#define VertexFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	private:

		struct Vertex
		{
			D3DXVECTOR3		pos;
			DWORD			diffuse;
			D3DXVECTOR2		tex;
		};

		LPDIRECT3DVERTEXBUFFER9	m_pVB;		//頂点バッファ

	public:
		LPDIRECT3DTEXTURE9		m_pTexture;	//テクスチャの情報


		D3DXVECTOR3		pos;
		D3DXVECTOR3		angle;
		D3DXVECTOR3		size;
	};
}


//--------------------------------------------------------------------------
//マトリックス機能
//--------------------------------------------------------------------------
namespace Mat4X4
{
	class Matrix
	{
	public:

		Matrix();
		
		//マトリックスをセットする
		//引数1:変換する行列
		void	SetMatrix(D3DTRANSFORMSTATETYPE type);

	public:
		D3DXMATRIX	mat;
	};
}


//---------------------------------------------------------
//シェーダクラス
//---------------------------------------------------------
namespace Effect
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void	Load(LPCWSTR fileName);	//シェーダファイルの読み込み
		void	Load(LPCSTR fileName);	//シェーダファイルの読み込み
		void	DeviceLost();			//シェーダデバイスを失った
		void	DeviceReset();			//シェーダデバイスの復元
		void	Set();					//シェーダの設定
		void	Render();				//シェーダの描画


		//テクニックの設定
		void	SetTechnique(const char* techniqueName);		//テクニック名の設定
		void	SetProjectViewMatrixName(const char* mWVPName);	//射影変換行列名の設定
		void	SetWorldMatrixName(const char* mWITName);		//ワールド変換行列名の設定
		void	SetLightDirName(const char* vLightDirName);		//ライトの方向名の設定
		void	SetColorName(const char* colorName);			//色名の設定

		//座標・マトリックスの設定
		void	SetMatrix(D3DXMATRIX* mat);
		void	SetVector(D3DXVECTOR4* vec);
		//座標・マトリックスの設定(ハンドル付き)
		void	SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat);
		void	SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec);

		//シェーダのパラメータ設定
		D3DXHANDLE	GetParamTechnique(const char* technique);	//テクニックの設定
		D3DXHANDLE	GetParameterName(const char* shaderName);	//シェーダの変数の設定
		bool		SetParamTexture(const char* texName,LPDIRECT3DTEXTURE9 tex);		//テクスチャの設定

		//描画パスの開始
		void	BeginPass(UINT pass);
		void	EndPass();
		void	Begin(UINT* pass,DWORD flags);
		void	End();
	private:


	public:
		LPD3DXEFFECT	m_pEffect;		//シェーダのデバイス
		LPD3DXBUFFER	m_pErr;			//バッファ

		//ハンドルはやはり、別に持たせる
		D3DXHANDLE		m_hTechnique;	//テクニック
		D3DXHANDLE		m_hmWVP;		//ローカル - 射影変換行列
		D3DXHANDLE		m_hmWIT;		//ローカル - ワールド変換行列
		D3DXHANDLE		m_hvLightDir;	//ライトの方向
		D3DXHANDLE		m_hvCol;		//頂点色
	};
}



//-------------------------------------------------------------------
//オブジェクトなど、共通して使用する機能
//-------------------------------------------------------------------
namespace LibDGD
{
	//レンダリングパイプラインにセット
	void	SetRenderState(D3DRENDERSTATETYPE, DWORD);

	//テクスチャステージセット
	void	SetTexStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value);

	//テクスチャのラッピングモード
	void	SetTexSamplerState(DWORD stage, D3DSAMPLERSTATETYPE type, DWORD value);

	//ストリームソースのセット
	void	SetStreamSource(UINT, LPDIRECT3DVERTEXBUFFER9, UINT, UINT);

	//FVFの設定
	void	SetFVF(DWORD fvf);

	//三角形の描画
	void	DrawPrimitive(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum);

	//頂点バッファの設定
	bool	CreateVertexBuffer(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf);
	//頂点のデコレーションの作成
	void	CreateVertexDeclaration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl);

	//テクスチャ画像の読み込み(VertexBuf用)
	bool	CreateTexVertexBuf(LPCTSTR fileName,LPDIRECT3DTEXTURE9* pTex);
	//テクスチャ画像の読み込み
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);
	bool	CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);

	//テクスチャをパイプラインにセット
	void	SetTexture(DWORD number, LPDIRECT3DTEXTURE9);

	//ビューとステンシルのクリア
	bool	ViewAndStencilClear();

	//バックシーンのクリア
	void	SceneClear();

	//Zバッファのクリア
	void	ZBufClear();

	//ビューポートの設定
	bool	SetViewPort(D3DVIEWPORT9*);

	//ライト関係の処理
	void	SetLight(int num, D3DLIGHT9* pLight);	//ライトのセット
	void	SetUseLight(int num, bool useFlag);		//ライトを使用するか

	bool	BeginRender();	//描画の開始
	void	EndRender();	//描画の終了
	void	PresentRender();//描画の反映

	//シャドウマップ関係
	void	CreateTexture(UINT width,UINT height,LPDIRECT3DTEXTURE9* tex);
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex,LPDIRECT3DSURFACE9* surface);
	void	CreateDepthStencilSurface(UINT widht,UINT height,LPDIRECT3DSURFACE9* surface);
	void	CreateDepthStencilSurface(UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality, LPDIRECT3DSURFACE9* surf);

	void	GetRenderTarget(DWORD, LPDIRECT3DSURFACE9* surface);
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface);

	void	SetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface);
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface);

	void	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader);
	void	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader);

	//シェーダ関連の処理
	void	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	void	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	void	CreateVertexShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHander);
	void	CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler);

	//仮の追加処理
	void	SetVertexBuf(UINT num, IDirect3DVertexBuffer9* verBuf, UINT size, UINT zero);
	void	VertexRender(D3DPRIMITIVETYPE type, UINT start, UINT num);
}



//----------------------------------------------------------------------------------
//デバイス共通の処理
//----------------------------------------------------------------------------------
namespace LibDEV
{
	HRESULT InitDevice(HWND, BOOL, int, int);		//Direct3Dの初期化
	void	FinalDevice();							//Direct3Dの解放

	LPDIRECT3DDEVICE9* GetDevice();					//デバイスを渡す
}