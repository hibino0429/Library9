#pragma once
#include "../../../Library9/Function.h"

//’Ç‰Á---------------------
#include "Shot.h"

//“G2ƒNƒ‰ƒX
class Enemy2
{
public:
	Enemy2();
	~Enemy2();

	//Šî–{ˆ—
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//’e‚Ì¶¬s
	void	ShotCreate();

public:
	
	//’è”
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

	Sphere			hitBase;	//‹…‘Ì‚Ì“–‚½‚è”»’è
};