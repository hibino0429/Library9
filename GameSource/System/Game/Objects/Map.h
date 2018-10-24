#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Camera.h"
#include "../../../Library9/Model/PolygonBox.h"
#include "../Objects/StreetLight.h"


//----------------------------------------------------------------------------------------
//マップ
//----------------------------------------------------------------------------------------
class Map
{
public:

	Map();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//マトリックス処理
	void	WorldMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);


	//位置の設定
	void	SetPos(D3DXVECTOR3&);
	void	SetAngle(D3DXVECTOR3&);
	void	SetSize(D3DXVECTOR3&);


	//カメラの位置を取得する
	void	GetCameraPos(Camera* camera);

	//マップとの当たり判定
	bool	CheckHit(Box3D& object);



public:

	Texture2::Image	image;	//画像
	Text::Font		font;	//フォント

	VertexBuf::Billboard	bill;	//頂点バッファ
	Mat4X4::Matrix			matW;	//マトリックス


	//マップにあるオブジェクト
	Model	ground;	//マップ
	Model	block;	//ボックス
	Model	tree;	//木のオブジェクト
	Model	house;	//家のオブジェクト
	Model	stone;	//石のオブジェクト
	StreetLight		stLight;//街灯オブジェクト


	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);

public:

	//モデルの当たり判定
	Box3D					blockHitBox;	//岩の当たり判定ボックス
	Box3D					treeHitBox;		//木の当たり判定ボックス
	Box3D					groundHitBox;	//地面の当たり判定ボックス
	Box3D					houseHitBox;	//家の当たり判定ボックス
	Box3D					stoneHitBox;	//石の当たり判定ボックス
	Box3D					stLightHitBox;	//街灯オブジェクト当たり判定ボックス

	//モデルの当たり判定範囲
	PolyBox					polyBox;		

public:
	//マップの情報
	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	D3DXMATRIX		Inv;	//逆行列用マトリックス
};