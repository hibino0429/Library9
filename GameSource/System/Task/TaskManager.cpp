#include "TaskManager.h"

//ˆ—‚Í“Á‚É‚È‚µ
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