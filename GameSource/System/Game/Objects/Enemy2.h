#pragma once
#include "../../../Library9/Function.h"

//追加---------------------
#include "Shot.h"

//敵2クラス
class Enemy2
{
public:
	Enemy2();
	~Enemy2();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//弾の生成s
	void	ShotCreate();

public:
	
	//定数
	static const int MaxShot = 10;

private:
	XFile::ModelX	model;
	Mat4X4::Matrix	world;

	Text::Font		font;

public:
	Shot::Object	shot[MaxShot];

public:
	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	float			shotCnt;
	float			moveCnt;

	Sphere			hitBase;	//球体の当たり判定
};