#pragma once
#include <list>
#include <algorithm>
#include "../Game/Objects/Shot.h"

using namespace std;


//�^�X�N�N���X
class Task
{
public:

	bool	Regist(Shot::Object*);	//�^�X�N�̓o�^
	bool	Release(Shot::Object*);	//�^�X�N�̉��

public:
	list<Shot::Object*>	task;
};