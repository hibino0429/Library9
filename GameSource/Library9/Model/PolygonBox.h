#pragma once
#include "../Function.h"
#include "../Collision/Box.h"



//-----------------------------------------------------------------------
//ポリゴンボックスのクラス
//-----------------------------------------------------------------------
class PolyBox
{
public:
	PolyBox();
	~PolyBox();

	//ポリゴンボックスの初期化
	bool	CreateHitBox(Box3D& hitbox);
	//ポリゴンボックスの描画
	void	DrawHitBox();

	//マトリックス処理
	void	WorldMat(Box3D hitbox);
	

private:

	//頂点バッファの構造体
	struct VertexBox
	{
		D3DXVECTOR3		pos;		//位置
		DWORD			diffuse;	//色
	};
#define BoxFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE )

	LPDIRECT3DVERTEXBUFFER9		pVB;	//バーテックスバッファ

	//ワールドマトリックス
	Mat4X4::Matrix	matWorld;




public:
	//追加
	//頂点バッファの作成の追加処理
	struct Box3DVertex
	{
		D3DXVECTOR3		pos;
		DWORD			color;
	};
#define Box3DVertexBuf (D3DFVF_XYZ | D3DFVF_DIFFUSE)

	LPDIRECT3DVERTEXBUFFER9		lpvb;

	void	VertexInit();
	void	VertexRender();
	


	//中心点の頂点
	struct Box3DPoint
	{
		D3DXVECTOR3		pos;
		DWORD			color;
	};

	LPDIRECT3DVERTEXBUFFER9		pointVB;

	void	PointInit();
	void	PointRender();
	void	SetMatrix(const D3DXVECTOR3& pos);
};