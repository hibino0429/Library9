#pragma once
#include "../../../Library9/Function.h"

//”š”­ƒNƒ‰ƒX
class Explode
{
public:
	Explode();
	~Explode();

	//Šî–{ˆ—
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