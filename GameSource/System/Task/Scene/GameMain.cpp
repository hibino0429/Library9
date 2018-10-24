#include "GameMain.h"

#include <time.h>


//----------------------------------------------------
//ゲームメインの初期化
//----------------------------------------------------
void	GameMain::Initailize()
{
	srand((unsigned int)time(0));

	cameraMan.Initialize();
	LightInit();

	LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_DITHERENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1, 1, 1, 1));

	
	map.Initialize();
	

	player.Initialize();
	samp.Initialize();
	//object.Initialize();
	obj.Initialize();

	D3DXMATRIX	lightV,lightP;
	D3DXMatrixPerspectiveFovLH(&lightP, D3DXToRadian(120), 1.0f, 40.0f, 700.0f);
	D3DXMatrixLookAtLH(&lightV, &D3DXVECTOR3(100, 500, 100), &D3DXVECTOR3(0, -60, 0), &D3DXVECTOR3(0, 1, 0));
	
	//Z値テクスチャの初期化
	zTexture.Initialize();
	zTexture.SetViewMatrix(&lightV);		//ライトのビュー
	zTexture.SetProjMatrix(&lightP);		//ライトの射影

	//深度バッファの初期化
	depthTexture.SetTexture(zTexture.GetTexture());	//テクスチャの情報を渡す
	depthTexture.Initialize();
	depthTexture.GetLightProjMatrix(&lightP);		//ライトの射影
	depthTexture.GetLightViewMatrix(&lightV);		//ライトのビュー
	depthTexture.SetCameraProjMatrix(&cameraMan.PassProjMatrix());	//カメラの射影

}


//----------------------------------------------------
//ゲームメインの終了
//----------------------------------------------------
void	GameMain::Finalize()
{
	MessageBox(NULL, TEXT("ゲームメインが終了します"), TEXT("GameMain"), MB_OK);
}


//----------------------------------------------------
//ゲームメインの更新
//----------------------------------------------------
Task	GameMain::UpDate()
{
	key = input.GetKeyState();
	
	//カメラマンの更新
	cameraMan.GetKeyboard(input.GetKeyState());
	cameraMan.CircleMove(&player);
	cameraMan.UpDate();

	//ライトの更新
	for (int i = 0; i < 4; ++i)
	{
		light[i].UpDate();
	}

	//スポットライトの更新
	light[1].SetPosition(D3DXVECTOR3(player.model.pos.x,player.model.pos.y + 10,player.model.pos.z));

	//追加---------
	
	map.UpDate();

	player.GetKeyboard(input.GetKeyState());
	player.GetCameraManAngle(cameraMan.angle);

	//プレイヤーとマップとの当たり判定
	player.Move(&map);
	player.UpDate();


	samp.BoxHitCheck(player.hitBox);
	samp.UpDate();

	obj.UpDate();

	//object.UpDate();


	//タスクの遷移
	Task	nextTask = Task::GameMain;
	if (key[DIK_V] & 0x80)
	{
		nextTask = Task::End;
	}

	return nextTask;
}


//----------------------------------------------------
//ゲームメインの描画
//----------------------------------------------------
void	GameMain::Render()
{
	LibDGD::ZBufClear();

	//ライトの描画
	for (int i = 0; i < 5; ++i)
	{
		light[i].Render();
	}
	//カメラのマンの描画
	cameraMan.Render();


	//--------------------------------------------------
	//描画の開始
	zTexture.Begin();

	//オブジェクトの描画
	player.ZRendere(&zTexture);
	//object.ZTexRender(&zTexture);
	samp.ZTexRender(&zTexture);
	map.ZTexRender(&zTexture);

	obj.Render(&zTexture);

	//描画の終了
	zTexture.End();
	//--------------------------------------------------

	//カメラのビュー・射影行列のセット
	depthTexture.SetCameraViewMatrix(&cameraMan.PassViewMatrix());
	depthTexture.SetCameraProjMatrix(&cameraMan.PassProjMatrix());

	//--------------------------------------------------
	//深度シャドウバッファの描画
	depthTexture.Begin(0, 0);
	
	//オブジェクトの描画
	//object.DepthRender(&depthTexture);
	samp.DepthRender(&depthTexture);
	map.DepthRender(&depthTexture);
	player.DepthRender(&depthTexture);

	obj.Render(&depthTexture);

	//描画の終了
	depthTexture.End();
	//--------------------------------------------------

	

	//法線マップのオブジェクト
	/*object.normalMap.SetViewMatrix(&cameraMan.PassViewMatrix());
	object.normalMap.SetProjMatrix(&cameraMan.PassProjMatrix());
	D3DXVECTOR3 cameraVec = cameraMan.camera.GetTarget() - cameraMan.camera.GetPos();
	object.normalMap.SetCameraVec(cameraVec);
	object.normalMap.SetLightDir(light[0].direction);
	object.Render();*/
}



//ライトの初期化
void	GameMain::LightInit()
{
	//ライト0
	light[0].SetNumber(0);
	light[0].SetUse(true);
	//ディレクショナルライト
	//必要なもの
	//タイプ・ディフューズ色・方向・スペキュラー色
	light[0].SetType(D3DLIGHT_DIRECTIONAL);
	light[0].SetDiffuse(D3DXCOLOR(1, 1, 1, 1));
	light[0].SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.1f));
	light[0].SetDirection(D3DXVECTOR3(-5.0f, -5.0f, 10.0f));
	light[0].position = D3DXVECTOR3(0, 100, 0);

	//ライト1
	light[1].SetNumber(1);
	light[1].SetUse(true);
	//ポイントライト
	//必要なもの
	//タイプ・位置・光の有効距離・光の減衰・ディフューズ色, (スペキュラー色)
	light[1].SetType(D3DLIGHT_POINT);
	light[1].SetDiffuse(D3DXCOLOR(1.0f, 0.2f, 0, 1));
	light[1].SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	light[1].SetPosition(D3DXVECTOR3(600, 10, -150));
	light[1].SetAttenuation((1.0f / 755.0f) * (1.0f / 755.0f));
	light[1].SetRange(850.0f);


	//ライト2
	light[2].SetNumber(2);
	light[2].SetUse(false);

	//ライト3
	light[3].SetNumber(3);
	light[3].SetUse(false);


	light[0].Initalize();
	light[1].Initalize();
	light[2].Initalize();
	light[3].Initalize();
}


//ライトの更新
void	GameMain::LightUpDate()
{

}

//ライトの射影変換をセット
void	GameMain::SetLightView(D3DXMATRIX* mat,D3DXVECTOR3& pos)
{
	D3DXMatrixLookAtLH(mat, 
		&D3DXVECTOR3(pos.x + 50,pos.y + 200,pos.z + 100), 
		&D3DXVECTOR3(pos.x,pos.y-50,pos.z),
		&D3DXVECTOR3(0, 1, 0)
	);
}



