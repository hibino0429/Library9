#include "Input.h"

DGD*	dgd5 = DGD::Instance();

//�R���X�g���N�^
Input::Input() :pDirectInput(NULL), pkeyboard(NULL), pMouse(NULL)
{
	
}

//�f�X�g���N�^
Input::~Input()
{
	if (pDirectInput != NULL) {	pDirectInput->Release(); pDirectInput = NULL; }
	if (pkeyboard != NULL) { pkeyboard->Release(); pkeyboard = NULL; }
	if (pMouse != NULL) { pMouse->Release(); pMouse = NULL; }
}


//---------------------------------------------------------
//DirectInput�̏�����
//---------------------------------------------------------
HRESULT		Input::InitDirectInput(HWND hWnd, HINSTANCE hInstance)
{
	//�ϐ��Ƃ�
	HRESULT hr = S_OK;		//���������̌��ʕԂ�
	
							//�ŏ��ɏ��������Ă���
	KillTimer(hWnd, 0);
	

	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDirectInput, NULL)))
	{
		MessageBox(NULL, TEXT("DirectInput8Create"), TEXT("DirectInput"), MB_OK);
		return hr;
	}

	if (FAILED(hr = SetKeyboard(hWnd))) { return hr; }
	//if (FAILED(hr = SetJoystick(hWnd))) { return hr; }
	if (FAILED(hr = SetMouse(hWnd)))	{ return hr; }
	
	return hr;
}


//---------------------------------------------------------
//DirectInput�֌W�̉������
//---------------------------------------------------------
void		Input::ClearDirectInput()
{
	//DirectInput�ŃL�[�{�[�h�A�}�E�X�A�W���C�X�e�B�b�N
	//�����ꂩ�g�p���Ȃ�A�g�p���I��
	if (pkeyboard) { pkeyboard->Unacquire(); }
	if (pJoystick) { pJoystick->Unacquire(); }
	if (pMouse)		{ pMouse->Unacquire(); }

	//�f�o�C�X�̉��
	pkeyboard->Release();
	pJoystick->Release();
	pMouse->Release();

	//DirectInput�̉��
	pDirectInput->Release();
}


