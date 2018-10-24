#pragma once
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <dinput.h>
#include "../DGD.h"


//���̓N���X
class Input
{
public:
	Input();
	~Input();

	//DirectInput�̏�����
	HRESULT		InitDirectInput(HWND, HINSTANCE);

	//DirectInput�֌W�̉������
	void		ClearDirectInput();

	//�}�E�X�̐ݒ�E�擾
	HRESULT		SetMouse(HWND);
	HRESULT		GetMouseState(HWND, int* result);

	//�W���C�X�e�B�b�N�̐ݒ�E�擾
	//HRESULT		SetJoystick(HWND);
	HRESULT		GetJoystickState(HWND, int* result);

	//�L�[�{�[�h�̏�Ԃ��擾
	HRESULT		SetKeyboard(HWND);
	int			GetKeyboardState();
	 char* GetKeyState();


	//�R�[���o�b�N�֐�
	BOOL CALLBACK	EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext);
	BOOL CALLBACK	EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext);

	//��`
	//���̒l�ɓx���|����ƃ��W�A���ɂȂ�
	#define	kDEG_TO_RAD		( D3DX_PI * 2.0f / 360.0f)	

	#define	kPI_1FOURTH		( D3DX_PI / 4.0f )			// 45�x
	#define	kPI_HALF		( D3DX_PI / 2.0f )			// 90�x

	//�@�W���C�X�e�B�b�N�Œʏ�A�{�^���A��������C�{�^����OK�AB���L�����Z���̈Ӗ���������
	#define kKEY_YES	(kKEY_Z | kKEY_ENTER | kKEY_SPACE | kKEY_C)
	#define	kKEY_NO		(kKEY_X)

	//�@�W���C�X�e�B�b�N�̐��x�Ɗ��x
	#define	kJS_RESO	1000
	#define	kJS_DEAD	( kJS_RESO / 2 )

	//-----------------------------------------------------------------------------
	//�@�L�[�{�[�h�i�W���C�X�e�B�b�N�j�̏��
	//�@�W���C�X�e�B�b�N�̏ꍇ��LEFT��RIGHT�ȂǑ�������L�[���͂������ɍs���邱�Ƃ͂��肦�Ȃ���
	//�@�L�[�{�[�h�ł͉\�ł��邱�Ƃ𒍈ӂ���
	enum {
		kKEY_NONE = 0x00000,
		kDIR_LEFT = 0x00001,
		kDIR_RIGHT = 0x00002,
		kDIR_UP = 0x00004,
		kDIR_DOWN = 0x00008,

		kKEY_Z = 0x00020,// A
		kKEY_X = 0x00040,// B
		kKEY_C = 0x00080,// C
		kKEY_A = 0x01000,// X
		kKEY_S = 0x02000,// Y
		kKEY_D = 0x04000,// Z

		kKEY_L = 0x08000,// L
		kKEY_R = 0x10000,// R

		kKEY_SPACE = 0x00010,

		kKEY_ENTER = 0x00100,
		kKEY_TAB = 0x00200,
		kKEY_SHIFT = 0x00400,
		kKEY_DELBS = 0x00800,

		kKEY_ERR = 0x80000,
		kKEY_DIR_MASK = 0x0000f,
		kKEY_BUTTON_MASK = 0xffff0,
		kKEY_ALL_MASK = 0xfffff
	};

private:
	LPDIRECTINPUT8		pDirectInput;	//DirectInput�I�u�W�F�N�g

	LPDIRECTINPUTDEVICE8	pkeyboard;	//�L�[�{�[�h�f�o�C�X
	LPDIRECTINPUTDEVICE8	pJoystick;	//�W���C�X�e�B�b�N�f�o�C�X
	LPDIRECTINPUTDEVICE8	pMouse;		//�}�E�X�f�o�C�X

	char				keys[256];
};



//���i�K�ł́A�L�[�{�[�h�̂ݑ���\