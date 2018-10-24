#pragma once

#include "DGD.h"
#include "Function.h"

//ライト
class Light
{
public:

	Light();
	~Light();

	//ライトの設定
	void	SetNumber(int);				//番号の指定
	void	SetUse(bool);				//使用するか指定

	void	SetType(D3DLIGHTTYPE);		//タイプ
	void	SetDiffuse(D3DXCOLOR);		//ディフューズ色
	void	SetSpecular(D3DXCOLOR);		//スペキュラ色
	void	SetAmbient(D3DXCOLOR);		//アンビエント色
	void	SetPosition(D3DXVECTOR3);	//光源の位置
	void	SetDirection(D3DXVECTOR3);	//光の方向
	void	SetRange(float);			//光源の有効距離
	void	SetFalloff(float);			//外部コーンの減衰
	void	SetAttenuation(float);		//光の減衰
	void	SetTheta(float);			//スポットライトの内部コーンの角度
	void	SetPhi(float);				//スポットライトの外部コーンの角度

	//基本処理
	void	Initalize();
	void	Finalize();
	void	UpDate();
	void	Render();
	

	//渡す処理
	D3DXMATRIX	PassWorldMatrix();	//ワールドマトリックスを渡す
	void	SetMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

private:

	//ライト
	D3DLIGHT9		m_light;

	//マトリックス
	Mat4X4::Matrix	world;

public:

	//ライト共通の変数
	int				number;		//番号
	bool			useFlag;	//ライトを使用するか
	

	//ライトの変数
	D3DLIGHTTYPE	type;		//タイプ
	D3DXCOLOR		diffuse;	//ディフューズ色
	D3DXCOLOR		specular;	//スペキュラ色
	D3DXCOLOR		ambient;	//アンビエント色
	D3DXVECTOR3		position;	//光源の位置
	D3DXVECTOR3		angle;		//光源の角度
	D3DXVECTOR3		size;		//光源の大きさ
	D3DXVECTOR3		direction;	//光の方向
	float			range;		//光源の有効距離
	float			falloff;	//外部コーンの減衰
	float			attenuation;//光の減衰
	float			theta;		//スポットライトの内部コーンの角度
	float			phi;		//スポットライトの外部コーンの角度

};

/////////////////
//ライトの種類
//点光源・スポットライト・ディレクショナルライト・環境光


//点光源の情報
//タイプ・位置・光の有効距離・光の減衰・ディフューズ色 , (スペキュラー色)


//スポットライトの情報
//


//ディレクショナルライト
//タイプ・光の方向・ディフューズ色 , (スペキュラー色)


//環境光の情報
//タイプ・ディフューズ色 , (スペキュラー色)

