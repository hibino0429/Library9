#include "Enemy2.h"

#include <stdio.h>

//�R���X�g���N�^
Enemy2::Enemy2()
{
	D3DXMatrixIdentity(&world.mat);
}

//�f�X�g���N�^
Enemy2::~Enemy2()
{
	Finalize();
}


//-------------------------------------------------------------------
//����������
//-------------------------------------------------------------------
void	Enemy2::Initialize()
{
	this->pos = D3DXVECTOR3(0, 0, 50);
	this->angle = D3DXVECTOR3(0, 180, 0);
	this->size = D3DXVECTOR3(3, 10, 10);

	this->shotCnt = 0;
	this->moveCnt = 0;


	this->hitBase = Sphere(this->pos, 30.0f);

	//���f���̓ǂݍ���
	model.Load(TEXT("./data/Model/Enemy/enemy2.x"));

	//�t�H���g�̐���
	font.Create(TEXT("MS �S�V�b�N"), 16, 16);
}


//--------------------------------------------------------------------
//�������
//--------------------------------------------------------------------
void	Enemy2::Finalize()
{
	model.Erase();

	font.Destory();
}


//--------------------------------------------------------------------
//�X�V����
//--------------------------------------------------------------------
void	Enemy2::UpDate()
{

	//�e�̐�������
	shotCnt++;
	int randam = rand() % 50 - 20;
	if (shotCnt >= 180 + randam)
	{
		this->ShotCreate();
		this->shotCnt = 0;
	}

	//�e�̍X�V����
	for (int i = 0; i < 10; ++i)
	{
		if (shot[i].state != shot[i].NONE)
		{
			shot[i].UpDate();
		}
	}


	this->hitBase = Sphere(this->pos, 15.0f);

	//�G2�̈ړ�����
	this->moveCnt++;
	if (moveCnt <= 120)
	{
		this->pos.x += 0.5f;
	}
	else if (moveCnt <= 240)
	{
		this->pos.x -= 0.5f;
	
	}
	else
	{
		this->moveCnt = 0;
	}

	
}


//--------------------------------------------------------------------
//�`�揈��
//--------------------------------------------------------------------
void	Enemy2::Render()
{
	//�V�[���̃N���A
	LibDGD::ZBufClear();

	//�}�g���b�N�X����
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;

	world.SetMatrix(D3DTS_WORLD);

	model.Render();

	//�e�̕`�揈��
	for (int i = 0; i < 10; ++i)
	{
		if (shot[i].state != shot[i].NONE)
		{
			shot[i].Render();
		}
	}


	//�t�H���g�̕`��
	font.Render(TEXT("�G2"), Box2D(500, 0, 500, 300), D3DXCOLOR(1, 1, 1, 1));
}





//�e�̐���
void	Enemy2::ShotCreate()
{
	for (int i = 0; i < 10; i++)
	{
		if (shot[i].state == shot[i].NONE)
		{
			shot[i].Initialize();
			shot[i].pos = this->pos;
			shot[i].moveVec = D3DXVECTOR3(0, 0, -1.0f);
			shot[i].angle = D3DXVECTOR3(90,180,0);
			break;
		}
	}
}