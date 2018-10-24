#include "DSound.h"

//�R���X�g���N�^
Sound::Sound() : pDirectSound(NULL),pDirectSoundBuf(NULL), dwSpeakerConfig(0), pDSoundGuid(NULL)
, pNewSoundBuf(NULL)
{
	
}

//�f�X�g���N�^
Sound::~Sound()
{
	this->BufRelease();
	this->InterfaceRelease();
}

//�T�E���h�E�f�o�C�X�̎擾
bool	Sound::DSoundEnumCallBack()
{
	
	//DirectSoundEnumerate((LPDSENUMCALLBACK)DSEnumProc, &hCombo);
	return true;
}
BOOL CALLBACK Sound::DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	HWND hCombo = (HWND)lpContext;
	LPGUID lpTemp = NULL;
	
	if (lpGUID != NULL)
	{
		if ((lpTemp = (LPGUID)malloc(sizeof(GUID))) == NULL)
		{
			return true;
		}
		memcpy(lpTemp, lpGUID, sizeof(GUID));
	}

	//ComboBox_AddString(hCombo, lpszDesc);
	//ComboBox_SetItemData(hCombo, ComboBox_FindString(hCombo, 0, lpszDesc), lpTemp);
	free(lpTemp);
	lpTemp = NULL;

	return true;
}


