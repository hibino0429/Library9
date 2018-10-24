#include "Explode.h"

//コンストラクタ
Explode::Explode() : active(false)
{
	D3DXMatrixIdentity(&world.mat);
}

//デストラクタ
Explode::~Explode()
{
	this->Finalize();
}




//----------------------------------------------------------------------------
//初期化処理
//----------------------------------------------------------------------------
void	Explode::Initialize()
{
	//仮
	//this->pos = D3DXVECTOR3(0, 0, 0);	
	//this->angle = D3DXVECTOR3(0, 0, 0);
	//this->size = D3DXVECTOR3(5, 5, 5);

	this->timeCnt = 0.0f;
	this->active = true;


	//モデルの読み込み
	model.Load(TEXT("explodeX.x"));

}

//----------------------------------------------------------------------------
//解放処理
//----------------------------------------------------------------------------
void	Explode::Finalize()
{
	model.Erase();
}


//----------------------------------------------------------------------------
//更新処理
//----------------------------------------------------------------------------
void	Explode::UpDate()
{
	if (!this->active) { return; }

	//仮
	this->timeCnt++;
	if (timeCnt >= 180) { this->active = false; this->timeCnt = 0; }
	

	//this->timeCnt++;
	//if (timeCnt > 120.0f) { this->active = false; this->timeCnt = 0; }
	//this->angle.y++;

	//if (timeCnt <= 60.0f)
	//{
	//	//MessageBox(NULL, TEXT("拡大します"), TEXT("UpDate"), MB_OK);
	//	this->size.x += 1.0f;
	//	this->size.y += 1.0f;
	//	this->size.z += 1.0f;
	//}
	//else if (timeCnt <= 120.0f)
	//{
	//	//MessageBox(NULL, TEXT("縮小します"), TEXT("UpDate"), MB_OK);
	//	this->size.x -= 1.0f;
	//	this->size.y -= 1.0f;
	//	this->size.z -= 1.0f;
	//}

}


//----------------------------------------------------------------------------
//描画処理
//----------------------------------------------------------------------------
void	Explode::Render()
{
	if (!this->active) { return; }

	//sceneのクリア
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
}



