#pragma once
#include "../../Library9/Function.h"
#include "TaskManager.h"

//�^�X�N�N���X�w�b�_-----------------------------------
#include "Scene/Title.h"
#include "Scene/GameMain.h"
#include "Scene/Ending.h"




//-----------------------------------------------------
//�^�X�N���C��
//-----------------------------------------------------
class	TaskMain
{
public:

	~TaskMain();

	//��{����
	void	Inialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//���C������
	HRESULT	Create(HWND hWnd,HINSTANCE hInst, BOOL isFullScreen, int clientWidth, int clientHeight);
	void	Destroy();
	void	SceneUpDate();
	void	SceneRender();

	//���͏����̏�����
	HRESULT	InputInit(HWND hWnd, HINSTANCE hInst);

public:
	TaskManager				task;		//�^�X�N�Ǘ�
	//-------------------------------------------------
	//�^�X�N�N���X
	//-------------------------------------------------
	Title			title;
	GameMain		gameMain;
	Ending			ending;
};