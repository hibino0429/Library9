#pragma once


//--------------------------------------------
//タスク管理クラス
//--------------------------------------------
class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	//タスクの種類
	enum TaskFlag
	{
		None,		//なし
		Title,		//タイトル
		GameMain,	//ゲーム本編
		End,		//エンド
	};

public:
	TaskFlag	nowTask;
	TaskFlag	nextTask;
};

typedef TaskManager::TaskFlag	Task;