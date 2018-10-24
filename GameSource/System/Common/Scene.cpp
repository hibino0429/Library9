//
// Scene.cpp
// シーンの実装
//

#include <windows.h>

#include "Scene.h"

//=============================================================
// 実装
//=============================================================
//-------------------------------------------------------------
// デフォルトコンストラクタ
//-------------------------------------------------------------
Scene::Scene()
 :m_pMyVB(0)
{
}

//-------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------
Scene::~Scene()
{

	Destroy();
}

//-------------------------------------------------------------
// シーンを生成
// 引数
//		pD3DDevice : IDirect3DDevice9 インターフェイスへのポインタ
// 戻り値
//		成功したらS_OK
//-------------------------------------------------------------
HRESULT Scene::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	Destroy();

	if(pD3DDevice == 0) {
		return E_FAIL;
	}

	//--------------------------------------
	// モデルの頂点バッファーを生成
	//--------------------------------------

	// 4つの頂点からなる頂点バッファを作る
	if( FAILED( pD3DDevice->CreateVertexBuffer( 
		4*sizeof(MY_VERTEX),	// 頂点バッファ全体のサイズ
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使われ方
        MY_VERTEX_FVF,			// 頂点データのFVFフォーマット
        D3DPOOL_MANAGED, 		// システムの頂点バッファ扱い方
		&m_pMyVB, 				// 頂点バッファを格納する変数
		NULL ) ) )				// 常にNULLに指定
	{
        return E_FAIL;
	}


    //頂点バッファーの中身を埋める
    MY_VERTEX* v;
    m_pMyVB->Lock( 0, 0, (void**)&v, 0 );

	//頂点データ：頂点の座標値の設定
    v[0].p = D3DXVECTOR3(-1.5f,  1.5f, 0.0f );	// 頂点①
    v[1].p = D3DXVECTOR3( 1.5f,  1.5f, 0.0f );	// 頂点②
    v[2].p = D3DXVECTOR3(-1.5f, -1.5f, 0.0f );	// 頂点③
    v[3].p = D3DXVECTOR3( 1.5f, -1.5f, 0.0f );	// 頂点④
    
	//頂点データ：頂点の基本的な色の設定（白色に設定）
    v[0].color = v[1].color = v[2].color = v[3].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_pMyVB->Unlock();

	//--------------------------------------
	// レンダリングステートパラメータの設定
	//--------------------------------------

	// 両面描画モードの指定
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// Ｚ比較を行なう
    pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ディザリングを行なう（高品質描画）
	pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE);
	// ノーライティングモード 	
    pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	

	return S_OK;
}

//-------------------------------------------------------------
// 座標変換を行う
// 引数
//		pD3DDevice : IDirect3DDevice9 インターフェイスへのポインタ
//-------------------------------------------------------------
void Scene::Transform(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if(pD3DDevice == 0) {
		return;
	}

	//---------------------------
	// ビューマトリックスの設定
	//---------------------------

	// 初期化
	D3DXMatrixIdentity(&m_view);

	// カメラの位置と方向を設定
	D3DXMatrixLookAtLH(&m_view, 
			&D3DXVECTOR3( 0.0f, 0.0f, -10.0f),	// カメラの位置
			&D3DXVECTOR3( 0.0f, 0.0f, 0.0f),	// カメラの方向を向ける点
			&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));	// カメラの上の方向

	// マトリックスをレンダリングパイプラインに設定
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_view);
		

	//---------------------------
	// 射影マトリックスの設定
	//---------------------------

	// ビューポートの取得
	D3DVIEWPORT9    vp;
	if(FAILED(pD3DDevice->GetViewport(&vp))) {
		return;
	}

	// アスペクト比の計算
	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	// 初期化
	D3DXMatrixIdentity(&m_proj);

	// 射影マトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_proj, 
			D3DXToRadian(45.0f),	// カメラの画角
			aspect,					// アスペクト比
			1.0f,					// nearプレーン
			1000.0f);				// farプレーン

	// マトリックスをレンダリングパイプラインに設定
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_proj);

}

//-------------------------------------------------------------
// オブジェクト等の描画
// 引数
//		pD3DDevice : IDirect3DDevice9 インターフェイスへのポインタ
//-------------------------------------------------------------
void Scene::Draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if(pD3DDevice == 0) {
		return;
	}

	if(m_pMyVB == 0) {
		return;
	}

	// 座標変換（カメラの設定など）
	Transform(pD3DDevice);

	// 座標変換（モデルの配置）
	D3DXMatrixIdentity(&m_world);
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_world);

	//--------------------------------------
	// 頂点バッファーの描画
	//--------------------------------------

	// 頂点バッファーをレンダリングパイプラインに設定
    pD3DDevice->SetStreamSource( 0, m_pMyVB, 0, sizeof(MY_VERTEX) );
    
	// 頂点データのＦＶＦフォーマットを設定
    pD3DDevice->SetFVF( MY_VERTEX_FVF );

	// 描画
    pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

}

//-------------------------------------------------------------
// シーンの破棄
//-------------------------------------------------------------
void Scene::Destroy()
{
	// 頂点バッファーの解放
	SAFE_RELEASE(m_pMyVB);
}
