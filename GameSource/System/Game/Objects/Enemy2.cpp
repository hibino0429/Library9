#include "Enemy2.h"

#include <stdio.h>

//コンストラクタ
Enemy2::Enemy2()
{
	D3DXMatrixIdentity(&world.mat);
}

//デストラクタ
Enemy2::~Enemy2()
{
	Finalize();
}


//-------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------
void	Enemy2::Initialize()
{
	this->pos = D3DXVECTOR3(0, 0, 50);
	this->angle = D3DXVECTOR3(0, 180, 0);
	this->size = D3DXVECTOR3(3, 10, 10);

	this->shotCnt = 0;
	this->moveCnt = 0;


	this->hitBase = Sphere(this->pos, 30.0f);

	//モデルの読み込み
	model.Load(TEXT("./data/Model/Enemy/enemy2.x"));

	//フォントの生成
	font.Create(TEXT("MS ゴシック"), 16, 16);
}


//--------------------------------------------------------------------
//解放処理
//--------------------------------------------------------------------
void	Enemy2::Finalize()
{
	model.Erase();

	font.Destory();
}


//--------------------------------------------------------------------
//更新処理
//--------------------------------------------------------------------
void	Enemy2::UpDate()
{

	//弾の生成処理
	shotCnt++;
	int randam = rand() % 50 - 20;
	if (shotCnt >= 180 + randam)
	{
		this->ShotCreate();
		this->shotCnt = 0;
	}

	//弾の更新処理
	for (int i = 0; i < 10; ++i)
	{
		if (shot[i].state != shot[i].NONE)
		{
			shot[i].UpDate();
		}
	}


	this->hitBase = Sphere(this->pos, 15.0f);

	//敵2の移動処理
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
//描画処理
//--------------------------------------------------------------------
void	Enemy2::Render()
{
	//シーンのクリア
	LibDGD::ZBufClear();

	//マトリックス処理
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;

	world.SetMatrix(D3DTS_WORLD);

	model.Render();

	//弾の描画処理
	for (int i = 0; i < 10; ++i)
	{
		if (shot[i].state != shot[i].NONE)
		{
			shot[i].Render();
		}
	}


	//フォントの描画
	font.Render(TEXT("敵2"), Box2D(500, 0, 500, 300), D3DXCOLOR(1, 1, 1, 1));
}





//弾の生成
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