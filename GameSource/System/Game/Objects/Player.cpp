#include "Player.h"


Player::Player()
{
	turnSpeed = 0.0f;
}

Player::~Player()
{
	Finalize();
}

//------------------------------------------------------------
//プレイヤーの初期化
//------------------------------------------------------------
void	Player::Initialize()
{

	this->key = 0;
	this->turnSpeed = 0.0f;
	this->speed = 0.0f;

	
	this->hitBox = Box3D(-30, -30, -30, 60, 60, 60);


	//モデルの読み込み
	model.Load(TEXT("./data/Model/Player/player1.x"));
	model.pos = D3DXVECTOR3(0, 80, 150);
	model.angle = D3DXVECTOR3(0, 0, 0);
	model.size = D3DXVECTOR3(10, 10, 10);


	polyBox.VertexInit();
	polyBox.PointInit();

	
	/*jump.LoadSound(TEXT("./data/Sound/jump.wav"));
	jump.SetVolume(50);
	shot.LoadSound(TEXT("./data/Sound/soundWave.wav"));
	shot.SetVolume(50);*/

	tex.Load("./data/Image/tex.bmp");
	font.Create("MS ゴシック", 12, 12);

	diffuseMap.Create();		//ディフューズマップの生成
}


//------------------------------------------------------------
//プレイヤーの解放
//------------------------------------------------------------
void	Player::Finalize()
{
	model.Erase();

	//jump.~Sounds();

	tex.Destroy();

	font.Destory();
}


//------------------------------------------------------------
//プレイヤーの更新
//------------------------------------------------------------
void	Player::UpDate()
{
	//カメラマンの旋回処理
	/*if (keys[DIK_A] & 0x80)
	{
		this->turnSpeed = -2.0f;
	}
	else if (keys[DIK_S] & 0x80)
	{
		this->turnSpeed = +2.0f;
	}
	else { this->turnSpeed = 0.0f; }*/


	//サウンド再生
	/*if (keys[DIK_B] & 0x80)
	{
		jump.Play(false);
	}

	if (keys[DIK_N] & 0x80)
	{
		shot.Play(false);
	}*/


}


//------------------------------------------------------------
//プレイヤーの描画
//------------------------------------------------------------
void	Player::Render()
{
	//ボックスの描画
	hitBox.Offset(model.pos);

	//ポリゴンボックスの描画
	polyBox.WorldMat(hitBox);
	polyBox.VertexRender();

	//ポリゴンポインとの描画
	polyBox.SetMatrix(D3DXVECTOR3(model.pos));
	polyBox.PointRender();

	model.size = D3DXVECTOR3(30, 30, 30);
	Matrix(model.pos, model.angle, model.size);
	
	diffuseMap.GetLightDir(lightDir);
	diffuseMap.GetLightColor(lightColor);
	diffuseMap.GetViewMatrix(&view);
	diffuseMap.GetProjMatrix(&proj);
	diffuseMap.GetWorldMatrix(&matW.mat);

	diffuseMap.Begin();
	diffuseMap.BeginPass();
	diffuseMap.SetShaderParam();
	model.Render();
	diffuseMap.EndPass();
	diffuseMap.End();

}

//Z値の描画
void	Player::ZRendere(ZTexture* zTex)
{
	Matrix(model.pos, model.angle, model.size);

	zTex->SetWorldMatrix(&matW.mat);
	model.ZTexRender(zTex);

}

//深度バッファ描画
void	Player::DepthRender(DepthTexture* depTex)
{
	Matrix(model.pos, model.angle, model.size);

	depTex->GetWorldMatrix(&matW.mat);
	model.DepthRender(depTex);


	//テクスチャ・フォントの描画
	font.Render("プレイヤー", Box2D(0, 0, 200, 10));
	tex.Render(Box2D(0, 0, 500, 500), Box2D(0, 0, 500, 500));
}


//マトリックス処理
void	Player::Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(model.angle.y), D3DXToRadian(model.angle.x), D3DXToRadian(model.angle.z));
	D3DXMatrixScaling(&mScale, model.size.x, model.size.y, model.size.z);

	matW.mat = mScale * mRot * mMove;
	matW.SetMatrix(D3DTS_WORLD);
}




//プレイヤーの生成
Player*	Player::Create(bool flag)
{
	if (!flag) { return NULL; }

	MessageBox(NULL, TEXT("プレイヤーの生成"), TEXT("Create"), MB_OK);

	return new Player;
}


//プレイヤーの破棄
void	Player::Destroy()
{	
	MessageBox(NULL, TEXT("プレイヤーの破棄"), TEXT("Destroy"), MB_OK);
	delete this;
}


