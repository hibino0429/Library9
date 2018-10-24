#pragma once
#include "../../../Library9/Function.h"
#include "../TaskManager.h"

//タスククラスの追加----------------------------
#include "../../../Library9/Input/Input.h"

//----------------------------------------------
//タイトルクラス
//----------------------------------------------
class Title
{
public:

	//基本処理
	void	Inialize();
	void	Finalize();
	Task	UpDate();
	void	Render();

public:
	Input	input;
	char*	key;
	
	//フォント
	Text::Font	font;

	//テクスチャ
	Texture2::Image	titleImg;
};
