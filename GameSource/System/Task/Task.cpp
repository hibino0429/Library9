#include "Task.h"


//�^�X�N�̓o�^
bool	Task::Regist(Shot::Object* object)
{
	//��̃^�X�N�ɓ����
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


//�^�X�N�̉��
bool	Task::Release(Shot::Object* object)
{
	for (auto it = task.begin();
		it != task.end();
		++it)
	{
		if ((*it) == object)
		{
			(*it)->Destroy();	//�I�u�W�F�N�g���폜
			//�^�X�N���폜����
			task.erase(it);
			(*it) = nullptr;
			return true;
		}
	}
	return false;
}