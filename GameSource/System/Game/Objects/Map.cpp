#include "Map.h"


//コンストラクタ
Map::Map() 
{
	D3DXMatrixIdentity(&matW.mat);
}


//--------------------------------------------------------------
//マップの初期化
//--------------------------------------------------------------
void	Map::Initialize()
{
	pos = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(100,10, 100);


	//モデルの読み込み-----------------------------
	ground.Load(TEXT("./data/Model/Map/map.x"));		//地面の読み込み
	block.Load(TEXT("./data/Model/Map/block.x"));		//壁の読み込み
	tree.Load(TEXT("./data/Model/Map/tree+.x"));		//木の読み込み
	house.Load(TEXT("./data/Model/Map/house.x"));		//家の読み込み
	stone.Load(TEXT("./data/Model/Map/stone.x"));		//石の読み込み
	

	//モデルの位置---------------------------------
	ground.pos = D3DXVECTOR3(0, 0, 0);
	ground.size = D3DXVECTOR3(1000, 10, 1000);
	block.pos = D3DXVECTOR3(500, 100, 300);
	block.size = D3DXVECTOR3(100, 100, 100);
	tree.pos = D3DXVECTOR3(300, 120, 200);
	tree.size = D3DXVECTOR3(30, 50, 30);
	house.pos = D3DXVECTOR3(-600, 100, -100);
	house.size = D3DXVECTOR3(100, 100, 100);
	stone.pos = D3DXVECTOR3(-400, 50, -400);
	stone.size = D3DXVECTOR3(50, 50, 50);
	stLight.Initialize();
	stLight.GetPos(D3DXVECTOR3(400, 10, -300));


	//モデルの当たり判定用ボックスの設定----------
	blockHitBox = Box3D(-100, -100, -100, 200, 200, 200);
	treeHitBox = Box3D(-30, -200, -30, 60, 400, 60);
	groundHitBox = Box3D(-500, -20, -500, 1000, 40, 1000);
	houseHitBox = Box3D(-70, -150, -100, 140, 200, 200);
	stoneHitBox = Box3D(-50, -50, -50, 100, 100, 100);
	stLightHitBox = Box3D(-30, -50, -30, 60, 100, 60);

	//モデルの当たり判定範囲のボックスの設定
	polyBox.WorldMat(treeHitBox);
	polyBox.VertexInit();
	
}



//--------------------------------------------------------------
//マップの解放
//--------------------------------------------------------------
void	Map::Finalize()
{

	//モデルの解放
	ground.Erase();
	block.Erase();
	tree.Erase();
	house.Erase();
	stone.Erase();
}


//--------------------------------------------------------------
//マップの更新
//--------------------------------------------------------------
void	Map::UpDate()
{
	stLight.UpDate();
}


//--------------------------------------------------------------
//マップの描画
//--------------------------------------------------------------
void	Map::Render()
{

	//ボックスの移動オフセット
	blockHitBox.Offset(block.pos);
	treeHitBox.Offset(tree.pos);
	groundHitBox.Offset(ground.pos);
	houseHitBox.Offset(house.pos);
	stoneHitBox.Offset(stone.pos);

	//地面の描画
	this->WorldMatrix(ground.pos, ground.angle, ground.size);
	ground.Render();

	//ブロックの描画
	this->WorldMatrix(block.pos, block.angle, block.size);
	block.Render();

	//木の描画
	this->WorldMatrix(tree.pos, tree.angle, tree.size);
	tree.Render();

	//家の描画
	this->WorldMatrix(house.pos, house.angle, house.size);
	house.Render();

	//石の描画
	this->WorldMatrix(stone.pos, stone.angle, stone.size);
	stone.Render();

	//街灯の描画
	stLight.Render();

	//ポリゴンボックスの表示
	polyBox.WorldMat(treeHitBox);
	polyBox.VertexRender();
}



