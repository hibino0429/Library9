#include "DGD.h"

//------------------------------------------------------
//コンストラクタ
//------------------------------------------------------
DGD::DGD() : m_pD3D(0),m_pD3DDevice(0)
{
	
}

//------------------------------------------------------
//DGD実体の生成
//------------------------------------------------------
DGD*	DGD::Instance()
{
	if (instance == 0)
	{
		instance = new DGD;
	}

	return instance;
}


//------------------------------------------------------
//デバイスの初期化
//------------------------------------------------------
HRESULT DGD::DeviceInit(HWND hWnd, BOOL isFullScreen, int clientWidth, int clientHeight)
{
	D3DDISPLAYMODE d3ddm;


	// Direct3D9オブジェクトの作成
	if ((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0) {
		return E_FAIL;	// 取得失敗
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータを初期化
	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.BackBufferCount = 1;
	if (isFullScreen) { // フルスクリーンの場合
		m_D3DPP.Windowed = FALSE;			// フルスクリーン表示の指定
		m_D3DPP.BackBufferWidth = clientWidth;		// フルスクリーン時の横幅
		m_D3DPP.BackBufferHeight = clientHeight;		// フルスクリーン時の縦幅
	}
	else {
		m_D3DPP.Windowed = TRUE;				// ウインドウ内表示の指定
	}
	m_D3DPP.BackBufferFormat = d3ddm.Format;			// カラーモードの指定
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 
	m_D3DPP.EnableAutoDepthStencil = TRUE;						// エラー対策
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D16;				// エラー対策
	m_D3DPP.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;			//バックバッファの操作
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_D3DPP, &m_pD3DDevice))) {
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_D3DPP, &m_pD3DDevice))) {
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_D3DPP, &m_pD3DDevice))) {
				// 初期化失敗
				return E_FAIL;
			}
		}
	}


	return S_OK;
}



//------------------------------------------------------
//デバイスの解放
//------------------------------------------------------
void	DGD::DeviceFinal()
{
	if (m_pD3DDevice != NULL) {	m_pD3DDevice->Release(); m_pD3DDevice = NULL; }
	if (m_pD3D != NULL) { m_pD3D->Release(); m_pD3D = NULL; }

}


//------------------------------------------------------
//深度バッファとステンシルバッファのクリア
//------------------------------------------------------
bool	DGD::ViewAndStencilClear()
{
	if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 64),
		1.0f,
		0)))
	{
		MessageBox(NULL, TEXT("深度とステンシルのクリア失敗"), TEXT("ViewAndStencilClear"), MB_OK);
		return false;
	}

	/*if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0)))
	{
		MessageBox(NULL, TEXT("各サーフェイスの初期化に失敗"), TEXT("Clear"), MB_OK);
		return false;
	}*/
	return true;
}

//Zバッファのクリア
bool	DGD::ZBufClear()
{
	if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 64),
		1.0f,
		0)))
	{
		MessageBox(NULL, TEXT("Zバッファのクリア失敗"), TEXT("ZBufClear"), MB_OK);
		return false;
	}
	return true;
}

//------------------------------------------------------
//描画開始宣言
//------------------------------------------------------
bool	DGD::BeginRender()
{
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		return true;
	}
	MessageBox(NULL, TEXT("描画失敗"), TEXT("BeginScene"), MB_OK);
	return false;
}


//------------------------------------------------------
//描画終了宣言
//------------------------------------------------------
void	DGD::EndRender()
{
	m_pD3DDevice->EndScene();
}


//------------------------------------------------------
//描画結果を画面に転送する
//------------------------------------------------------
void	DGD::PresentRender()
{
	if (FAILED(m_pD3DDevice->Present(0, 0, 0, 0)))
	{
		m_pD3DDevice->Reset(&m_D3DPP);
	}
}



//--------------
//頂点バッファの作成
HRESULT	DGD::CreateVertexBuf(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf)
{
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(
		len,
		D3DUSAGE_WRITEONLY,
		fvf,
		D3DPOOL_MANAGED,
		vertexBuf,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("頂点バッファの失敗"), TEXT("頂点生成失敗"), MB_OK);
		return E_FAIL;
	}
	return S_OK;
}




//描画する頂点バッファの指定
void	DGD::SetVertexBufRender(UINT streamNum, IDirect3DVertexBuffer9* vertexBuf, UINT offsetBuf, UINT stride)
{
	m_pD3DDevice->SetStreamSource(streamNum, vertexBuf, offsetBuf, stride);
}