//2:DirectSound�I�u�W�F�N�g�̍쐬
bool	Sound::DSoundCreate()
{
	if (FAILED(DirectSoundCreate8(
		NULL,		//�f�t�H���g�ł�NULL�AGUID���擾����Ȃ�pDSoundGuid
		&pDirectSound,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("DirectSound�I�u�W�F�N�g�̐����Ɏ��s���܂���"), TEXT("DSoundCreate"), MB_OK);
		return false;
	}
	return true;
}



//3:�������x���̐ݒ�
bool	Sound::SetCooperativeLevel(HWND hWnd)
{
	if (FAILED(pDirectSound->SetCooperativeLevel(
		hWnd, DSSCL_PRIORITY
	)))
	{
		MessageBox(NULL, TEXT("�������x���̐ݒ�Ɏ��s���܂���"), TEXT("SetCooperativeLevel"), MB_OK);
		return false;
	}
	return true;
}




//4:�f�o�C�X�̐��\�̒���
bool	Sound::GetCaps()
{
	dsCaps.dwSize = sizeof(DSCAPS);	//�K��������

	if (FAILED(pDirectSound->GetCaps(&dsCaps)))
	{
		MessageBox(NULL, TEXT("�f�o�C�X�̐��\�̎擾�Ɏ��s���܂���"), TEXT("GetCaps"), MB_OK);
		return false;
	}
	return true;
}



//5:�X�s�[�J�[�̒���
bool	Sound::GetSpeakerConfig()
{
	if (FAILED(pDirectSound->GetSpeakerConfig(&dwSpeakerConfig)))
	{
		MessageBox(NULL, TEXT("�X�s�[�J�[�̏��̎擾�Ɏ��s���܂���"), TEXT("GetSpeakerConfig"), MB_OK);
		return false;
	}

	switch (DSSPEAKER_CONFIG(dwSpeakerConfig))
	{
	case DSSPEAKER_5POINT1:		//�T�u�E�[�t�@�t����5�T���E���h�E�X�s�[�J�[
		break;
	case DSSPEAKER_DIRECTOUT:	//�X�s�[�J�[�p�̍\���͍s���Ȃ�
		break;
	case DSSPEAKER_HEADPHONE:	//�w�b�h�z��
		break;
	case DSSPEAKER_MONO:		//���m�����E�X�s�[�J�[
		break;
	case DSSPEAKER_QUAD:		//4�`�����l���E�X�e���I�E�X�s�[�J�[
		break;
	case DSSPEAKER_STEREO:		//�X�e���I�E�X�s�[�J�[

		//2�̃X�s�[�J�[�̔z�u
		switch (DSSPEAKER_GEOMETRY(dwSpeakerConfig))
		{
		case DSSPEAKER_GEOMETRY_WIDE:		//���X�i�[�𒆐S�Ƃ���20�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_NARROW:		//���X�i�[�𒆐S�Ƃ���10�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_MIN:		//���X�i�[�𒆐S�Ƃ���5�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_MAX:		//���X�i�[�𒆐S�Ƃ���180�x�̊p�x
			break;
		}
		break;

	case DSSPEAKER_SURROUND:	//�T���E���h�E�X�s�[�J�[
		break;
	case DSSPEAKER_7POINT1:		//�T�u�E�[�t�@�t����7�T���E���h�E�X�s�[�J�[
		break;
	}
	return true;
}





//6:�v���C�}���E�o�b�t�@�̍쐬
bool	Sound::CreateSoundBuffer()
{
	//DSBUFFERDESC�\���̂�ݒ�
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//�v���C�}���E�o�b�t�@���w��
	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//�o�b�t�@�̍쐬
	if (FAILED(pDirectSound->CreateSoundBuffer(
		&dsBufDesc, &pDirectSoundBuf, NULL
	)))
	{
		MessageBox(NULL, TEXT("�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}


	//�v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	//�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������
	PCMWAVEFORMAT	pcmWF;
	ZeroMemory(&pcmWF, sizeof(PCMWAVEFORMAT));
	pcmWF.wf.wFormatTag = WAVE_FORMAT_PCM;		//Wave�̃t�H�[�}�b�g
	pcmWF.wf.nChannels = 2;						//2�`�����l��(�X�e���I)
	pcmWF.wf.nSamplesPerSec = 22050;			//�T���v�����O�E���[�g	22kHz
	pcmWF.wf.nBlockAlign = 4;
	pcmWF.wf.nAvgBytesPerSec = pcmWF.wf.nSamplesPerSec * pcmWF.wf.nBlockAlign;	//�Œ�
	pcmWF.wBitsPerSample = 16;					//16�r�b�g

	pDirectSoundBuf->SetFormat((LPCWAVEFORMATEX)&pcmWF);	//�o�b�t�@�Ƀt�H�[�}�b�g���Z�b�g
	
	return true;
}





//7:�Z�J���_���E�o�b�t�@�̍쐬
bool	Sound::CreateSecondaryBuffer()
{
	WAVEFORMATEX	pcmWF;
	DSBUFFERDESC	dsBufDesc;

	//Wave�t�H�[�}�b�g�̏�����
	ZeroMemory(&pcmWF, sizeof(WAVEFORMATEX));
	pcmWF.wFormatTag = WAVE_FORMAT_PCM;			//Wave�t�H�[�}�b�g
	pcmWF.nChannels = 2;						//2�`�����l��(�X�e���I)
	pcmWF.nSamplesPerSec = 22050;				//�T���v�����O�E���[�g(22kHz)
	pcmWF.nBlockAlign = 4;						//�u���b�N�E�A���C�����g
	pcmWF.nAvgBytesPerSec = pcmWF.nSamplesPerSec * pcmWF.nBlockAlign;	//1�b�Ԃ̃f�[�^�]���T�C�Y
	pcmWF.wBitsPerSample = 16;					//16�r�b�g


	//DSBUFFERDESC�\���̂̃Z�b�g
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//�T�E���h�E�o�b�t�@���쐬
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	
	//��Őݒ肵��Wave�t�H�[�}�b�g������3�b�̃o�b�t�@���쐬
	dsBufDesc.dwBufferBytes = 3 * pcmWF.nAvgBytesPerSec;		//3�b�̓]���o�C�g��
	dsBufDesc.lpwfxFormat = &pcmWF;

	//�o�b�t�@���쐬
	LPDIRECTSOUNDBUFFER		pDSB;
	if (FAILED(pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSB, NULL)))
	{
		MessageBox(NULL, TEXT("�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSecondaryBuf"), MB_OK);
		return false;
	}

	//IDirectSoundBuffer8�C���^�[�t�F�C�X�����o��
	if (FAILED(pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)pDirectSound)))
	{
		MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̎擾�Ɏ��s���܂���"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	pDSB->Release();

	return true;
}



//8:�Z�J���_���E�o�b�t�@�ւ̏�������
bool	Sound::WriteSecondaryBuffer()
{
	DWORD	dwOffset = 0;		//���b�N���J�n����A�o�b�t�@�̐擪����̃o�C�g����ݒ�
	DWORD	dwBlockBytes = 0;//���b�N����u���b�N�̃o�C�g����ݒ�

	LPVOID	lpvPtr1 = {};		//�ŏ��̃u���b�N�̃|�C���^
	DWORD	dwBytes1 = {};		//�ŏ��̃u���b�N�̃T�C�Y
	LPVOID	lpvPtr2 = {};		//2�Ԗڂ̃u���b�N�̃|�C���^
	DWORD	dwBytes2 = {};		//2�Ԗڂ̃u���b�N�̃T�C�Y
	HRESULT hr = S_OK;

	hr = pDirectSoundBuf->Lock(dwOffset, dwBlockBytes,
		&lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	//DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�ARestore()���g�p���o�b�t�@�𕜌�
	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();
		//hr = pDirectSoundBuf->Lock(dwOffset,dwSoundBytes,
		//	&lpvPtr1, &dwAudio1, &lpvPtr2, &dwAudio2, 0);
	}
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("�Z�J���_���o�b�t�@�̃��b�N�Ɏ��s���܂���"), TEXT("Lock"), MB_OK);
		return false;
	}
	

	//�o�b�t�@�ɏ�������


	//�������݂��I��������AUnlock����
	hr = pDirectSoundBuf->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);

	return true;
}




