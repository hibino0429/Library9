#pragma once

//追加--------------------
#include "../../../Library9/Camera.h"
#include "../../../Library9/Light.h"
#include "../../Game/Objects/Player.h"
#include "../../Game/Objects/Map.h"
#include "../../Game/Objects/Enemy.h"
#include "../../Game/Objects/Enemy2.h"
#include "../../Game/Effects/Particle.h"
#include "../../Game/Effects/Magic.h"
#include "../../Game/Objects/CameraMan.h"
#include "../../Game/Components/Sample.h"		//サンプル用
#include "../TaskManager.h"
#include "../../Game/Objects/Object.h"
#include "../../Game/Components/smoke.h"
#include "../../Game/Objects/Obj.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/ZTexture.h"

//ゲームメイン
class GameMain
{
public:


	//基本処理
	void	Initailize();
	void	Finalize();
	Task	UpDate();
	void	Render();


	//ライトの処理
	void	LightInit();
	void	LightUpDate();
	void	SetLightView(D3DXMATRIX* mat,D3DXVECTOR3& pos);

public:

	Light		light[4];

	//プレイヤー-----------
	Player		player;
	
	//マップ---------------
	Map			map;

	//敵-------------------
	//Enemy		enemy;
	//Enemy2		enemy2;
	
	//入力-----------------
	Input		input;
	char*		key;

	//パーティクル---------
	//Particle	particle;
	//MagicEffect	magicEff;

	//サンプル用
	Samp		samp;
	Obj			obj;

	//カメラマン
	CameraMan	cameraMan;
	
	//オブジェクト
	Object		object;

	//煙
	//Smoke		smoke;

	ZTexture		zTexture;
	DepthTexture	depthTexture;
	
};