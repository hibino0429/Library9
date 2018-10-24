#pragma once
#include "../../../Library9/Function.h"

//�ǉ�---------------------
#include "Shot.h"

//�G2�N���X
class Enemy2
{
public:
	Enemy2();
	~Enemy2();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//�e�̐���s
	void	ShotCreate();

public:
	
	//�萔
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

	Sphere			hitBase;	//���̂̓����蔻��
};