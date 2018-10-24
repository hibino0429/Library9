#include "CameraMan.h"


//コンストラクタ
CameraMan::CameraMan()
{

}


//デストラクタ
CameraMan::~CameraMan()
{
	
}


//---------------------------------------------------------------------------
//初期化処理
//---------------------------------------------------------------------------
void	CameraMan::Initialize()
{
	camera.Initialize();


	this->pos = D3DXVECTOR3(0, 0, 0);
	this->angle = D3DXVECTOR3(0, 0, 0);
	this->size = D3DXVECTOR3(1, 1, 1);

	dist = 300.0f;
	viewPointHeight = +250.0f;
	pointOfGazeHeight = +150.0f;

	angleAxis = 0;
}



//---------------------------------------------------------------------------
//解放処理
//---------------------------------------------------------------------------
void	CameraMan::Finalize()
{
	
}



//---------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------
void	CameraMan::UpDate()
{
	//左右の旋回
	//if (keys[DIK_A] & 0x80) { this->angle.y += 2.0f; }
	//if (keys[DIK_S] & 0x80) { this->angle.y -= 2.0f; }

	angleAxis = 0;
	if (keys[DIK_A] & 0x80) { angleAxis = 1; }
	if (keys[DIK_S] & 0x80) { angleAxis = -1; }

	
	
	camera.UpDate();
}


//---------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------
void	CameraMan::Render()
{
	camera.Render();
}






//カメラの取得
void	CameraMan::GetPlayerPos(Player* player)
{
	//左右の旋回
	this->angle.y += player->turnSpeed * D3DXToRadian(30);

	D3DXVECTOR3		vec(0, 0, -dist);
	D3DXMATRIX		matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(this->angle.y));
	D3DXVec3TransformCoord(&vec, &vec, &matR);
	this->pos = player->model.pos + vec;

	//カメラの位置・向きの決定
	camera.SetTargetPos(player->model.pos + D3DXVECTOR3(0,+100,0));
	camera.SetPos(pos + D3DXVECTOR3(0, 300, 0));
}





//キーボードの入力を取得
void	CameraMan::GetKeyboard(char* key)
{
	this->keys = key;
}


//カメラマンの円周移動
void	CameraMan::CircleMove(Player* player)
{
	//左右の旋回
	this->angle.y += this->angleAxis * D3DXToRadian(30);

	D3DXVECTOR3		vec(0, 0, -dist);
	D3DXMATRIX		matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(this->angle.y));
	D3DXVec3TransformCoord(&vec, &vec, &matR);
	this->pos = player->model.pos + vec;


	//カメラの位置・向きの決定
	camera.SetTargetPos(player->model.pos + D3DXVECTOR3(0, +30, 0));
	camera.SetPos(this->pos + D3DXVECTOR3(0, 200, 0));
}


//ビューマトリックスを渡す
D3DXMATRIX	CameraMan::PassViewMatrix()
{
	return	this->camera.PassViewMatrix();
}

//プロジェクションマトリックスを渡す
D3DXMATRIX	CameraMan::PassProjMatrix()
{
	return	this->camera.PassProjMatrix();
}