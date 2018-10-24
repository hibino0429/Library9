#pragma once
#include "../../Library9/Function.h"
#include "TaskManager.h"

//タスククラスヘッダ-----------------------------------
#include "Scene/Title.h"
#include "Scene/GameMain.h"
#include "Scene/Ending.h"




//-----------------------------------------------------
//タスクメイン
//-----------------------------------------------------
class	TaskMain
{
public:

	~TaskMain();

	//基本処理
	void	Inialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//メイン処理
	HRESULT	Create(HWND hWnd,HINSTANCE hInst, BOOL isFullScreen, int clientWidth, int clientHeight);
	void	Destroy();
	void	SceneUpDate();
	void	SceneRender();

	//入力処理の初期化
	HRESULT	InputInit(HWND hWnd, HINSTANCE hInst);

public:
	TaskManager				task;		//タスク管理
	//-------------------------------------------------
	//タスククラス
	//-------------------------------------------------
	Title			title;
	GameMain		gameMain;
	Ending			ending;
};