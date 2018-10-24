#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Animation.h"

#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>


//魔法エフェクトクラス
class MagicEffect
{
public:

	MagicEffect();
	~MagicEffect();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();



private:

	Animation*	m_animAngle;
	Animation*	m_animRadius;
	Animation*	m_animHeight;
	int			m_numAnimArrayElem;	//オブジェクトの数


	//頂点バッファ
	struct Vertex1
	{
		D3DXVECTOR3		pos;	//位置
		float			p_size;	//サイズ
		DWORD			color;	//色
	};
	
#define VERTEX_FVF (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)

	LPDIRECT3DVERTEXBUFFER9		m_VBEffect;		//頂点バッファ
	LPDIRECT3DTEXTURE9			m_TexEffect;	//テクスチャ


	Mat4X4::Matrix		world;
};