//9:�Z�J���_���o�b�t�@�̃t�H�[�}�b�g�̐ݒ�
bool	Sound::SecondarySetFormat(LPTSTR fileName)
{
	//WAVE�t�@�C�����J��
	CWaveFile	waveFile;
	waveFileName = fileName;
	if (FAILED(waveFile.Open(waveFileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Wave�t�@�C���̃I�[�v���Ɏ��s"), TEXT("Open"), MB_OK);
		return false;
	}

	//�Z�J���_���E�o�b�t�@�̍쐬
	DSBUFFERDESC	dsBufDesc;
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsBufDesc.dwBufferBytes = waveFile.GetSize();
	dsBufDesc.lpwfxFormat = waveFile.GetFormat();
	
	//�o�b�t�@�̍쐬
	LPDIRECTSOUNDBUFFER		pDSBuf;
	if (FAILED(pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
	{
		MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̍쐬�Ɏ��s"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}
	
	//SoundBuffer�̃C���^�[�t�F�C�X�̎擾
	HRESULT hr;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDirectSoundBuf);
	SAFE_RELEASE(pDSBuf);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("SoundBuf�̃C���^�[�t�F�C�X�̎擾�Ɏ��s"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	
	//�Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID	lpvPtr1 = NULL;
	DWORD	dwByte1 = 0;
	LPVOID	lpvPtr2 = NULL;
	DWORD	dwByte2 = 0;

	hr = pDirectSoundBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	
	//DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�ARestore()�Ńo�b�t�@�𕜌�
	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();
		hr = pDirectSoundBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	}
	if (SUCCEEDED(hr))
	{
		//�o�b�t�@�ɏ�������
		DWORD	rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
		if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

		//�������ݏI����AUnlock����
		hr = pDirectSoundBuf->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
	}
	return true;
}



//10:�T�E���h�����������L����Z�J���_���o�b�t�@
bool	Sound::DuplicateSoundBuf()
{
	LPDIRECTSOUNDBUFFER	pDSB = {};
	pDirectSound->DuplicateSoundBuffer(pDirectSoundBuf, &pNewSoundBuf);
	pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pNewSoundBuf);
	pDSB->Release();
	return true;
}



//11:�T�E���h�̍Đ�
bool	Sound::Play(bool loop)
{
	HRESULT hr;
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDirectSoundBuf->SetCurrentPosition(0);	//�擪����Đ�
	
	hr = pDirectSoundBuf->Play(0, 0, flags);
	
	if(hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();		//����ꂽ�T�E���h�������𕜌�
		//�T�E���h�o�b�t�@��ݒ肵�Ȃ���
	}
	return true;
}

bool	Sound::Stop()
{
	pDirectSoundBuf->Stop();
	return true;
}



//�{�����[���̐ݒ�
bool	Sound::SetVolume(LONG volume)
{
	pDirectSoundBuf->SetVolume(volume);
	return true;
}

//�p���̐ݒ�
bool	Sound::SetPan(LONG pan)
{
	//�p���̒l��1/100dB�P�ʂŐݒ�
	//�E�`�����l����������[-10000]�A���`�����l����������[10000]
	pDirectSoundBuf->SetPan(pan);
	return true;
}


//���g���̐ݒ�
bool	Sound::SetFrequency(DWORD frequency)
{
	//�Đ�������g����Hz�P�ʂŐݒ�
	//min(100)����max(100000)�܂ł̒l
	pDirectSoundBuf->SetFrequency(frequency);
	return true;
}

//�I�u�W�F�N�g�̍폜
void	Sound::BufRelease()
{
	if (pDirectSound != NULL) { pDirectSoundBuf->Release(); pDirectSound = NULL; }
}

void	Sound::InterfaceRelease()
{
	if (pDirectSound != NULL) { pDirectSoundBuf->Release(); pDirectSound = NULL; }
}





//------------------------------------------------------------------
//�T�E���h�f�o�C�X�̃V���O���g���N���X
//------------------------------------------------------------------
SoundDevice::SoundDevice() : pDirectSound(NULL), pDSoundGuid(NULL)
{

}

//��������
SoundDevice*	SoundDevice::Instance()
{
	if (instance == NULL)
	{
		instance = new SoundDevice;
	}
	return instance;
}


//---------------------------------------------------------
//�����o����
//---------------------------------------------------------
//�T�E���h�E�f�o�C�X�̎擾
bool	SoundDevice::DSoundEnumCallBack()
{

	//DirectSoundEnumerate((LPDSENUMCALLBACK)DSEnumProc, &hCombo);
	return true;
}
BOOL CALLBACK SoundDevice::DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	HWND hCombo = (HWND)lpContext;
	LPGUID lpTemp = NULL;

	if (lpGUID != NULL)
	{
		if ((lpTemp = (LPGUID)malloc(sizeof(GUID))) == NULL)
		{
			return true;
		}
		memcpy(lpTemp, lpGUID, sizeof(GUID));
	}

	//ComboBox_AddString(hCombo, lpszDesc);
	//ComboBox_SetItemData(hCombo, ComboBox_FindString(hCombo, 0, lpszDesc), lpTemp);
	free(lpTemp);
	lpTemp = NULL;

	return true;
}


//2:DirectSound�I�u�W�F�N�g�̍쐬
bool	SoundDevice::DSoundCreate()
{
	if (FAILED(DirectSoundCreate8(
		NULL,		//�f�t�H���g�ł�NULL�AGUID���擾����Ȃ�pDSoundGuid
		&pDirectSound,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("DirectSound�I�u�W�F�N�g�̐����Ɏ��s���܂���"), TEXT("DSoundCreate"), MB_OK);
		return false;
	}
	return true;
}



//3:�������x���̐ݒ�
bool	SoundDevice::SetCooperativeLevel(HWND hWnd)
{
	if (FAILED(pDirectSound->SetCooperativeLevel(
		hWnd, DSSCL_PRIORITY
	)))
	{
		MessageBox(NULL, TEXT("�������x���̐ݒ�Ɏ��s���܂���"), TEXT("SetCooperativeLevel"), MB_OK);
		return false;
	}
	return true;
}




//4:�f�o�C�X�̐��\�̒���
bool	SoundDevice::GetCaps()
{
	dsCaps.dwSize = sizeof(DSCAPS);	//�K��������

	if (FAILED(pDirectSound->GetCaps(&dsCaps)))
	{
		MessageBox(NULL, TEXT("�f�o�C�X�̐��\�̎擾�Ɏ��s���܂���"), TEXT("GetCaps"), MB_OK);
		return false;
	}
	return true;
}



//5:�X�s�[�J�[�̒���
bool	SoundDevice::GetSpeakerConfig()
{
	if (FAILED(pDirectSound->GetSpeakerConfig(&dwSpeakerConfig)))
	{
		MessageBox(NULL, TEXT("�X�s�[�J�[�̏��̎擾�Ɏ��s���܂���"), TEXT("GetSpeakerConfig"), MB_OK);
		return false;
	}

	switch (DSSPEAKER_CONFIG(dwSpeakerConfig))
	{
	case DSSPEAKER_5POINT1:		//�T�u�E�[�t�@�t����5�T���E���h�E�X�s�[�J�[
		break;
	case DSSPEAKER_DIRECTOUT:	//�X�s�[�J�[�p�̍\���͍s���Ȃ�
		break;
	case DSSPEAKER_HEADPHONE:	//�w�b�h�z��
		break;
	case DSSPEAKER_MONO:		//���m�����E�X�s�[�J�[
		break;
	case DSSPEAKER_QUAD:		//4�`�����l���E�X�e���I�E�X�s�[�J�[
		break;
	case DSSPEAKER_STEREO:		//�X�e���I�E�X�s�[�J�[

								//2�̃X�s�[�J�[�̔z�u
		switch (DSSPEAKER_GEOMETRY(dwSpeakerConfig))
		{
		case DSSPEAKER_GEOMETRY_WIDE:		//���X�i�[�𒆐S�Ƃ���20�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_NARROW:		//���X�i�[�𒆐S�Ƃ���10�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_MIN:		//���X�i�[�𒆐S�Ƃ���5�x�̊p�x
			break;
		case DSSPEAKER_GEOMETRY_MAX:		//���X�i�[�𒆐S�Ƃ���180�x�̊p�x
			break;
		}
		break;

	case DSSPEAKER_SURROUND:	//�T���E���h�E�X�s�[�J�[
		break;
	case DSSPEAKER_7POINT1:		//�T�u�E�[�t�@�t����7�T���E���h�E�X�s�[�J�[
		break;
	}
	return true;
}





////6:�v���C�}���E�o�b�t�@�̍쐬
//bool	SoundDevice::CreateSoundBuffer()
//{
//	//DSBUFFERDESC�\���̂�ݒ�
//	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
//	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
//
//	//�v���C�}���E�o�b�t�@���w��
//	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
//	dsBufDesc.dwBufferBytes = 0;
//	dsBufDesc.lpwfxFormat = NULL;
//
//
//	//�o�b�t�@�̍쐬
//	if (FAILED(pDirectSound->CreateSoundBuffer(
//		&dsBufDesc, &pDirectSoundBuf, NULL
//	)))
//	{
//		MessageBox(NULL, TEXT("�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuffer"), MB_OK);
//		return false;
//	}
//
//
//	//�v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
//	//�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������
//	PCMWAVEFORMAT	pcmWF;
//	ZeroMemory(&pcmWF, sizeof(PCMWAVEFORMAT));
//	pcmWF.wf.wFormatTag = WAVE_FORMAT_PCM;		//Wave�̃t�H�[�}�b�g
//	pcmWF.wf.nChannels = 2;						//2�`�����l��(�X�e���I)
//	pcmWF.wf.nSamplesPerSec = 22050;			//�T���v�����O�E���[�g	22kHz
//	pcmWF.wf.nBlockAlign = 4;
//	pcmWF.wf.nAvgBytesPerSec = pcmWF.wf.nSamplesPerSec * pcmWF.wf.nBlockAlign;	//�Œ�
//	pcmWF.wBitsPerSample = 16;					//16�r�b�g
//
//	pDirectSoundBuf->SetFormat((LPCWAVEFORMATEX)&pcmWF);	//�o�b�t�@�Ƀt�H�[�}�b�g���Z�b�g
//
//	return true;
//}