#pragma once


//--------------------------------------------
//�^�X�N�Ǘ��N���X
//--------------------------------------------
class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	//�^�X�N�̎��
	enum TaskFlag
	{
		None,		//�Ȃ�
		Title,		//�^�C�g��
		GameMain,	//�Q�[���{��
		End,		//�G���h
	};

public:
	TaskFlag	nowTask;
	TaskFlag	nextTask;
};

typedef TaskManager::TaskFlag	Task;