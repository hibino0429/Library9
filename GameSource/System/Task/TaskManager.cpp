#include "TaskManager.h"

//処理は特になし
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