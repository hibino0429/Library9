#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Input/Input.h"

//追加
#include "CameraMan.h"
#include "../../../Library9/Sound/SoundManager.h"
#include "Map.h"
#include "../../../Library9/Texture/Texture.h"
#include "../../../Library9/Font/Font.h"
#include <string>
#include "../../../Library9/Model/Model.h"

#include "../../ShaderSystem/ZTexture.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/NormalMap.h"
#include "../../ShaderSystem/DiffuseMap.h"

//参照するクラス--------------------------------------------
class CameraMan;
class Map;

//----------------------------------------------------------
//プレイヤークラス
//----------------------------------------------------------
class Player
{
public:

	Player();
	~Player();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//プレイヤーの生成
	static Player*	Create(bool flag);

	//プレイヤーの破棄
	void	Destroy();


	void	GetKey(int key);
	void	GetKeyboard(char*);

	//あたり判定
	bool	Hit(D3DXVECTOR3* min, D3DXVECTOR3* max);


	//カメラマンの向きを取得
	void	GetCameraManAngle(CameraMan* cameraMan);

	void	GetCameraManAngle(D3DXVECTOR3& angle);
	D3DXVECTOR3	GetPos();

	//めり込まない移動
	void	CheckMove(D3DXVECTOR3& est_,Map* map);


	//移動処理
	void	Move(Map* map);
	void	Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size);

public:
	
	//仮の変数-----------------------------------------------
	D3DXVECTOR3		cameraManAngle = D3DXVECTOR3(0,0,0);	//カメラマンの向き


public:
	Texture			tex;
	Font			font;
	//サウンド
	//Sounds			shot;
	//Sounds			jump;

	//プレイヤーの情報
	bool			active;
	int				key;

	char*			keys;
	float		turnSpeed;		//カメラの旋回速度
	float			speed;		//スピード

	PolyBox			polyBox;		//ポリゴンボックス
	Box3D			hitBox;			//当たり判定ボックス

	Model	model;
	Mat4X4::Matrix	matW;		//マトリックス
	
	void		ZRendere(ZTexture* zTex);
	void		DepthRender(DepthTexture* depTex);

	//ディフューズマップ
	DiffuseMap		diffuseMap;
	D3DXVECTOR3		lightDir;
	D3DXVECTOR3		lightColor;
	D3DXMATRIX		view;
	D3DXMATRIX		proj;
	void	GetLightInfo(Light* light);	//ライトの情報
	void	GetCameraInfo(CameraMan* cameraMan);
};

