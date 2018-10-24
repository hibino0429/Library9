#include "StreetLight.h"


//-----------------------------------------------------
//コンストラクタ
//-----------------------------------------------------
StreetLight::StreetLight()
{
	D3DXMatrixIdentity(&world.mat);
}

//-----------------------------------------------------
//デストラクタ
//-----------------------------------------------------
StreetLight::~StreetLight()
{
	this->Finalize();
}


//------------------------------------------------------
//初期化処理
//------------------------------------------------------
void	StreetLight::Initialize()
{
	//変数の初期化
	frameCnt = 0.0f;
	timeCnt = 0.0f;
	hitBox = Box3D(-30, 0, -30, 60, 500, 60);

	//街灯オブジェクトの設定
	streetLight.Load(TEXT("./data/Model/Map/streetLight.x"));
	streetLight.pos = D3DXVECTOR3(0, 0, 0);
	streetLight.angle = D3DXVECTOR3(0, 0, 0);
	streetLight.size = D3DXVECTOR3(30, 30, 30);


	//ライトの設定
	light.SetNumber(5);
	light.SetUse(true);
	//ポイントライト
	//必要なもの
	//タイプ・位置・光の有効距離・光の減衰・ディフューズ色, (スペキュラー色)
	light.SetType(D3DLIGHT_POINT);
	light.SetDiffuse(D3DXCOLOR(1.0f, 0.2f, 0, 1));
	light.SetDiffuse(D3DXCOLOR(0.0f, 0.2f, 0.8f, 1));
	light.SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	light.SetPosition(D3DXVECTOR3(-300, 10, 0));
	light.SetAttenuation((1.0f / 2000.0f) * (1.0f / 2000.0f));
	light.SetRange(750.0f);

	light.Initalize();
}


//-------------------------------------------------------
//解放処理
//-------------------------------------------------------
void	StreetLight::Finalize()
{
	streetLight.Erase();

	light.SetUse(false);
}


//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void	StreetLight::UpDate()
{
	frameCnt++;
	int randam = 0;
	if (frameCnt >= 10.0f)
	{
		frameCnt = 0;
		randam = rand() % 20;
		timeCnt += 1 + randam;
	}
	if (timeCnt >= 60.0f)
	{
		timeCnt = 2.0f + randam;
	}
}


//--------------------------------------------------------
//描画処理
//--------------------------------------------------------
void	StreetLight::Render()
{
	hitBox.Offset(streetLight.pos);
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, streetLight.pos.x, streetLight.pos.y, streetLight.pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, 
		D3DXToRadian(streetLight.angle.y), 
		D3DXToRadian(streetLight.angle.x), 
		D3DXToRadian(streetLight.angle.z));
	D3DXMatrixScaling(&mScale, streetLight.size.x, streetLight.size.y, streetLight.size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);

	streetLight.Render();

	//ライト
	light.SetAttenuation((sinf(2.0f * 3.14f / 180.0f * (timeCnt)) + 0.02f) * ((1.0f / 2000.0f) * (1.0f / 2000.0f)));
	light.SetPosition(D3DXVECTOR3(streetLight.pos.x,streetLight.pos.y + 50,streetLight.pos.z));
	light.Initalize();
}






//--------------------------------
//街灯の位置を取得
void	StreetLight::GetPos(const D3DXVECTOR3& pos)
{
	streetLight.pos = pos;
}

//--------------------------------
//使用するライトのセット
void	StreetLight::SetUseLight(int number)
{
	light.SetNumber(number);
}