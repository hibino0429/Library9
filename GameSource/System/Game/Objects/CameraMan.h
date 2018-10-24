#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Camera.h"
#include "Player.h"


//参照するクラス------------------------------------------------------
class Player;



//--------------------------------------------------------------------
//カメラマンクラス
//--------------------------------------------------------------------
class CameraMan
{
public:
	CameraMan();
	~CameraMan();


	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	
	//プレイヤーの位置を取得
	void	GetPlayerPos(Player* player);
	
	//プレイヤーの位置をセット
	void	GetKeyboard(char* key);
	char*	keys;

	//カメラマンの移動
	void	CircleMove(Player* player);
	int		angleAxis;

	
	//渡す処理
	D3DXMATRIX	PassViewMatrix();		//ビューマトリックスを渡す
	D3DXMATRIX	PassProjMatrix();		//プロジェクションマトリックスを渡す

public:
	Camera			camera;

public:

	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	float			dist;				//距離
	float			viewPointHeight;	//視点の高さ
	float			pointOfGazeHeight;	//注視点の高さ
};