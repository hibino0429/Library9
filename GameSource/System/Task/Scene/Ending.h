#pragma once
#include "../../../Library9/Function.h"
#include "../TaskManager.h"

//�g�p����N���X--------------------------------------
#include "../../../Library9/Input/Input.h"



//----------------------------------------------------
//�G���f�B���O�^�X�N
//----------------------------------------------------
class Ending
{
public:

	//��{����
	void		Initialize();
	void		Finalize();
	Task		UpDate();
	void		Render();

public:
	//����
	Input	input;
	char*	key;

	//�t�H���g
	Text::Font	font;
};
