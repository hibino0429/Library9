//
// Window.cpp
// �A�v���P�[�V����(�E�B���h�E)�̎���
//
// �R�}���h���C���p�����[�^��/f������ƃt���X�N���[���\��
//
#pragma warning(disable:4005)

#include <windows.h>

#include "../GameSource/System/Common/Renderer.h"
#include "../GameSource/System/Common/Scene.h"
#include "../GameSource/System/Task/TaskMain.h"
#include "../GameSource/Library9/Sound/SoundManager.h"


#define CLIENT_WIDTH	640	// �N���C�A���g�̈�̃f�t�H���g�̕�, �t���X�N���[���̏ꍇ�͐��������𑜓x
#define	CLIENT_HEIGHT	480	// �N���C�A���g�̈�̃f�t�H���g�̍���, �t���X�N���[���̏ꍇ�͐��������𑜓x
TCHAR  clsName[] = TEXT("D3DFWSampleClass");	// �E�B���h�E��
TCHAR  winName[] = TEXT("D3DFWSample");			// �E�B���h�E��

//�V���O���g���N���X�̐���
DGD*	DGD::instance = 0;
SoundDevice* SoundDevice::instance = 0;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------
// �A�v���P�[�V�����̃G���g���|�C���g
// ����
//		hInstance     : ���݂̃C���X�^���X�̃n���h��
//		hPrevInstance : �ȑO�̃C���X�^���X�̃n���h��
//		lpCmdLine	  : �R�}���h���C���p�����[�^
//		nCmdShow	  : �E�B���h�E�̕\�����
// �߂�l
//		����������0�ȊO�̒l
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���ɂ��邩�ǂ����̔���
	// �R�}���h���C����/f��/F���ݒ肳��Ă�����t���X�N���[���ɂ���
	BOOL isFullScreen = FALSE;
    for(int i = 0; i < nCmdShow; i++) {
		if(_stricmp((char*)&lpCmdLine[i], "/f") == 0) {	// �R�}���h���C����/f�𔭌�
			isFullScreen = TRUE;	 // �t���O��TRUE�ɐݒ�
			break;
		}
    }

	HWND		hWnd;
	MSG			msg;

	// �E�B���h�E�N���X�̏�����
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),				// ���̍\���̂̃T�C�Y
		NULL,							// �E�C���h�E�̃X�^�C��(default)
		WindowProc,						// ���b�Z�[�W�����֐��̓o�^
		0,								// �ʏ�͎g��Ȃ��̂ŏ��0
		0,								// �ʏ�͎g��Ȃ��̂ŏ��0
		hInstance,						// �C���X�^���X�ւ̃n���h��
		NULL,							// �A�C�R���i�Ȃ��j
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���̌`
		NULL, NULL,						// �w�i�Ȃ��A���j���[�Ȃ�
		clsName,						// �N���X���̎w��
		NULL							// ���A�C�R���i�Ȃ��j
	};

	// �E�B���h�E�N���X�̓o�^
	if(RegisterClassEx(&wcex) == 0){
		return 0;	// �o�^���s
	}
	
	// �E�B���h�E�̍쐬
	if(isFullScreen) { // �t���X�N���[��
		int sw;
		int sh;
		// ��ʑS�̂̕��ƍ������擾
		sw = GetSystemMetrics(SM_CXSCREEN);
		sh = GetSystemMetrics(SM_CYSCREEN);

		hWnd = CreateWindow( 
					clsName, 			// �o�^����Ă���N���X��
					winName, 			// �E�C���h�E��
					WS_POPUP,			// �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
					0, 					// �E�C���h�E�̉������̈ʒu
					0, 					// �E�C���h�E�̏c�����̈ʒu
					CLIENT_WIDTH, 		// �E�C���h�E�̕�
					CLIENT_HEIGHT,		// �E�C���h�E�̍���
					NULL,				// �e�E�C���h�E�̃n���h���i�ȗ��j
					NULL,				// ���j���[��q�E�C���h�E�̃n���h��
					hInstance, 			// �A�v���P�[�V�����C���X�^���X�̃n���h��
					NULL				// �E�C���h�E�̍쐬�f�[�^
				);
	}
	else {
		hWnd = CreateWindow(clsName, 
							winName, 
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT, 
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL);

		// �E�B���h�E�T�C�Y���Đݒ肷��
		RECT rect;
		int ww, wh;
		int cw, ch;
		// �N���C�A���g�̈�̊O�̕����v�Z
		GetClientRect(hWnd, &rect);		// �N���C�A���g�����̃T�C�Y�̎擾
		cw = rect.right - rect.left;	// �N���C�A���g�̈�O�̉������v�Z
		ch = rect.bottom - rect.top;	// �N���C�A���g�̈�O�̏c�����v�Z

		// �E�C���h�E�S�̂̉����̕����v�Z
		GetWindowRect(hWnd, &rect);		// �E�C���h�E�S�̂̃T�C�Y�擾
		ww = rect.right - rect.left;	// �E�C���h�E�S�̂̕��̉������v�Z
		wh = rect.bottom - rect.top;	// �E�C���h�E�S�̂̕��̏c�����v�Z
		ww = ww - cw;					// �N���C�A���g�̈�ȊO�ɕK�v�ȕ�
		wh = wh - ch;					// �N���C�A���g�̈�ȊO�ɕK�v�ȍ���

		// �E�B���h�E�T�C�Y�̍Čv�Z
		ww = CLIENT_WIDTH + ww;			// �K�v�ȃE�C���h�E�̕�
		wh = CLIENT_HEIGHT + wh;		// �K�v�ȃE�C���h�E�̍���

		// �E�C���h�E�T�C�Y�̍Đݒ�
		SetWindowPos(hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);

	}

	// �E�B���h�E�̕\��
    ShowWindow(hWnd, nCmdShow);

	// WM_PAINT���Ă΂�Ȃ��悤�ɂ���
	ValidateRect(hWnd, 0);
	

	//--------------------
	//�Q�[�����C���̐���
	//--------------------
	TaskMain	taskMain;
	if (FAILED(taskMain.Create(hWnd, wcex.hInstance, isFullScreen, CLIENT_WIDTH, CLIENT_HEIGHT)))
	{
		MessageBox(NULL, TEXT("�^�X�N���C���̐����Ɏ��s���܂���"), TEXT("taskMain.Create()"),MB_OKCANCEL);
		return E_FAIL;
	}

	// ���b�Z�[�W��������ѕ`�惋�[�v
	while(TRUE) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {	// PostQuitMessage()���Ă΂ꂽ
				break;	//���[�v�̏I��
			}
			else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else {	// �������郁�b�Z�[�W�������Ƃ��͕`����s��

			// �E�B���h�E�������Ă��鎞�����`�悷�邽�߂̏���
			WINDOWPLACEMENT wndpl;
			GetWindowPlacement(hWnd, &wndpl);	// �E�C���h�E�̏�Ԃ��擾
			if((wndpl.showCmd != SW_HIDE) && 
				(wndpl.showCmd != SW_MINIMIZE) &&
				(wndpl.showCmd != SW_SHOWMINIMIZED) &&
				(wndpl.showCmd != SW_SHOWMINNOACTIVE)) {

				// �`�揈���̎��s
				//renderer.RenderScene(&scene);


				//----------------------------
				//�Q�[�����C���̍X�V�E�`��
				//----------------------------
				taskMain.SceneUpDate();
				taskMain.SceneRender();
			}
		}

    }
	

	return (int) msg.wParam;
}

//-------------------------------------------------------------
// ���b�Z�[�W�����p�R�[���o�b�N�֐�
// ����
//		hWnd	: �E�B���h�E�n���h��
//		msg		: ���b�Z�[�W
//		wParam	: ���b�Z�[�W�̍ŏ��̃p�����[�^
//		lParam	: ���b�Z�[�W��2�Ԗڂ̃p�����[�^
// �߂�l
//		���b�Z�[�W��������
//-------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
	case WM_CLOSE:				// �E�C���h�E������ꂽ
		PostQuitMessage(0);		// �A�v���P�[�V�������I������
		break;
	case WM_KEYDOWN:				// �L�[�������ꂽ
		if (wParam == VK_ESCAPE) {	// �����ꂽ�̂�ESC�L�[��
			PostQuitMessage(0);		// �A�v���P�[�V�������I������
		}
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
