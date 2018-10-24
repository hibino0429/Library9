#include "TaskMain.h"


//------------------------------------------------------------
//�^�X�N�̏���������
//------------------------------------------------------------
void	TaskMain::Inialize()
{
	task.nowTask = Task::None;
	task.nextTask = Task::Title;
}


//------------------------------------------------------------
//�^�X�N�̉������
//------------------------------------------------------------
void	TaskMain::Finalize()
{

}


//------------------------------------------------------------
//�^�X�N�̍X�V����
//------------------------------------------------------------
void	TaskMain::UpDate()
{
	//���̃^�X�N���A���݂̃^�X�N�ƈ�v���Ȃ��ꍇ
	if (task.nowTask != task.nextTask)
	{
		//�����s���̃^�X�N�̏I���������Ăяo��
		switch (task.nowTask) {
		case Task::Title:		title.Finalize();	 break;
		case Task::GameMain:	gameMain.Finalize(); break;
		case Task::End:			ending.Finalize();	 break;
		}
		//���̃^�X�N��
		task.nowTask = task.nextTask;
		//���̃^�X�N�̏������������Ă�
		switch (task.nowTask) {
		case Task::Title:		title.Inialize();		break;
		case Task::GameMain:	gameMain.Initailize();	break;
		case Task::End:			ending.Initialize();	break;
		}
	}
	//���݂̃^�X�N�̎��s�E�X�V�������Ăяo��
	switch (task.nowTask) {
	case Task::Title:		task.nextTask = title.UpDate();		break;
	case Task::GameMain:	task.nextTask = gameMain.UpDate();	break;
	case Task::End:			task.nextTask = ending.UpDate();	break;
	}
	
}


//------------------------------------------------------------
//�^�X�N�̕`�揈��
//------------------------------------------------------------
void	TaskMain::Render()
{
	switch (task.nowTask) {
	case Task::Title:		title.Render();		break;
	case Task::GameMain:	gameMain.Render();	break;
	case Task::End:			ending.Render();	break;
	}
}






//---------------------------------------------------------------/
//�^�X�N���C������
//---------------------------------------------------------------/
HRESULT	TaskMain::Create(HWND hWnd, HINSTANCE hInst, BOOL isFullScreen, int clientWidth, int clientHeight)
{
	//DirectInput�̏�����
	if (FAILED(InputInit(hWnd, hInst)))
	{
		MessageBox(NULL, TEXT("���s���܂���"), TEXT("���s"), MB_OKCANCEL);
		return E_FAIL;
	}

	//DirectSound�̏�����
	/*if (!SE::Create(hWnd))
	{
		MessageBox(NULL, TEXT("�T�E���h�̏������Ɏ��s���܂���"), TEXT("SE::Create"), MB_OKCANCEL);
		return E_FAIL;
	}*/

	//Audio�̏�����
	if (!Audio::CreateSoundDevice(hWnd))
	{
		MessageBox(NULL, TEXT("Audio�̐����Ɏ��s���܂���"), TEXT("����͑傢�Ȃ�����"),MB_OK);
		return E_FAIL;
	}
	

	//Direct3D�̏�����
	if (FAILED(LibDEV::InitDevice(hWnd, isFullScreen, clientWidth, clientHeight)))
	{
		MessageBox(NULL, TEXT("Direct3D�f�o�C�X�̐����Ɏ��s���܂���"), TEXT("InitDevice"), MB_OK);
		return E_FAIL;
	}

	//�Q�[���̏�����
	this->Inialize();

	return S_OK;
}

//--------------------------------------------------------------/
//�Q�[���̔j������
//--------------------------------------------------------------/
void	TaskMain::Destroy()
{
	//�Q�[���̉��
	this->Finalize();

	LibDEV::FinalDevice();
}

//--------------------------------------------------------------/
//�Q�[�����C���̍X�V
//--------------------------------------------------------------/
void	TaskMain::SceneUpDate()
{
	//�Q�[���̍X�V
	this->UpDate();
}

//---------------------------------------------------------------/
//�Q�[�����C���̕`��
//---------------------------------------------------------------/
void	TaskMain::SceneRender()
{
	if (!LibDGD::ViewAndStencilClear()) { return; }

	if (LibDGD::BeginRender())
	{
		//�Q�[���̕`��
		this->Render();

		LibDGD::EndRender();
	}
	LibDGD::PresentRender();
}


//---------------------------------------------------------------/
//�f�X�g���N�^
//---------------------------------------------------------------/
TaskMain::~TaskMain()
{
	Destroy();
}


//----------------------------------------------------------------
//���͏����̏���������
//----------------------------------------------------------------
HRESULT		TaskMain::InputInit(HWND hWnd, HINSTANCE hInst)
{
	//Title�̓��͏����̏�����
	if (FAILED(title.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	//GameMain�̓��͏���
	if (FAILED(gameMain.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	//Ending�̓��͏���
	if (FAILED(ending.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	return S_OK;
}