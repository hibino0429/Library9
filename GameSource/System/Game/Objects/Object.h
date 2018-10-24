#pragma once

//使用する機能------------------------------------------
#include "../../../Library9/Function.h"

#include "../../../Library9/Model/Model.h"
#include "../../ShaderSystem/ZTexture.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/NormalMap.h"
//------------------------------------------------------
//オブジェクトの共通クラス
//------------------------------------------------------
class Object
{
public:

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


public:


	//マトリックス処理
	//引数1:位置
	//引数2:向き
	//引数3:サイズ
	void	Matrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

	//当たり判定処理
	//引数1:Box3Dのボックス
	bool	CheckHit(Box3D& box);

public:

	Box3D	hitBox;				//ボックス
	Mat4X4::Matrix	matWorld;	//ワールドマトリックス
public:
	Model	myObject;

	//ノーマルマップ
	NormalMap	normalMap;

	//シェーダの処理
public:
	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);


public:
	//取得処理
	void	GetMatrix(D3DXMATRIX* mat, D3DXMATRIX* getmat);		//マトリックス
	void	GetVector4(D3DXVECTOR4* vec, D3DXVECTOR4* getvec);	//位置・ベクトル
};