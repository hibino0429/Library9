#pragma once
#include "../../../Library9/Function.h"
#include "../TaskManager.h"

//�^�X�N�N���X�̒ǉ�----------------------------
#include "../../../Library9/Input/Input.h"

//----------------------------------------------
//�^�C�g���N���X
//----------------------------------------------
class Title
{
public:

	//��{����
	void	Inialize();
	void	Finalize();
	Task	UpDate();
	void	Render();

public:
	Input	input;
	char*	key;
	
	//�t�H���g
	Text::Font	font;

	//�e�N�X�`��
	Texture2::Image	titleImg;
};
