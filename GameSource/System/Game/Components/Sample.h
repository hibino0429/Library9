#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Model/PolygonBox.h"
#include "../Objects/StreetLight.h"
#include "../../../Library9/Sound/SoundManager.h"
#include "../../../Library9/Model/Model.h"

//サンプルクラス
//DirectXの実験を行う
class Samp
{
public:

	Samp();
	~Samp();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//マップとの当たり判定
	bool	BoxHitCheck(Box3D& box);

	//マトリックス処理
	void	Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size);

public:
	
	//ワールド空間のXYZの方向を占めすモデル
	Model	Arrow;
	Model	fire;	//炎

	Mat4X4::Matrix	world;

public:
	
	//ライト
	Light		light;

public:

	//モデルの情報
	Model		model;
	Box3D		hitModel;


	//ライトの波の調整
	float	frameCnt;	//フレームカウント
	float	timeCnt;	//秒
	float	value;		//変位値



	StreetLight	streetLight;	//街灯

public:
	
	PolyBox			obj1Box;
	PolyBox			obj2Box;
	Box3D			obj1HitBox;
	Box3D			obj2HitBox;

	D3DXVECTOR3		vertexPos;
	D3DXVECTOR3		vertexSize;


	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);
};