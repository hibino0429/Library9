#include "Sample.h"

//コンストラクタ
Samp::Samp() 
{
	D3DXMatrixIdentity(&world.mat);
}

//デストラクタ
Samp::~Samp()
{

}



//-----------------------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------------------
void	Samp::Initialize()
{



	//ワールド空間の座標を示す矢印
	Arrow.Load(TEXT("./data/Model/Map/arrow.x"));
	Arrow.pos = D3DXVECTOR3(0, 0, 0);
	Arrow.angle = D3DXVECTOR3(0, 0, 0);
	Arrow.size = D3DXVECTOR3(30, 30, 30);


	//炎
	fire.Load(TEXT("./data/Model/Map/fire4.x"));
	fire.pos = D3DXVECTOR3(-300, 0, 0);
	fire.angle = D3DXVECTOR3(0, 0, 0);
	fire.size = D3DXVECTOR3(30, 30, 30);

	hitModel = Box3D(-20, -60, -20, 40, 120, 40);

	//ライトの設定
	light.SetNumber(3);
	light.SetUse(true);
	//ポイントライト
	//必要なもの
	//タイプ・位置・光の有効距離・光の減衰・ディフューズ色, (スペキュラー色)
	light.SetType(D3DLIGHT_POINT);
	light.SetDiffuse(D3DXCOLOR(1.0f, 0.2f, 0, 1));
	light.SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	light.SetPosition(D3DXVECTOR3(fire.pos.x, fire.pos.y + 20, fire.pos.z));
	light.SetPosition(D3DXVECTOR3(-300, 10, 0));
	light.SetAttenuation((1.0f / 2000.0f) * (1.0f / 2000.0f));
	light.SetRange(750.0f);

	light.Initalize();

	frameCnt = 0.0f;
	timeCnt = 0.0f;



	//街灯
	streetLight.Initialize();
	streetLight.GetPos(D3DXVECTOR3(300, 0, -20));


}


//解放処理
void	Samp::Finalize()
{

	Arrow.Erase();
	fire.Erase();

	light.SetUse(false);

}


//-----------------------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------------------
void	Samp::UpDate()
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

	//街灯
	streetLight.UpDate();

}


//-----------------------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------------------
void	Samp::Render()
{

	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	Arrow.Render();


	Matrix(fire.pos, fire.angle, fire.size);
	fire.Render();
	
	//ライト
	light.SetAttenuation((sinf(2 * 3.14f/180 * (timeCnt)) + 0.02f) * ((1.0f / 2000.0f) * (1.0f / 2000.0f)));
	light.Initalize();


	//街灯
	streetLight.Render();

	hitModel.Offset(fire.pos);

	
}



//Z値テクスチャの描画
void	Samp::ZTexRender(ZTexture* zTex)
{
	//矢印のオブジェクト
	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	zTex->SetWorldMatrix(&world.mat);
	Arrow.ZTexRender(zTex);

	//炎のオブジェクト
	Matrix(fire.pos, fire.angle, fire.size);
	zTex->SetWorldMatrix(&world.mat);
	fire.ZTexRender(zTex);
}

void	Samp::DepthRender(DepthTexture* depTex)
{
	//矢印のオブジェクト
	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	depTex->GetWorldMatrix(&world.mat);
	Arrow.DepthRender(depTex);

	//炎のオブジェクト
	Matrix(fire.pos, fire.angle, fire.size);
	depTex->GetWorldMatrix(&world.mat);
	fire.DepthRender(depTex);

	//ライト
	light.SetAttenuation((sinf(2 * 3.14f / 180 * (timeCnt)) + 0.02f) * ((1.0f / 2000.0f) * (1.0f / 2000.0f)));
	light.Initalize();
}



//マトリックス処理
void	Samp::Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y),D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);
}

//ボックスとの当たり判定
bool	Samp::BoxHitCheck(Box3D& box)
{
	if (hitModel.HitCheck(box))
	{
		//MessageBox(NULL, TEXT("衝突しました"), TEXT("オッケー"), MB_OK);
		return true;
	}
	return false;
}





