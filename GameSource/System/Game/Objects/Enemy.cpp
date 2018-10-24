#include "Enemy.h"

#include <string>


Enemy::Enemy()
{
	D3DXMatrixIdentity(&matW.mat);
}

Enemy::~Enemy()
{
	Finalize();
}


//敵の初期化
void	Enemy::Initialize()
{
	model.Load(TEXT("./data/Model/Enemy/enemy1.x"));

	enemyLifeFont.Create(TEXT("MS ゴシック"), 16, 16);

	model.pos = D3DXVECTOR3(0, 10, 100);
	model.angle = D3DXVECTOR3(0, 0, 0);
	model.size = D3DXVECTOR3(100, 100, 100);

	this->moveCnt = 0.0f;
	this->shotCnt = 0.0f;

	this->life = 10;

	this->active = true;

	point[0].pos = D3DXVECTOR3(100, 10, 10);
	point[1].pos = D3DXVECTOR3(200, 10, -40);
	point[2].pos = D3DXVECTOR3(-20, 10, -100);
	point[3].pos = D3DXVECTOR3(-400, 10, 200);
	point[4].pos = D3DXVECTOR3(50, 10, -500);
	point[5].pos = D3DXVECTOR3(-200, 10, 300);
	point[6].pos = D3DXVECTOR3(300, 10, 100);
	point[7].pos = D3DXVECTOR3(-600, 10, 100);
	point[8].pos = D3DXVECTOR3(0, 10, -300);
	point[9].pos = D3DXVECTOR3(70, 10, 500);
	
	setPoint = true;
	randPoint = 6;

	playerPos = D3DXVECTOR3(0, 0, 0);
	moveVec = D3DXVECTOR3(0, 0, 0);
	searchAngle = D3DXToRadian(120/2);
	searchDist = 30;
}

void	Enemy::Finalize()
{
	model.Erase();

	enemyLifeFont.Destory();

}

void	Enemy::UpDate()
{
	this->Chase();
}


void	Enemy::Render()
{

	//モデルの描画
	D3DXMATRIX		mMove;
	D3DXMATRIX		mRot;
	D3DXMATRIX		mScale;

	D3DXMatrixTranslation(&mMove, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(model.angle.y), D3DXToRadian(model.angle.x), D3DXToRadian(model.angle.z));
	D3DXMatrixScaling(&mScale, model.size.x, model.size.y, model.size.z);

	matW.mat = mScale * mRot * mMove;

	matW.SetMatrix(D3DTS_WORLD);

	model.Render();


	enemyLifeFont.Render(TEXT("敵1"), Box2D(0, 0, 100, 100), D3DXCOLOR(1, 1, 1, 1));
}





//ダメージ処理
void	Enemy::LifeDecrease()
{
	if (this->life > 0)
	{
		this->life--;
	}
}



//敵の巡回処理
void	Enemy::Patrol()
{
	//敵の更新
	if (setPoint) {
		randPoint = rand() % 10;
		setPoint = false;
	}
	//1:地点の位置と敵の位置のベクトルを算出
	D3DXVECTOR3	vec = point[randPoint].pos - model.pos;
	//2:ベクトルの距離を保存しておき、その方向(angle)へ移動させる

	//ベクトルから角度を得る
	float angle = atan2(vec.z, vec.x);
	//その角度へ移動
	model.pos.x += cos(angle) * 1;
	model.pos.z += sin(angle) * 1;

	//3:ベクトルの距離が、30距離未満になったら、次の地点へのランダム位置を求める
	float dist = vec.x * vec.x + vec.z * vec.z;

	if (dist <= 30 && !setPoint)
	{
		setPoint = true;
	//	MessageBox(NULL, TEXT("次の地点へ進みます"), TEXT("Let's　Go"), MB_OK);
	}

}


//敵の追跡処理
void	Enemy::Chase()
{
	if (this->SearchAngle())
	{
		this->moveVec = D3DXVECTOR3(cos(this->angle.y), 0, sin(this->angle.y)) * 10.0f;
	}
	else
	{
		//Patrol();
	}
}


//位置の取得
void		Enemy::GetPos(D3DXVECTOR3& pos)
{
	this->playerPos = pos;
}

//視野角内かを調べる
bool		Enemy::SearchAngle()
{
	//敵の視野にプレイヤーが入ったか、確認する

	//1:外積を利用して、左右判定をする
	//外積の計算は、x1y2 - x2y1
	//外積の計算結果は、
	float cross = 0.0f;

	//敵からプレイヤーへの距離
	//D3DXVECTOR3	toTarget = model.pos - playerPos;	//距離
	D3DXVECTOR3	toTarget = playerPos - model.pos;
													//視野角範囲にいるターゲットを対象にする
	float	dist = toTarget.x * toTarget.x + toTarget.z * toTarget.z;

	if (dist < searchDist * searchDist)
	{
		D3DXVECTOR3	toTargetN;
		D3DXVec3Normalize(&toTargetN, &toTarget);	//正規化
		D3DXVECTOR3		moveVecN = D3DXVECTOR3(cos(this->angle.y), 0, sin(this->angle.y));

		//内積で左右どちらかの判定
		float dot = moveVecN.x * moveVecN.x + moveVecN.z * moveVecN.z;
		//視野角が視野角範囲より大きい場合
		if (dot > cos(searchAngle)) {
			//移動の調節
			if (dot > cos(D3DXToRadian(4))) {
				
			//MessageBox(NULL, TEXT("追跡中"), TEXT("now chase"), MB_OK);
			}
			else {
				float cr = moveVecN.x * toTargetN.z - moveVecN.z * toTargetN.x;
				//左右に合わせて旋回する
				if (cr >= 0) { this->angle.y += D3DXToRadian(4); }
				else { this->angle.y -= D3DXToRadian(4); }
				MessageBox(NULL, TEXT("つい積します"), TEXT("やったーー"), MB_OK);
				return true;
			}
		}
	}
	return false;
}




//地点の処理
D3DXVECTOR3		Point::SendPos()
{
	return this->pos;
}

void			Point::ReceivePos(D3DXVECTOR3& pos)
{
	this->pos = pos;
}




