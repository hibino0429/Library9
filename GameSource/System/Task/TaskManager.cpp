#include "TaskManager.h"

//�����͓��ɂȂ�
TaskManager::TaskManager()
{
	nowTask = TaskManager::TaskFlag::None;
	nextTask = TaskManager::TaskFlag::Title;
}

TaskManager::~TaskManager()
{
	nowTask = TaskManager::TaskFlag::None;
	nextTask = TaskManager::TaskFlag::Title;
}