//頂点データのFVFフォーマットの設定
void	DGD::SetVertexFVF(DWORD fvf)
{
	m_pD3DDevice->SetFVF(fvf);
}

//頂点データを描画
void	DGD::VertexRender(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum)
{
	m_pD3DDevice->DrawPrimitive(renderType, startVertex, primitiveNum);
}


//頂点に張り付けるテクスチャのセット
void	DGD::SetVertexTexture(DWORD stageNum, LPDIRECT3DTEXTURE9 tex)
{
	m_pD3DDevice->SetTexture(stageNum, tex);
}

//頂点デコレーションを作成
bool	DGD::CreateVertexDecration(const D3DVERTEXELEMENT9* decl,LPDIRECT3DVERTEXDECLARATION9 pDecl)
{
	if (FAILED(m_pD3DDevice->CreateVertexDeclaration(decl,&pDecl)))
	{
		MessageBoxA(NULL, "頂点デコレーションの作成に失敗しました", "CreateVertexDecration", MB_OK);
		return false;
	}
	return true;
}


//--------------
//レンダリングステートの設定

//------------------------------------------------------
//両面(表裏)を描画するか
//------------------------------------------------------
void	DGD::CullMode(bool flag)
{
	if (flag)
	{
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}
}

//Z比較を行う
void	DGD::ZEnable(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, flag);
}

//ディザリングをするか
void	DGD::DitherEnable(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, flag);
}

//ライトを影響させるか
void	DGD::LightMode(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, flag);
}


//テクスチャステージの設定
void	DGD::SetTextureStageState(DWORD stage,D3DTEXTURESTAGESTATETYPE type,DWORD value)
{
	m_pD3DDevice->SetTextureStageState(stage, type, value);
}

//テクスチャラッピングモードの設定
void	DGD::SetSamplerState(DWORD stage,D3DSAMPLERSTATETYPE type,DWORD value)
{
	m_pD3DDevice->SetSamplerState(stage, type, value);
}



//------------------------
//マトリックスの設定

//マトリックスをレンダリングパイプラインに設定
void	DGD::SetMatrixToRender(D3DTRANSFORMSTATETYPE matType, D3DXMATRIX* mat)
{
	m_pD3DDevice->SetTransform(matType, mat);
}


//--------------------------
//ビューポートの設定
bool	DGD::SetViewPort(D3DVIEWPORT9* viewport)
{
	if (FAILED(m_pD3DDevice->GetViewport(viewport)))
	{
		MessageBox(NULL, TEXT("ビューポットの設定に失敗"), TEXT("SetViewPort"), MB_OK);
		return false;
	}
	return true;
}


//-------------------------
//ライトをレンダリングパイプラインへセット
void	DGD::SetLight(int num, D3DLIGHT9* light)
{
	m_pD3DDevice->SetLight(num, light);
}

//ライトを使用するか
void	DGD::LightEnable(int num, bool use)
{
	m_pD3DDevice->LightEnable(num, use);
}


//レンダリングパイプラインにセット
void	DGD::SetRenderState(D3DRENDERSTATETYPE type, DWORD value)
{
	m_pD3DDevice->SetRenderState(type, value);
}


bool	DGD::CretateTexture(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex)
{
	if (FAILED(D3DXCreateTextureFromFileA(
		m_pD3DDevice,
		fileName,
		pTex
	)))
	{
		MessageBox(NULL, TEXT("テクスチャの生成に失敗しました"), TEXT("CreateTextureA"), MB_OK);
		return false;
	}
	return true;
}

//---------------------------------
//テクスチャの生成
bool	DGD::CretateTexture(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex)
{
	if (FAILED(D3DXCreateTextureFromFileW(
		m_pD3DDevice,
		fileName,
		pTex
	)))
	{
		MessageBox(NULL, TEXT("テクスチャの生成に失敗"), TEXT("CreateTexture"), MB_OK);
		return false;
	}
	return true;
}

//テクスチャの生成Ex
bool	DGD::CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture)
{
	if (FAILED(D3DXCreateTextureFromFileExW(
		m_pD3DDevice,
		fileName,
		width,
		height,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
		colorKey, pSrcInfo, pPalette,
		texture
	)))
	{
		MessageBox(NULL, TEXT("テクスチャExの生成に失敗しました"), TEXT("CreateTextureEx"), MB_OK);
		return false;
	}
	return true;
}