//--------------------------------------------------------
//DirectInput�ŃL�[�{�[�h���g�p�\�ɂ���
//--------------------------------------------------------
HRESULT		Input::SetKeyboard(HWND hWnd)
{
	//�ϐ�
	HRESULT	hr;		//�������Ƃ��̌��ʗp

					//�V�X�e���L�[�{�[�h�f�o�C�X��T���Ċm��
					//�L�[�{�[�h���Ȃ��ꍇ�A�͒��ӂ��K�v
	if (FAILED(hr = pDirectInput->CreateDevice(GUID_SysKeyboard, &pkeyboard, NULL)))
	{
		return hr;
	}

	if (pkeyboard == NULL)
	{
		return S_OK;		//�L�[�{�[�h���Ȃ�
	}

	//DirectInput����󂯎��f�[�^�t�H�[�}�b�g���L�[�{�[�h�ɐݒ�
	//c_dfDIKeyboard�́ADirectInput���p�ӂ����O���[�o���ϐ�
	//const�ݒ肳��ĕϐ��̒l�͕ύX�ł��Ȃ�
	if (FAILED(hr = pkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//�V�X�e����A�ق���DirectInput�𗘗p�����A�v���P�[�V������
	//�ǂ̂悤�ɘA�g����΂悢��
	//DirectInput�ɒʒm���邽�߂ɁA�������x�����Z�b�g
	//(�t�H�A�O�����h�E���ړ��́E�������[�h�EWindows�L�[�����ɌŒ�)
	if (FAILED(hr = pkeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
	{
		return hr;
	}

	//�L�[�{�[�h�̓��͂�L���ɂ���
	pkeyboard->Acquire();

	return S_OK;
}


//----------------------------------------------------------
//�L�[�{�[�h�̏�Ԃ��擾
//�����L�[�̓��͂�F��
//�o�b�t�@���g���A�f�[�^���͂��s���ꍇ�A�ύX�̕K�v����
//----------------------------------------------------------
int			Input::GetKeyboardState()
{
	int	result = kKEY_NONE;	//�Ԃ茌�p�ϐ�
	HRESULT	hr;
	BYTE	diks[256];		//DirectInput�̃L�[�{�[�h�X�e�[�^�X�o�b�t�@

							//�L�[�{�[�h�f�o�C�X���Ȃ��ꍇ�A�Ȃ߂炩�ɋ���
	if (NULL == pkeyboard) { return kKEY_ERR; }

	//���̓f�o�C�X�̏�Ԃ��m�ۂ��A�z��Ɏ��߂�
	ZeroMemory(diks, sizeof(diks));
	hr = pkeyboard->GetDeviceState(sizeof(diks), diks);
	if (FAILED(hr))
	{
		//�������͂������Ă����ꍇ�A�m�ۂ��A�ێ������݂�
		hr = pkeyboard->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pkeyboard->Acquire(); }

		//�G���[���͋A��
		if (FAILED(hr)) { return kKEY_ERR; }
	}

	//======================================================================
	//�L�[�{�[�h����̓��͂ɂ��
	if ((diks[0xcb] & 0x80) || (diks[0x4b] & 0x80))
	{
		result |= kDIR_LEFT;
	}                         // ��
	if ((diks[0xcd] & 0x80) || (diks[0x4d] & 0x80))
	{
		result |= kDIR_RIGHT;
	}                        // �E
	if ((diks[0xc8] & 0x80) || (diks[0x48] & 0x80))
	{
		result |= kDIR_UP;
	}                            // ��
	if ((diks[0xd0] & 0x80) || (diks[0x50] & 0x80))
	{
		result |= kDIR_DOWN;
	}                         // ��
							  //======================================================================

	if (diks[0x0f] & 0x80) { result |= kKEY_TAB; }       // Tab
	if (diks[0x2c] & 0x80) { result |= kKEY_Z; }         // Z
	if (diks[0x2d] & 0x80) { result |= kKEY_X; }         // X
	if (diks[0x2e] & 0x80) { result |= kKEY_C; }         // C
	if (diks[0x39] & 0x80) { result |= kKEY_SPACE; }     // Space
	if (diks[0x1c] & 0x80) { result |= kKEY_ENTER; }     // Enter
	if ((diks[0x0e] & 0x80) || (diks[0xd3] & 0x80))
	{
		result |= kKEY_DELBS;
	}                        // Del��BackSpace
	if ((diks[0x2a] & 0x80) || (diks[0x36] & 0x80))
	{
		result |= kKEY_SHIFT;
	}                        // Shift

	return(result);
}

//���͏���
char*		Input::GetKeyState()
{
	HRESULT hr = pkeyboard->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		pkeyboard->GetDeviceState(sizeof(keys), &keys);
		return keys;
	}
	return NULL;
}

//--------------------------------------------------------
//DirectInput�Ń}�E�X���g�p�\�ɂ���
//�L�[�{�[�h�ƃ}�E�X�̒��Ԃ̏������s��
//���ړ��͂�����
//�o�b�t�@�f�[�^�����������ꍇ�A�o�b�t�@�̐ݒ�Ȃǂ��K�v�ɂȂ�
//--------------------------------------------------------
HRESULT		Input::SetMouse(HWND hWnd)
{

	HRESULT	hr = S_OK;

	//�V�X�e���}�E�X�f�o�C�X��T���Ċm�ۂ���
	if (FAILED(hr = pDirectInput->CreateDevice(GUID_SysMouse, &pMouse, NULL)))
	{
		return hr;
	}

	//�W���C�X�e�B�b�N�͊m�ۂł�����
	//�W���C�X�e�B�b�N���ڑ�����Ă��Ȃ������ꍇ�A�ォ��ڑ����Ă��F�����Ȃ�
	if (NULL == pMouse)
	{
		MessageBox(NULL, TEXT("�}�E�X��������܂���"), TEXT("�G���["), MB_ICONERROR | MB_OK);
		return hr;
	}

	// DirectInput����󂯎��f�[�^�t�H�[�}�b�g���}�E�X�i�g���d�l�j�ɐݒ肷��
	// c_dfDIMouse2��DirectInput���p�ӂ����O���[�o���ϐ���const�ݒ肳��Ă���
	// �ϐ��̒l�͕ύX�ł��Ȃ�
	// ���̕�����Joystick�̏����Ɠ��l
	// �����������̃}�E�X�����邱�Ƃ͍l�����Ă��Ȃ�
	if (FAILED(hr = pMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return(hr);
	}

	// ���̃f�o�C�X�Ɠ��l�ɋ������x�����Z�b�g����
	// �����ł̓t�H�A�O�����h�E�r���I���p���[�h�ɌŒ�
	// �Q�[���̑���̂��߂Ƀ}�E�X���g���ꍇ�́A�ʏ킱�̃��[�h�ł��܂�Ȃ�
	// �������A���̃��[�h�ł́A�}�E�X�J�[�\���������Ȃ��Ȃ邽�߁A
	// �A�v���P�[�V�������Ń}�E�X�J�[�\����Ǝ��ɕ\��������ȂǍH�v��
	// �K�v�ɂȂ�̂ŗv����
	if (FAILED(hr = pMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		ClearDirectInput();
		if (hr == DIERR_UNSUPPORTED)
		{
			MessageBox(NULL, TEXT("DirectInput���T�|�[�g���Ă��Ȃ��������x���ł��B"), TEXT("�G���["), MB_ICONERROR | MB_OK);
		}
		return(hr);
	}

	// �}�E�X�̓��͂�L���ɂ���
	pMouse->Acquire();

	return S_OK;
}



//--------------------------------------------------------
//�}�E�X�̏�Ԃ��擾
//�o�b�t�@���g���āA�f�[�^���͂��s�������ꍇ�A�ύX�̕K�v������
//--------------------------------------------------------
HRESULT		Input::GetMouseState(HWND hWnd, int* result)
{
	HRESULT       hr;             // �V�X�e�����U���g
	DIMOUSESTATE2 aMouseState;    // DirectInput�̃}�E�X���\����

								  // �}�E�X���Ȃ��ꍇ�́A�Ȃ߂炩�ɋ���
	if (NULL == pMouse) { return S_OK; }

	// ���͋@��̏�Ԃ��m�ۂ��A�z��ɔ[�߂�
	// �L�[�{�[�h�Ƃ悭���Ă���
	ZeroMemory(&aMouseState, sizeof(DIMOUSESTATE2));

	hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState);
	if (FAILED(hr))
	{
		// �������͂������Ă����ꍇ�A�Ċm�ۂ����݂�
		hr = pMouse->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pMouse->Acquire(); }

		// �G���[���͑��̃A�v���P�[�V�������t�H�A�O�����h��
		// �Ȃ��Ă����肷��̂ŉ������Ȃ��ŋA��
		if (FAILED(hr))
		{
			*result = kKEY_ERR;
			return(S_OK);
		}
	}

	//======================================================================
	// �}�E�X�{�^���̓ǂݎ��
	if (aMouseState.rgbButtons[0x00] & 0x80) { *result |= kKEY_Z; }    // Z
	if (aMouseState.rgbButtons[0x01] & 0x80) { *result |= kKEY_X; }    // X
	if (aMouseState.rgbButtons[0x02] & 0x80) { *result |= kKEY_C; }    // C
	if (aMouseState.rgbButtons[0x03] & 0x80) { *result |= kKEY_A; }    // A
	if (aMouseState.rgbButtons[0x04] & 0x80) { *result |= kKEY_S; }    // S
	if (aMouseState.rgbButtons[0x05] & 0x80) { *result |= kKEY_D; }    // D
	if (aMouseState.rgbButtons[0x06] & 0x80) { *result |= kKEY_L; }    // L
	if (aMouseState.rgbButtons[0x07] & 0x80) { *result |= kKEY_R; }    // R


																	   //======================================================================
																	   // �ړ������̓ǂݎ��
	if ((aMouseState.lX != 0) || (aMouseState.lY != 0))
	{
		const double kPI_1EIGHTH = kPI_1FOURTH / 2.0f;    // 8���̂P

		double aTheta = atan2((double)aMouseState.lX, (double)aMouseState.lY);

		if ((aTheta < kPI_1EIGHTH * 3.0f) && (aTheta > kPI_1EIGHTH * -3.0f))
		{
			*result |= kDIR_DOWN;
		}
		else
			if ((aTheta > kPI_1EIGHTH * 5.0f) || (aTheta < kPI_1EIGHTH * -5.0f))
			{
				*result |= kDIR_UP;
			}

		if ((aTheta > kPI_1EIGHTH * 1.0f) && (aTheta < kPI_1EIGHTH * 7.0f))
		{
			*result |= kDIR_RIGHT;
		}
		else
			if ((aTheta < kPI_1EIGHTH * -1.0f) && (aTheta > kPI_1EIGHTH * -7.0f))
			{
				*result |= kDIR_LEFT;
			}
	}

	return(S_OK);
}


/*
//--------------------------------------------------------
//DirectInput�ŃW���C�X�e�B�b�N���g�p�\�ɂ���
//�����̏ꍇ�A�����ŏ�����������ύX������
//--------------------------------------------------------
HRESULT		Input::SetJoystick(HWND hWnd)
{
	HRESULT hr;    // �����������Ƃ��̌��ʕԂ��p

				   // �W���C�X�e�B�b�N��T���Ċm�ۂ���
				   // �i�W���C�X�e�B�b�N�͕�������\��������j
				   // EnumJoysticksCallback�̓f�o�C�X���ƂɌĂяo�����R�[���o�b�N�֐�
				   // �f�o�C�X�̐������Ăяo�����
				   // DI8DEVCLASS_GAMECTRL�͂��ׂẴQ�[���p�R���g���[����T���o�����߂̒萔
				   // DIEDFL_ATTACHEDONLY�̓A�^�b�`��Ԃɂ���A�C���X�g�[�����݂̃f�o�C�X�̂� 
	if (FAILED(hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return(hr);
	}

	// �W���C�X�e�B�b�N�͊m�ۂł����H
	// �W���C�X�e�B�b�N���ڑ�����Ă��Ȃ������ꍇ�A���Ƃ���ڑ����Ă��F�����Ȃ�
	if (NULL == pJoystick)
	{
		MessageBox(NULL, TEXT("�W���C�X�e�B�b�N�������ł��܂���ł����B"), TEXT("�W���C�X�e�B�b�N�m�ۂł��Ȃ�"), MB_ICONERROR | MB_OK);
		return(S_OK);    // �����ŋA���Ă��܂�
	}

	// DirectInput����󂯎��f�[�^�t�H�[�}�b�g��
	// �W���C�X�e�B�b�N�i�g���d�l�j�ɐݒ肷��
	// c_dfDIJoystick2��DirectInput���p�ӂ����O���[�o���ϐ�
	// const�ݒ肳��Ă��ĕϐ��̒l�͕ύX�ł��Ȃ�
	// ���̕����͕��ʂ̃W���C�p�b�h���g������͒�^��ɋ߂����A
	// �����̃W���C�X�e�B�b�N������ꍇ�A���ꂼ��ɑ΂���
	// �f�[�^�t�H�[�}�b�g��ݒ肷��K�v�����邱�Ƃɒ��ӂ���
	if (FAILED(hr = pJoystick->SetDataFormat(&c_dfDIJoystick2)))
	{
		return(hr);
	}

	// �V�X�e����A����DirectInput�𗘗p�����A�v���P�[�V�����ƁA
	// �ǂ̂悤�ɘA�g����΂悢�̂�
	// DirectInput�ɒʒm���邽�߂ɁA�������x�����Z�b�g����
	// ����������̃W���C�X�e�B�b�N���g���ꍇ��
	// ���ꂼ��ɑ΂��Đݒ肷��K�v������
	// �����ł̓t�H�A�O�����h�E�r���I���p���[�h�ɌŒ�
	// ���ʁA�W���C�X�e�B�b�N�g���ꍇ�͂��̐ݒ�̂܂܂ł��܂�Ȃ�
	if (FAILED(hr = pJoystick->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		return(hr);
	}

	// EnumDevices���\�b�h�ŒT���o���ꂽ�W���C�X�e�B�b�N��ɂ���I�u�W�F�N�g�A
	// �܂葀�삷�邽�߂̃{�^��������L�[��
	// 1��1�m�F���Ă���
	// EnumObjectsCallback�̓f�B�o�C�X��ɃI�u�W�F�N�g�������邽�т�
	// �Ăяo�����R�[���o�b�N�֐�
	// DIDFT_ALL�̓f�o�C�X��̑S�Ă̓��o�̓I�u�W�F�N�g��񋓂��邽�߂̒萔
	if (FAILED(hr = pJoystick->EnumObjects(EnumObjectsCallback, (VOID*)hWnd, DIDFT_ALL)))
	{
		return(hr);
	}

	// �W���C�X�e�B�b�N�̓��͂�L���ɂ���
	pJoystick->Acquire();

	return(S_OK);
}
*/


//--------------------------------------------------------
//�W���C�X�e�B�b�N�̏�Ԃ��擾����
//�o�b�t�@���g�������͂��s���Ȃ�A�ύX�̕K�v������
//--------------------------------------------------------
HRESULT		Input::GetJoystickState(HWND hWnd, int* result)
{
	HRESULT  hr = S_OK;
	//  TCHAR strText[512];    // �f�o�C�X�̏�Ԃ��擾����o�b�t�@�i���Ƀ{�^���j
	DIJOYSTATE2 aJoystickState;    // �W���C�X�e�B�b�N�̏�Ԃ��擾����
								   //  TCHAR* str;

								   // �����A�W���C�X�e�B�b�N�f�o�C�X������������Ă��Ȃ������ꍇ��
								   // ���������ɋA��
	if (NULL == pJoystick)
	{
		*result = kKEY_ERR;
		return (S_OK);
	}

	// �f�o�C�X�̌��݂̏󋵂��擾����
	hr = pJoystick->Poll();
	if (FAILED(hr))
	{
		// DirectInput��Poll���\�b�h���Ăяo���ꂽ���_�ł�
		// ���̓X�g���[���̏�Ԃ�`���邪
		// ���͋@�킪�Ȃ�炩�̌����Ŏ���ꂽ�Ƃ��Ă�
		// ��������\�b�h���Ԃ��G���[�ȊO�Œm�邱�Ƃ͂ł��Ȃ�
		// �܂��A�f�o�C�X�����Z�b�g�����i���Ȃ�
		// ���̂��߁A�f�o�C�X���Ď擾���邱�Ƃ����݂�
		hr = pJoystick->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pJoystick->Acquire(); }

		// ����ȊO�̃G���[�́A���̃A�v���P�[�V�������t�H�A�O�����h�ɂȂ��Ă��邩
		// �A�v���P�[�V�������̂��ŏ�������ăf�[�^���擾�ł��Ȃ��ꍇ���قƂ��
		// ���������ꍇ�́A���������ɋA���Č�ōĎ擾�����݂�
		return(S_OK);
	}

	// �W���C�X�e�B�b�N�̏�Ԃ��擾����
	// �����Ŏ擾�ł����Ԃ́A���Poll()���\�b�h���Ăяo�������_�̂���
	// GetDeviceState�̌Ăяo�����x���΁A���R���ꂾ���Â����ɂȂ��Ă��܂�
	// �������G���[��Ԃ��ꍇ�A�W���C�X�e�B�b�N�����������ꂽ�\��������
	if (FAILED(hr = pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &aJoystickState)))
	{
		return(hr);
	}


	// �����{�^���̌��o�iZ���͌��Ă��Ȃ��j
	if (aJoystickState.lX > kJS_DEAD) { *result |= kDIR_RIGHT; }
	else if (aJoystickState.lX < -kJS_DEAD) { *result |= kDIR_LEFT; }
	if (aJoystickState.lY > kJS_DEAD) { *result |= kDIR_DOWN; }
	else if (aJoystickState.lY < -kJS_DEAD) { *result |= kDIR_UP; }

	// �ǂ̃{�^���������ꂽ���m�F����
	// rgbButtons�͉����ꂽ�{�^���ɑΉ������z��̍ŏ�ʃr�b�g��1�ɂȂ�
	if (aJoystickState.rgbButtons[0x00] & 0x80) { *result |= kKEY_Z; }     // A
	if (aJoystickState.rgbButtons[0x01] & 0x80) { *result |= kKEY_X; }     // B
	if (aJoystickState.rgbButtons[0x02] & 0x80) { *result |= kKEY_C; }     // C

	if (aJoystickState.rgbButtons[0x03] & 0x80) { *result |= kKEY_A; }     // X
	if (aJoystickState.rgbButtons[0x04] & 0x80) { *result |= kKEY_S; }     // Y
	if (aJoystickState.rgbButtons[0x05] & 0x80) { *result |= kKEY_D; }     // Z

	if (aJoystickState.rgbButtons[0x06] & 0x80) { *result |= kKEY_L; }     // L
	if (aJoystickState.rgbButtons[0x07] & 0x80) { *result |= kKEY_R; }     // R
	if (aJoystickState.rgbButtons[0x08] & 0x80) { *result |= kKEY_ENTER; } // Start

	return(hr);
}



