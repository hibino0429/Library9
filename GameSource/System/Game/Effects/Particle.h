#pragma once

#include "../../../Library9/Function.h"

#include <mmsystem.h>
#include <math.h>

//パーティクルクラス
class Particle
{
public:

	Particle();
	~Particle();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

private:

	//頂点バッファの定義
	struct MY_VERTEX
	{
		D3DXVECTOR3	pos;		//位置
		FLOAT		p_sizse;	//サイズ
		DWORD		color;		//色
	};
#define MY_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)


	//ポイントスプライトの定義
	struct PointSprite
	{
		D3DXVECTOR3		pos;	//初期位置
		float			psize;	//サイズ
		D3DXVECTOR3		vec;	//初期の角度
		DWORD			startTime;	//開始時間
		float			duration;	//継続時間
	};

#define MY_NUM_PSPRITE 128

	PointSprite		m_psprite[MY_NUM_PSPRITE];

	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャ画像
	
	LPDIRECT3DVERTEXBUFFER9	m_pVBEffect;	//エフェクトバッファ


	//マトリックス
	Mat4X4::Matrix		world;	//ワールド座標系
};