#pragma once
#include "../../../Library9/Function.h"
#include "Shot.h"


//---------------------------------
//�n�_�|�C���g�N���X
//---------------------------------
class	Point
{
public:
	D3DXVECTOR3		pos;
	Box3D			hitBox;

public:

	//��{����
	void	Initliaze();
	void	Finalize();
	void	UpDate();
	void	Render();

	D3DXVECTOR3		SendPos();
	void			ReceivePos(D3DXVECTOR3& pos);
};




//�G1�N���X
class Enemy
{
public:
	Enemy();
	~Enemy();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//���C�t�����炷
	void	LifeDecrease();


	//�G�̏��񏈗�
	void	Patrol();

	//�G�̒ǐՏ���
	void	Chase();
	bool	SearchAngle();	//���E�ɓ����Ă��邩
	
	void	GetPos(D3DXVECTOR3& pos);	//�ʒu�̎擾

public:

	//�萔
	static const int		MaxShot = 5;

public:
	XFile::ModelX	model;	//�{��

	Text::Font		enemyLifeFont;	//���C�t�\���p

	Mat4X4::Matrix	matW;


public:

	Point			point[10];		//�n�_

	//�ϐ�
	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	float			shotCnt;
	float			moveCnt;
	
	int				life;

	bool			active;
	bool			setPoint;
	int				randPoint;


	//�ǉ�
	D3DXVECTOR3		playerPos;
	D3DXVECTOR3		moveVec;
	float			searchAngle;
	float			searchDist;
};