//Z値テクスチャの描画
void	Map::ZTexRender(ZTexture* zTex)
{
	//ボックスの移動オフセット
	blockHitBox.Offset(block.pos);
	treeHitBox.Offset(tree.pos);
	groundHitBox.Offset(ground.pos);
	houseHitBox.Offset(house.pos);
	stoneHitBox.Offset(stone.pos);

	WorldMatrix(ground.pos, ground.angle, ground.size);
	zTex->SetWorldMatrix(&matW.mat);
	ground.ZTexRender(zTex);

	WorldMatrix(block.pos, block.angle, block.size);
	zTex->SetWorldMatrix(&matW.mat);
	block.ZTexRender(zTex);

	WorldMatrix(tree.pos, tree.angle, tree.size);
	zTex->SetWorldMatrix(&matW.mat);
	tree.ZTexRender(zTex);

	WorldMatrix(house.pos, house.angle, house.size);
	zTex->SetWorldMatrix(&matW.mat);
	house.ZTexRender(zTex);

	WorldMatrix(stone.pos, stone.angle, stone.size);
	zTex->SetWorldMatrix(&matW.mat);
	stone.ZTexRender(zTex);

}

//Depthテクスチャの描画
void	Map::DepthRender(DepthTexture* depTex)
{
	WorldMatrix(ground.pos, ground.angle, ground.size);
	depTex->GetWorldMatrix(&matW.mat);
	ground.DepthRender(depTex);

	WorldMatrix(block.pos, block.angle, block.size);
	depTex->GetWorldMatrix(&matW.mat);
	block.DepthRender(depTex);

	WorldMatrix(tree.pos, tree.angle, tree.size);
	depTex->GetWorldMatrix(&matW.mat);
	tree.DepthRender(depTex);

	WorldMatrix(house.pos, house.angle, house.size);
	depTex->GetWorldMatrix(&matW.mat);
	house.DepthRender(depTex);

	WorldMatrix(stone.pos, stone.angle, stone.size);
	depTex->GetWorldMatrix(&matW.mat);
	stone.DepthRender(depTex);
}



//マップの位置
void	Map::SetPos(D3DXVECTOR3& pos)
{
	this->pos = pos;
}

//マップのアングル
void	Map::SetAngle(D3DXVECTOR3& angle)
{
	this->angle = angle;
}

//マップのサイズ
void	Map::SetSize(D3DXVECTOR3& size)
{
	this->size = size;
}


//かめらの位置を取得する
void	Map::GetCameraPos(Camera* camera)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;
	
	D3DXVECTOR3 dir = pos - camera->GetTarget();	//視線

	//平行移動
	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	//回転
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(-atanf(dir.y / dir.z)), D3DXToRadian(angle.z));
	//拡大縮小
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	//行列の合成
	matW.mat = mScale * mRot * mMove;


	//視線ベクトルを正規化し向きを取得
	D3DXVec3Normalize(&dir, &dir);	//向きを取得

	//外積の計算
	//外積を利用して平面が面(ビルボード)に対して垂直のベクトルを取得

}



//ワールドマトリックス
void	Map::WorldMatrix(D3DXVECTOR3& pos,D3DXVECTOR3& angle,D3DXVECTOR3& size)
{
	D3DXMATRIX		mMove;
	D3DXMATRIX		mRot;
	D3DXMATRIX		mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	matW.mat = mScale * mRot * mMove;
	matW.SetMatrix(D3DTS_WORLD);
}









//-------------------------------------------------------
//マップとの当たり判定
//-------------------------------------------------------
bool	Map::CheckHit(Box3D& object)
{
	//マップのボックスと取得したボックスとの当たり判定
	//ブロックとの当たり判定
	if (blockHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("ブロックと衝突しました"), TEXT("ブロック"), MB_OK);
		return true;
	}
	//木との当たり判定
	if (treeHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("木と衝突しました"), TEXT("木"), MB_OK);
		return true;
	}
	//地面との当たり判定
	//if (groundHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("地面と衝突しました"), TEXT("地面"), MB_OK);
	//	return true;
	}
	//家との当たり判定
	if (houseHitBox.Hit(object))
	{
		return true;
	}
	//石との当たり判定
	if (stoneHitBox.Hit(object))
	{
		return true;
	}
	//街灯との当たり判定
	if (stLight.hitBox.Hit(object))
	{
		return true;
	}
	return false;
}