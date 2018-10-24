#pragma once
#include <list>
#include <algorithm>
#include "../Game/Objects/Shot.h"

using namespace std;


//タスククラス
class Task
{
public:

	bool	Regist(Shot::Object*);	//タスクの登録
	bool	Release(Shot::Object*);	//タスクの解放

public:
	list<Shot::Object*>	task;
};