#pragma once
#include "../Function.h"


//-----------------------------------------------------------------------------------------
//2Dボックス
//-----------------------------------------------------------------------------------------
class Box2D
{
public:
	Box2D();							//コンストラクタ
	Box2D(float,float,float,float);		//引数付きコンストラクタ

	//当たり判定
	bool	Hit(Box2D);	
	Box2D	OffSetCopy(D3DXVECTOR2& pos);		//オフセットのコピー
	void	OffSet(D3DXVECTOR2& pos);			//オフセット

public:
	float x, y;
	float sizeX, sizeY;
};



//----------------------------------------------------------------------------------------
//float型のボックスを作成
//3Dボックス
//----------------------------------------------------------------------------------------
class Box3D
{
public:
	Box3D();
	Box3D(float, float, float, float, float, float);
	~Box3D();

	//当たり判定
	bool	Hit(Box3D&);
	bool	HitCheck(Box3D&);

	//オフセット
	void	Offset(const D3DXVECTOR3&);
	Box3D	OffsetCopy(const D3DXVECTOR3&);


public:
	float	x, y, z;
	float	sizeX, sizeY, sizeZ;
	D3DXVECTOR3	minB;
	D3DXVECTOR3	maxB;


};




//----------------------------------------------------------
//球体
//----------------------------------------------------------
class Sphere
{
public:
	Sphere();
	Sphere(D3DXVECTOR3& pos, float r);

	//距離を求める
	float	ObjDirection(Sphere&);	//オブジェクト間の距離2乗
	float	rDirection(Sphere&);	//半径の距離の2乗

	//当たり判定
	bool	Hit(Sphere&);

public:
	D3DXVECTOR3		pos;	//位置
	float			r;		//半径
};


//----------------------------------------------------
//レイクラス
//----------------------------------------------------
class Ray
{
public:
	Ray();
	Ray(D3DXVECTOR2& start, D3DXVECTOR2& vec);

	//判定処理
	bool			ZeroVector();		//ベクトルが0かどうかを調べる

										//取得処理
	D3DXVECTOR2		GetStartPos();		//始点の取得処理
	D3DXVECTOR2		GetDirVector();		//方向ベクトルの取得処理

										//自分自身の処理
	void			Normalize();		//正規化
	float			Dot(const D3DXVECTOR2& pos, const D3DXVECTOR2& vec);	//内積
	float			Length(const D3DXVECTOR2& pos);			//大きさ

private:
	D3DXVECTOR2		startPos;		//始点
	D3DXVECTOR2		dirVector;		//方向ベクトル

};



//---------------------------------------------------
//円クラス
//---------------------------------------------------
class Circle
{
public:
	Circle();
	Circle(D3DXVECTOR2& pos, float rad);

	//円とレイとの衝突判定
	bool	HitRay(Ray* ray);

private:
	D3DXVECTOR2		center;	//中心点
	float			radius;	//半径

	D3DXVECTOR2		nearColPos;		//近い衝突座標
	D3DXVECTOR2		farColPos;		//遠い衝突座標
};