bool DGD::CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO * pSrcInfo, PALETTEENTRY * pPalette, LPDIRECT3DTEXTURE9 * texture)
{
	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		fileName,
		width,
		height,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
		colorKey, pSrcInfo, pPalette,
		texture
	)))
	{
		MessageBox(NULL, TEXT("テクスチャExの生成に失敗しました"), TEXT("CreateTextureEx"), MB_OK);
		return false;
	}
	return true;
}


//---------------------------------
//スプライトの生成
bool	DGD::CreateSprite(LPD3DXSPRITE* pSprite)
{
	if (FAILED(D3DXCreateSprite(m_pD3DDevice, pSprite)))
	{
		MessageBox(NULL, TEXT("スプライトの生成に失敗"), TEXT("CreateSprite"), MB_OK);
		return false;
	}
	return true;
}

//サーフェイスの作成
bool	DGD::CreateOffScreenPlainSurface(UINT width, UINT height,D3DPOOL pool, IDirect3DSurface9** pSurface, HANDLE* sharedHandle)
{
	if (FAILED(m_pD3DDevice->CreateOffscreenPlainSurface(width, height, m_D3DPP.BackBufferFormat, pool, pSurface, sharedHandle)))
	{
		MessageBox(NULL, TEXT("サーフェイスの作成に失敗しました"), TEXT("CraeteOffScreenPlainSurface"), MB_OK);
		return false;
	}
	return true;
}


//サーフェイスの描画
void	DGD::SurfaceRender(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
{
	m_pD3DDevice->UpdateSurface(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
}

//サーフェイスのバックバッファ
void	DGD::GetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->GetRenderTarget(targetIndex, surface)))
	{
		MessageBox(NULL, TEXT("レンダーターゲットの取得に失敗しました"), TEXT("GetRenderTarget"), MB_OK);
		return;
	}
}

//サーフェイスのステンシルバッファ
void	DGD::GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->GetDepthStencilSurface(surface)))
	{
		MessageBox(NULL, TEXT("深度バッファのの取得に失敗しました"), TEXT("GetDepthStencilSurface"), MB_OK);
		return;
	}
}

//テクスチャの作成
bool	DGD::TextureCreate(LPDIRECT3DTEXTURE9* tex,UINT width,UINT height)
{
	if (FAILED(D3DXCreateTexture(
		m_pD3DDevice,
		width,
		height,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A16B16G16R16,			//D3DFMT_A8R8G8B8 , D3DFMT_A16B16G16R16
		D3DPOOL_DEFAULT,
		tex
	)))
	{
		MessageBox(NULL, TEXT("テクスチャの作成に失敗しました"), TEXT("TextureCreate"), MB_OK);
		return false;
	}
	return true;
}

//ステンシルバッファの作成
bool	DGD::StencilBufCreate(LPDIRECT3DSURFACE9* surface,UINT width,UINT height)
{
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(
		width,
		height,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		surface,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("ステンシルバッファの作成に失敗しました"), TEXT("StencilBufCreate"), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::StencilBufCreate(LPDIRECT3DSURFACE9* surf, UINT width, UINT height, D3DFORMAT format,
	D3DMULTISAMPLE_TYPE type, DWORD quality)
{
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(
		width, height,
		format, type, quality,
		FALSE,
		surf,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("ステンシルバッファの作成に失敗"), TEXT("StencilBufCreate"), MB_OK);
		return false;
	}
	return true;
}

//ステンシルバッファの設定
void	DGD::SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->SetDepthStencilSurface(*surface)))
	{
		MessageBox(NULL, TEXT("ステンシルバッファの設定に失敗しました"), TEXT("SetDepthStencilSurface"), MB_OK);
		return;
	}
}

//サーフェイスのセット
void	DGD::SetRenderTarget(DWORD num, LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->SetRenderTarget(num, *surface)))
	{
		MessageBox(NULL, TEXT("サーフェイスの設定に失敗しました"), TEXT("SetRenderTarget"), MB_OK);
		return;
	}
}



