#include "Particle.h"


//コンストラクタ
Particle::Particle() : m_pVBEffect(NULL),m_pTexture(NULL)
{
	D3DXMatrixIdentity(&world.mat);
}

//デストラクタ
Particle::~Particle()
{
	
	if (m_pTexture != nullptr) { m_pTexture->Release(); }
	if (m_pVBEffect != nullptr) { m_pVBEffect->Release(); }

}


//------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------
void	Particle::Initialize()
{
	MY_VERTEX*	v;

	//頂点バッファの作成
	if (FAILED(LibDGD::CreateVertexBuffer(
		MY_NUM_PSPRITE * sizeof(MY_VERTEX),
		MY_VERTEX_FVF,
		&m_pVBEffect
	)))
	{
		MessageBox(NULL, TEXT("頂点バッファの作成に失敗しました"), TEXT("すいません"), MB_OK);
		return;
	}

	//テクスチャの読み込み
	//画像の読み込み
	if (FAILED(LibDGD::CreateTextureEx(
		TEXT("./data/image/spark.bmp"), 0, 0, 0xFF000000, NULL, NULL, &m_pTexture
	)))
	{
		MessageBox(NULL, TEXT("テクスチャの画像"), TEXT("CreateTextureEx"), MB_OK);
		return;
	}

	//////画面の描画モード
	//LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	////ライトの計算をしない
	//LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	////Z比較を行わない
	//LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	//////ディザリングを行う
	//LibDGD::SetRenderState(D3DRS_DITHERENABLE, TRUE);


	////テクスチャステージの設定
	//LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//LibDGD::SetTexStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//LibDGD::SetTexStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	////アルファブレンディングの設定
	//LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	////テクスチャフィルターの設定
	//LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////ポイントスプライトの設定
	//LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);	//ポイントスプライトを教える
	//
	//LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);	//視点に応じてサイズを変更
	//LibDGD::SetRenderState(D3DRS_POINTSIZE, 1.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSIZE_MIN, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_C, 1.0f);	//距離の2乗


	////////////////////////////////////
	//ポイントスプライトの初期化
	////////////////////////////////////
	DWORD	time = ::timeGetTime();
	int i;
	for (i = 0; i < MY_NUM_PSPRITE; i++)
	{
		//ポイントスプライトの初期位置
		m_psprite[i].pos = D3DXVECTOR3(0, 0, 0);

		//ポイントスプライトの初速度とその方向
		m_psprite[i].vec.x = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;
		m_psprite[i].vec.y = ((float)rand() / (float)RAND_MAX) * 30.0f + 30.0f;
		m_psprite[i].vec.z = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;

		//ポイントスプライトのサイズ
		m_psprite[i].psize = ((float)rand() / (float)RAND_MAX) * 4.0f + 8.0f;

		//ポイントスプライトの継続時間
		m_psprite[i].duration = ((float)rand() / (float)RAND_MAX) * 2.0f + 2.0f;

		//ポイントスプライトの開始時間
		m_psprite[i].startTime = time - (DWORD)(((float)rand() / (float)RAND_MAX) * 2.0f * 1000.0f);

	}

	
	//頂点バッファの中身を埋める
	m_pVBEffect->Lock(0, 0, (LPVOID*)&v, 0);
	for (i = 0; i < MY_NUM_PSPRITE; ++i)
	{
		v[i].color = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	}
	m_pVBEffect->Unlock();

}



//------------------------------------------------------------------------
//解放処理
//------------------------------------------------------------------------
void	Particle::Finalize()
{

}



//------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------
void	Particle::UpDate()
{
	
}



//------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------
void	Particle::Render()
{
	//シーンのクリア
	LibDGD::ZBufClear();

	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//テクスチャステージの設定
	LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	//アルファブレンディングの設定
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャフィルターの設定
	LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//ポイントスプライトの設定
	LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);	//ポイントスプライトを教える
	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);	//視点に応じてサイズを変更
	LibDGD::SetRenderState(D3DRS_POINTSIZE, (DWORD)1.0f);
	LibDGD::SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_A, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_B, (DWORD) 0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_C, (DWORD)1.0f);	//距離の2乗

	DWORD	time = timeGetTime();
	MY_VERTEX*	v;

	int i;

	//ポイントスプライトの更新
	float t;
	m_pVBEffect->Lock(0, 0, (LPVOID*)&v, 0);
	for (i = 0; i < MY_NUM_PSPRITE; ++i)
	{
		//経過時間を計算
		t = (float(time - m_psprite[i].startTime)) / 1000.0f;

		//継続時間を超えていたら初期化する
		if (t > m_psprite[i].duration)
		{
			m_psprite[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_psprite[i].startTime = time;
			m_psprite[i].duration = ((float)rand() / (float)RAND_MAX) * 2.0f + 2.0f;
			t = 0.0f;
		}

		//ポイントスプライトの位置の計算
		v[i].pos.x = m_psprite[i].pos.x + m_psprite[i].vec.x * t + 0.5f * (0.0f) * t * t;
		v[i].pos.y = m_psprite[i].pos.y + m_psprite[i].vec.y * t + 0.5f * (-9.8f) * t * t;
		v[i].pos.z = m_psprite[i].pos.z + m_psprite[i].vec.z * t + 0.5f * (0.0f) * t * t;

		//ポイントスプライトのサイズを設定
		v[i].p_sizse = m_psprite[i].psize;
	}
	m_pVBEffect->Unlock();


	//////////////////////////////////////////////
	//エフェクトの描画
	//////////////////////////////////////////////
	LibDGD::SetTexture(0, m_pTexture);

	//ワールド変換
	D3DXMatrixIdentity(&world.mat);
	world.SetMatrix(D3DTS_WORLD);


	//オブジェクトの描画
	LibDGD::SetStreamSource(0, m_pVBEffect, 0, sizeof(MY_VERTEX));
	LibDGD::SetFVF(MY_VERTEX_FVF);
	LibDGD::DrawPrimitive(D3DPT_POINTLIST, 0, MY_NUM_PSPRITE);

	LibDGD::SetTexture(0, NULL);
	//レンダリングステートを戻す
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);	//視点に応じてサイズを変更
	LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);	//ポイントスプライトを教える

}