//--------------------------------------------------------
//EnumDevices���\�b�h�Őݒ�
//�W���C�X�e�B�b�N1�ɂ�1��Ăяo�����R�[���o�b�N�֐�
//�񋓂𑱂���Ȃ�ADIENUM_CONTINUE
//���������Ȃ�ADIENUM_STOP
//--------------------------------------------------------
BOOL CALLBACK Input::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���l������
	// g_pJoystick�Ɋm�ۂ��ꂽ����[�߂�̂ŁA
	// �����̃W���C�X�e�B�b�N��F�����������ꍇ��
	// ���̐�����LPDIRECTINPUTDEVICE8�^�̕ϐ���p�ӂ��Ă���
	hr = Input::pDirectInput->CreateDevice(pdidInstance->guidInstance, &pJoystick, NULL);

	// ���s���Ă����ꍇ�A���̃W���C�X�e�B�b�N�͎g���Ȃ��B
	// �f�o�C�X��񋓂��Ă���r���Ń��[�U�[��
	// �W���C�X�e�B�b�N���O�����\��������
	// �����ł́A�W���C�X�e�B�b�N��1������΂���ł����̂ŁA
	// ���s�����Ƃ��ɂ������čēx��������悤�ɂ��Ă���
	if (SUCCEEDED(hr))
	{
		return(DIENUM_STOP);
	}
	else { return(DIENUM_CONTINUE); }
}