//キーの取得
void Player::GetKey(int key)
{
	this->key = key;
}

void	Player::GetKeyboard(char* keys)
{
	this->keys = keys;
}



//あたり判定
bool	Player::Hit(D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	if ((this->model.pos.x < min->x) && (max->x < this->model.pos.x)) {
		if (this->model.pos.y < min->y && max->y < this->model.pos.y) {
			if (this->model.pos.z < min->z && max->z < this->model.pos.z) {
				return true;
			}
		}
	}
	
	return false;
}





//カメラマンの角度を取得
void	Player::GetCameraManAngle(CameraMan* cameraMan)
{

	D3DXVECTOR3 est(0, 0, 0);
	model.angle.y = cameraMan->angle.y + model.angle.y + 90;
	D3DXMATRIX	matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(model.angle.y));
	est.z = -1 * this->speed;
	D3DXVec3TransformCoord(&est, &est, &matR);
	
	model.pos += est;
}


//カメラマンの向きを取得
void	Player::GetCameraManAngle(D3DXVECTOR3& angle)
{
	this->cameraManAngle = angle;
}



//移動処理
void	Player::Move(Map* map)
{
	bool keyFlag = false;
	if (keys[DIK_LEFT] & 0x80) { this->speed = 3.0f; model.angle.y = 90; keyFlag = true; }
	if (keys[DIK_RIGHT] & 0x80) { this->speed = 3.0f; model.angle.y = 270; keyFlag = true; }
	if (keys[DIK_UP] & 0x80) { this->speed = 3.0f; model.angle.y = 180; keyFlag = true;}
	if (keys[DIK_DOWN] & 0x80) { this->speed = 3.0f; model.angle.y = 0; keyFlag = true;}


	//向きに応じた移動
	D3DXVECTOR3		est(0, 0, 0);
	if (keyFlag)
	{
		model.angle.y += cameraManAngle.y;
		D3DXMATRIX	matR;
		D3DXMatrixRotationY(&matR, D3DXToRadian(model.angle.y));
		est.z = -1.0f * this->speed;
		D3DXVec3TransformCoord(&est, &est, &matR);

	}
	//キー入力の移動処理
	this->speed = 0.0f;
	if (keys[DIK_Z] & 0x80) { model.pos.y += 1.0f; }
	if (keys[DIK_X] & 0x80) { model.pos.y -= 1.0f; }


	CheckMove(est, map);	//ブロックとの当たり判定

}



//めり込まない移動処理
void	Player::CheckMove(D3DXVECTOR3& est_,Map* map)
{
	//X軸に対して
	while (est_.x != 0.0f) {
		float preX = model.pos.x;

		if (est_.x >= 1.0f) { model.pos.x += 1.0f; est_.x -= 1.0f; }
		else if (est_.x <= -1.0f) { model.pos.x -= 1.0f; est_.x += 1.0f; }
		else { model.pos.x += est_.x; est_.x = 0.0f; }
		
		//当たり判定
		Box3D hitbase = hitBox.OffsetCopy(model.pos);
		if (map->CheckHit(hitbase))
		{
			model.pos.x = preX;
			break;
		}
	}

	//Z軸に対して
	while (est_.z != 0.0f) {
		float preZ = model.pos.z;

		if (est_.z >= 1.0f) { model.pos.z += 1.0f; est_.z -= 1.0f; }
		else if (est_.z <= -1.0f) { model.pos.z -= 1.0f; est_.z += 1.0f; }
		else { model.pos.z += est_.z; est_.z = 0.0f; }

		Box3D hitbase = hitBox.OffsetCopy(model.pos);
		if (map->CheckHit(hitbase))
		{
			model.pos.z = preZ;
			break;
		}
	}

	//Y軸に対して
	while (est_.y != 0.0f) {
		float preY = model.pos.y;

		if (est_.y >= 1.0f) { model.pos.y += 1.0f; est_.y -= 1.0f; }
		else if (est_.y <= -1.0f) { model.pos.y -= 1.0f; est_.y += 1.0f; }
		else { model.pos.y += est_.y; est_.y = 0.0f; }

		Box3D hitbase = hitBox.OffsetCopy(model.pos);
		if (map->CheckHit(hitbase))
		{
			model.pos.y = preY;
			break;
		}
	}
}



D3DXVECTOR3		Player::GetPos()
{
	return this->model.pos;
}





void	Player::GetLightInfo(Light* light)
{
	lightDir = light->direction;
	lightColor = (D3DXVECTOR3)light->diffuse;
}
void	Player::GetCameraInfo(CameraMan* cameraMan)
{
	view = cameraMan->PassViewMatrix();
	proj = cameraMan->PassProjMatrix();
}

