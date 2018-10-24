#pragma once
#include "../../../Library9/Function.h"
#include "../TaskManager.h"

//使用するクラス--------------------------------------
#include "../../../Library9/Input/Input.h"



//----------------------------------------------------
//エンディングタスク
//----------------------------------------------------
class Ending
{
public:

	//基本処理
	void		Initialize();
	void		Finalize();
	Task		UpDate();
	void		Render();

public:
	//入力
	Input	input;
	char*	key;

	//フォント
	Text::Font	font;
};
