#pragma once
#include "../../../Library9/Function.h"

//爆発クラス
class Explode
{
public:
	Explode();
	~Explode();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


public:

	XFile::ModelX	model;
	Mat4X4::Matrix	world;

	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

public:

	float			timeCnt;
	bool			active;
};