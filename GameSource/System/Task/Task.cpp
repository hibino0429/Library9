#include "Task.h"


//タスクの登録
bool	Task::Regist(Shot::Object* object)
{
	//空のタスクに入れる
	if (task.empty())
	{
		task.push_back(object);
		return true;
	}
	else
	{
		task.push_back(object);
		return true;
	}
	return false;
}


//タスクの解放
bool	Task::Release(Shot::Object* object)
{
	for (auto it = task.begin();
		it != task.end();
		++it)
	{
		if ((*it) == object)
		{
			(*it)->Destroy();	//オブジェクトを削除
			//タスクを削除する
			task.erase(it);
			(*it) = nullptr;
			return true;
		}
	}
	return false;
}