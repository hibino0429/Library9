#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Light.h"
#include "../../../Library9/Model/Model.h"

//---------------------------------------------------------
//街頭オブジェクト
//---------------------------------------------------------
class StreetLight
{
public:
	StreetLight();
	~StreetLight();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//そのほかの機能
	void	GetPos(const D3DXVECTOR3& pos);		//街灯の位置を取得
	void	SetUseLight(int number);		//使用するライトの番号

public:
	//定数

	//変数
	//ライトの変化
	float	frameCnt;
	float	timeCnt;
	Box3D	hitBox;			//衝突判定

public:
	//オブジェクト
	Model	streetLight;
	Light			light;		//ライトオブジェクト
	
public:
	Mat4X4::Matrix	world;
};