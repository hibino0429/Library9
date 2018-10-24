#pragma once
#include "../../../Library9/Function.h"
#include "Shot.h"


//---------------------------------
//地点ポイントクラス
//---------------------------------
class	Point
{
public:
	D3DXVECTOR3		pos;
	Box3D			hitBox;

public:

	//基本処理
	void	Initliaze();
	void	Finalize();
	void	UpDate();
	void	Render();

	D3DXVECTOR3		SendPos();
	void			ReceivePos(D3DXVECTOR3& pos);
};




//敵1クラス
class Enemy
{
public:
	Enemy();
	~Enemy();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//ライフを減らす
	void	LifeDecrease();


	//敵の巡回処理
	void	Patrol();

	//敵の追跡処理
	void	Chase();
	bool	SearchAngle();	//視界に入っているか
	
	void	GetPos(D3DXVECTOR3& pos);	//位置の取得

public:

	//定数
	static const int		MaxShot = 5;

public:
	XFile::ModelX	model;	//本体

	Text::Font		enemyLifeFont;	//ライフ表示用

	Mat4X4::Matrix	matW;


public:

	Point			point[10];		//地点

	//変数
	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	float			shotCnt;
	float			moveCnt;
	
	int				life;

	bool			active;
	bool			setPoint;
	int				randPoint;


	//追加
	D3DXVECTOR3		playerPos;
	D3DXVECTOR3		moveVec;
	float			searchAngle;
	float			searchDist;
};