//---------------------------------------------------------
//EnumObjects���\�b�h�Őݒ�
//�W���C�X�e�B�b�N�̊p�x�A�{�^���A�����R���g���[���[��
//1��1���ׂĂ����R�[���o�b�N�֐�
//---------------------------------------------------------
BOOL CALLBACK Input::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext)
{
	HWND hWnd = (HWND)pContext;

	// �񋓂��ꂽ�I�u�W�F�N�g���p�x�R���g���[���������ꍇ
	// �p�x�R���g���[����DIPROP_RANGE���Z�b�g���čő�ŏ��l��ݒ肷��
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diprg;
		// �K���������������Ȃ���΂Ȃ�Ȃ�
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		// �K���������������Ȃ���΂Ȃ�Ȃ�
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		// dwObj �����o�̉��ߕ��@���w�肷��
		// �ڍׂɂ��ẮAdwObj�����o�Ɋւ��鉺�̐������Q�Ƃ��邱��
		diprg.diph.dwHow = DIPH_BYID;
		// dwHow �����o�� DIPH_BYID �̏ꍇ�A���̃����o�́A
		// �ݒ�܂��͎擾�����v���p�e�B�����I�u�W�F�N�g�̎��ʎq�Ƃ���
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.lMin = -kJS_RESO;    // �p�x�f�o�C�X�̍ŏ��l
		diprg.lMax = +kJS_RESO;    // �p�x�f�o�C�X�̍ő�l

		MessageBox(NULL, TEXT("��Βl�����Βl���o�͂���f�B�o�C�X���m�F���܂����B\n�ő�l�A�ŏ��l��ݒ肵�܂��B"), TEXT("�f�o�C�X�̊m�F"), MB_ICONEXCLAMATION | MB_OK);

		// ���o�p�x�͈̔͂�ݒ肷��
		// DIPROP_RANGE�Őݒ���s�����A�ꕔ�̃f�o�C�X�ł́A
		// ����͓ǂݎ���p�ł��邽�߁A���s����ꍇ������
		// �ꕔ�̃f�o�C�X�ł́A����͓ǂݎ���p�ɂȂ��Ă���
		// ���s�����ꍇ�́A�p�x�f�B�o�C�X���ǂ�Ȓl���o�͂��Ă��邩
		// �킩��Ȃ��̂ŗ񋓂��~�߂�
		if (FAILED(pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
		{
			return(DIENUM_STOP);
		}
	}

	return(DIENUM_CONTINUE);
}