//---------------------------------
//フォントの生成
bool	DGD::CreateFont2D(
	float height, 
	float width, 
	UINT weight, 
	UINT wipLevels, 
	bool italic, 
	UINT charSet, 
	DWORD outputPrecision, 
	DWORD quority, 
	DWORD pitchAndfamiry, 
	LPCWSTR fontName, 
	LPD3DXFONT* pFont)
{
	if (FAILED(D3DXCreateFontW(
		m_pD3DDevice,
		(UINT)height,
		(UINT)width,
		weight,
		wipLevels,
		italic,
		charSet,
		outputPrecision,
		quority,
		pitchAndfamiry,
		fontName,
		pFont
	)))
	{
		MessageBox(NULL, TEXT("フォントの生成に失敗"), TEXT("CreateFont"), MB_OK);
		return false;
	}
	return true;
}
//フォントの生成
bool	DGD::CreateFont2DA(
	float height,
	float width,
	UINT weight,
	UINT wipLevels,
	bool italic,
	UINT charSet,
	DWORD outputPrecision,
	DWORD quority,
	DWORD pitchAndfamiry,
	LPCSTR fontName,
	LPD3DXFONT* pFont)
{
	if (FAILED(D3DXCreateFontA(
		m_pD3DDevice,
		(UINT)height,
		(UINT)width,
		weight,
		wipLevels,
		italic,
		charSet,
		outputPrecision,
		quority,
		pitchAndfamiry,
		fontName,
		pFont
	)))
	{
		MessageBox(NULL, TEXT("フォントの生成に失敗"), TEXT("CreateFont"), MB_OK);
		return false;
	}
	return true;
}

//---------------------------------
//モデルのロード
bool	DGD::LoadModel(LPCWSTR modelName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
{
	if (FAILED(D3DXLoadMeshFromXW(
		modelName,
		D3DXMESH_SYSTEMMEM,
		m_pD3DDevice,
		NULL,
		mtrlBuf,
		NULL,
		numMtrl,
		mesh)))
	{
		MessageBox(NULL, TEXT("モデルの読み込み失敗"), TEXT("LoadModel"), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::LoadModel(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
{
	if (FAILED(D3DXLoadMeshFromXA(
		fileName,
		D3DXMESH_SYSTEMMEM,
		m_pD3DDevice,
		NULL,
		mtrlBuf,
		NULL,
		numMtrl,
		mesh)))
	{
		MessageBoxA(NULL, "モデルの読み込み失敗","LoadModel", MB_OK);
		return false;
	}
	return true;
}


//マテリアルのセット
void	DGD::SetMaterial(D3DMATERIAL9* mtrl)
{
	m_pD3DDevice->SetMaterial(mtrl);
}




//------------------------------------------
//シェーダ関連処理
//------------------------------------------
//エフェクトファイルの読み込み
bool	DGD::LoadEffectFile(LPCWSTR fileName,LPD3DXEFFECT* pEffect,LPD3DXBUFFER pErr)
{
	if (FAILED(D3DXCreateEffectFromFileW(m_pD3DDevice, fileName,
		NULL, NULL, 0, NULL, pEffect, &pErr)))
	{
		MessageBox(NULL, TEXT("シェーダファイルが読み込めません"), TEXT("シェーダエラー"), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::LoadEffectFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
{
	if (FAILED(D3DXCreateEffectFromFileA(m_pD3DDevice, fileName,
		NULL, NULL, 0, NULL, pEffect, &pErr)))
	{
		MessageBoxA(NULL, "シェーダファイルが読み込めませんでした", "LoadEffectFile", MB_OK);
		return false;
	}
	return true;
}

//頂点シェーダハンドラの生成
bool	DGD::CreateVertexShader(LPD3DXBUFFER pShader,DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHandler)
{
	if (FAILED(m_pD3DDevice->CreateVertexShader(
		(DWORD*)pShader->GetBufferPointer(),
		shaderHandler
	)))
	{
		MessageBox(NULL, TEXT("頂点シェーダハンドラの生成に失敗"), TEXT("CreateVertexShader"), MB_OK);
		return false;
	}
	return true;
}
//ピクセルシェーダハンドラの生成
bool	DGD::CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler)
{
	if (FAILED(m_pD3DDevice->CreatePixelShader(
		(DWORD*)pShader->GetBufferPointer(),
		shaderHandler
	)))
	{
		MessageBox(NULL, TEXT("ピクセルシェーダの生成に失敗"), TEXT("CreatePixelShader"), MB_OK);
		return false;
	}
	return true;
}

//頂点シェーダの設定
bool	DGD::SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader)
{
	if (FAILED(m_pD3DDevice->SetVertexShader(*pShader)))
	{
		MessageBox(NULL, TEXT("頂点シェーダの設定に失敗しました"), TEXT("SetVertexShader"), MB_OK);
		return false;
	}
	return true;
}
//ピクセルシェーダの設定
bool	DGD::SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader)
{
	if (FAILED(m_pD3DDevice->SetPixelShader(*pShader)))
	{
		MessageBox(NULL, TEXT("ピクセルシェーダの設定に失敗しました"), TEXT("SetPixelShader"), MB_OK);
		return false;
	}
	return true;
}