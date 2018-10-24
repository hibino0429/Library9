#include "SoundManager.h"

SoundDevice* sd = SoundDevice::Instance();

//�T�E���h�f�o�C�X�̐���
bool	SoundManager::Create(HWND hWnd)
{
	//1:�T�E���h�f�o�C�X�̗�

	//2:IDirectSound8�C���^�[�t�F�C�X�̎擾
	sound.DSoundCreate();

	//3:�������x���̐ݒ�
	sound.SetCooperativeLevel(hWnd);

	//4:�f�o�C�X�̐��\�̒���
	sound.GetCaps();

	//5:�X�s�[�J�̒���
	sound.GetSpeakerConfig();

	//6:�v���C�}���o�b�t�@�̐���
	sound.CreateSoundBuffer();

	return true;
}


//�Z�J���_���o�b�t�@�̍쐬
void	SoundManager::LoadSound(LPTSTR fileName)
{
	if (fileName == sound.waveFileName)
	{
		sound.DuplicateSoundBuf();
	}
	sound.SecondarySetFormat(fileName);
}

//�Z�J���_���o�b�t�@�̍Đ�
void	SoundManager::Play(bool loop)
{
	sound.Play(loop);
}

//�Z�J���_���o�b�t�@�̒�~
void	SoundManager::Stop()
{
	sound.Stop();
}

//�{�����[���̐ݒ�
void	SoundManager::SetVolume(LONG valume)
{
	sound.SetVolume(valume);
}

//�p���̐ݒ�
void	SoundManager::SetPan(LONG pan)
{
	sound.SetPan(pan);
}

//�Đ����g���̐ݒ�
void	SoundManager::SetFrequency(DWORD frequency)
{
	sound.SetFrequency(frequency);
}







namespace SE2
{
	//�T�E���h�f�o�C�X�̐���
	bool	Create(HWND hWnd)
	{
		//1:�T�E���h�f�o�C�X�̗�

		//2:IDirectSound8�C���^�[�t�F�C�X�̎擾
		se.DSoundCreate();

		//3:�������x���̐ݒ�
		se.SetCooperativeLevel(hWnd);

		//4:�f�o�C�X�̐��\�̒���
		se.GetCaps();

		//5:�X�s�[�J�̒���
		se.GetSpeakerConfig();

		//6:�v���C�}���o�b�t�@�̐���
		se.CreateSoundBuffer();

		return true;
	}


	//�Z�J���_���o�b�t�@�̍쐬
	void	LoadSound(LPTSTR fileName)
	{
		if (fileName == se.waveFileName)
		{
			se.DuplicateSoundBuf();
		}
		se.SecondarySetFormat(fileName);
	}

	//�Z�J���_���o�b�t�@�̍Đ�
	void	Play(bool loop)
	{
		se.Play(loop);
	}

	//�Z�J���_���o�b�t�@�̒�~
	void	Stop()
	{
		se.Stop();
	}

	//�{�����[���̐ݒ�
	void	SetVolume(LONG valume)
	{
		se.SetVolume(valume);
	}

	//�p���̐ݒ�
	void	SetPan(LONG pan)
	{
		se.SetPan(pan);
	}

	//�Đ����g���̐ݒ�
	void	SetFrequency(DWORD frequency)
	{
		se.SetFrequency(frequency);
	}

}







//---------------------------------------------------------------------------------------------
//�T�E���h�f�o�C�X�̃V���O���g���N���X�𗘗p�����Z�J���_���T�E���h
//---------------------------------------------------------------------------------------------

//�R���X�g���N�^
Sounds::Sounds() : pDirectSoundBuf(NULL), pNewSoundBuf(NULL)
{

}

//�f�X�g���N�^
Sounds::~Sounds()
{
	if (pDirectSoundBuf != NULL) { pDirectSoundBuf->Release(); pDirectSoundBuf = NULL; }
	if (pNewSoundBuf != NULL) { pNewSoundBuf->Release(); pNewSoundBuf = NULL; }
}

//9:�Z�J���_���o�b�t�@�̃t�H�[�}�b�g�̐ݒ�
bool	Sounds::SecondarySetFormat(LPTSTR fileName)
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
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
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
bool	Sounds::DuplicateSoundBuf()
{
	LPDIRECTSOUNDBUFFER	pDSB = NULL;
	sd->pDirectSound->DuplicateSoundBuffer(pDirectSoundBuf, &pNewSoundBuf);
	pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pNewSoundBuf);
	pDSB->Release();
	return true;
}



//11:�T�E���h�̍Đ�
bool	Sounds::Play(bool loop)
{
	HRESULT hr;
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDirectSoundBuf->SetCurrentPosition(0);	//�擪����Đ�

	hr = pDirectSoundBuf->Play(0, 0, flags);

	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();		//����ꂽ�T�E���h�������𕜌�
										//�T�E���h�o�b�t�@��ݒ肵�Ȃ���
	}
	return true;
}

bool	Sounds::Stop()
{
	pDirectSoundBuf->Stop();
	return true;
}



//�{�����[���̐ݒ�
bool	Sounds::SetVolume(LONG volume)
{
	pDirectSoundBuf->SetVolume(volume);
	return true;
}

//�p���̐ݒ�
bool	Sounds::SetPan(LONG pan)
{
	//�p���̒l��1/100dB�P�ʂŐݒ�
	//�E�`�����l����������[-10000]�A���`�����l����������[10000]
	pDirectSoundBuf->SetPan(pan);
	return true;
}


//���g���̐ݒ�
bool	Sounds::SetFrequency(DWORD frequency)
{
	//�Đ�������g����Hz�P�ʂŐݒ�
	//min(100)����max(100000)�܂ł̒l
	pDirectSoundBuf->SetFrequency(frequency);
	return true;
}




bool	Sounds::LoadSound(LPTSTR fileName)
{
	CreateSoundBuffer();

	if (fileName == waveFileName)
	{
		//DuplicateSoundBuf();
		return false;
	}
	SecondarySetFormat(fileName);

	return true;
}


//6:�v���C�}���E�o�b�t�@�̍쐬
bool	Sounds::CreateSoundBuffer()
{
	//DSBUFFERDESC�\���̂�ݒ�
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//�v���C�}���E�o�b�t�@���w��
	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//�o�b�t�@�̍쐬
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(
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






namespace SE
{
	//�T�E���h�f�o�C�X�̐���
	bool	Create(HWND hWnd)
	{
		//1:�T�E���h�f�o�C�X�̗�

		//2:IDirectSound8�C���^�[�t�F�C�X�̎擾
		sd->DSoundCreate();

		//3:�������x���̐ݒ�
		sd->SetCooperativeLevel(hWnd);

		//4:�f�o�C�X�̐��\�̒���
		sd->GetCaps();

		//5:�X�s�[�J�̒���
		sd->GetSpeakerConfig();

		//6:�v���C�}���o�b�t�@�̐���
		//sd->CreateSoundBuffer();

		return true;
	}

}



////////////////////////////////////////////////////////////////////////
//�R���X�g���N�^
StreamSound::StreamSound() : pDirectSoundData(NULL),pDirectSoundNotify(NULL),
hThreadHandle(NULL),dwThreadID(0),dwBlockSize(0),dwPlayAdd(0)
{
	for (int i = 0; i < 3; ++i) { hEvent[i] = NULL; }
}

//�f�X�g���N�^
StreamSound::~StreamSound()
{
	if (pDirectSoundData != NULL) { pDirectSoundData->Release(); pDirectSoundData = NULL; }
	if (pDirectSoundNotify != NULL) { pDirectSoundNotify->Release(); pDirectSoundNotify = NULL; }
	if (hThreadHandle != NULL) { hThreadHandle = NULL; }
	dwThreadID = 0;
	dwBlockSize = 0;
	dwPlayAdd = 0;
	for (int i = 0; i < 3; ++i) { hEvent[i] = NULL; }
}


//�X�g���[���Đ�
bool	StreamSound::CreateNotify(LPTSTR fileName)
{
	CWaveFile	waveFile;
	waveFile.Open(fileName, NULL, WAVEFILE_READ);

	//1:Notify�C���^�[�t�F�C�X�̎擾
	if (FAILED(pDirectSoundNotify->QueryInterface(
		IID_IDirectSoundNotify8,
		(LPVOID*)&pDirectSoundNotify)))
	{
		MessageBox(NULL, TEXT("Notify8�̍쐬�Ɏ��s���܂���"), TEXT("pDirectNotifyQueryInterface"), MB_OK);
		return false;
	}

	//2:�ʒm�C�x���g�̃I�u�W�F�N�g�̍쐬
	HANDLE	hEvent[3];
	//����1:�f�t�H���g�B�Z�L�����e�B����
	//����2:�������Z�b�g(FALSE)
	//����3:������� - ��V�O�i��(FALSE)
	//����4:���O
	hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent[2] = CreateEvent(NULL, FALSE, FALSE, NULL);

	
	//3:�ʒm�ʒu�̐ݒ�
	DSBPOSITIONNOTIFY	posNotify[3];

	posNotify[0].dwOffset = 0;		//0�b��
	posNotify[0].hEventNotify = hEvent[0];
	posNotify[1].dwOffset = 1;		//1�b��
	posNotify[1].hEventNotify = hEvent[1];
	posNotify[2].dwOffset = DSBPN_OFFSETSTOP;		//�Đ���~
	posNotify[2].hEventNotify = hEvent[2];

	//��~�ʒu�̐ݒ�
	//����1:�\���̂̐�
	//����2:�\���̂̃|�C���^
	if (FAILED(pDirectSoundNotify->SetNotificationPositions(3, posNotify)))
	{
		MessageBox(NULL, TEXT("��~�ʒu�̐ݒ�Ɏ��s���܂���"), TEXT("SetNotifyPos"), MB_OK);
		return false;
	}
	return true;
}


//�X���b�h�̍쐬
bool	StreamSound::CreateThreadNotify()
{
	HANDLE hThreadHandle;		//�X���b�h�̃n���h��
	DWORD	dwThreadID;			//�X���b�h��ID
	hThreadHandle = CreateThread(NULL, 0,MyThreadFunc, NULL, 0, &dwThreadID);
	if (hThreadHandle == NULL)
	{
		MessageBox(NULL, TEXT("�X���b�h�̐����Ɏ��s���܂���"), TEXT("CreateThread"), MB_OK);
		return false;
	}
	return true;
}


//�T�E���h�o�b�t�@�փR�s�[����
void	StreamSound::Block_Copy(UINT i)
{
	//��x�X�V����f�[�^�T�C�Y(�T�E���h�o�b�t�@�̔���)
	UINT dsize = (UINT)dwBlockSize / 2;

	//�o�b�t�@�����b�N
	LPBYTE	blockAdd1, blockAdd2;
	DWORD	blockSize1, blockSize2;

	if (FAILED(pDirectSoundData->Lock(dsize * i, dsize,
		(LPVOID*)&blockAdd1, &blockSize1,
		(LPVOID*)&blockAdd2, &blockSize2, 0)))
	{
		MessageBox(NULL, TEXT("�o�b�t�@�̃��b�N�Ɏ��s���܂���"), TEXT("Block_Copy"), MB_OK);
		return;
	}

	//�o�b�t�@�̑O���Ƀf�[�^���R�s�[
	UINT rsize, asize;
	for (asize = 0; asize < blockSize1; asize += rsize)
	{
		waveFile.Read((BYTE*)blockSize1 - asize, (DWORD)blockAdd1 + asize, (DWORD*)&rsize);
		if (rsize == 0) { break; }
		if (blockSize1 - asize != rsize)
		{
			waveFile.ResetFile();	//�t�@�C���������߂�
		}
	}

	//�o�b�t�@�̌㔼�Ƀf�[�^���R�s�[
	for (asize = 0; asize < blockSize2; asize += rsize)
	{
		waveFile.Read((BYTE*)blockSize2 - asize, (DWORD)blockAdd2 + asize, (DWORD*)&rsize);
		if (rsize == 0) { break; }
		if (blockSize2 - asize != rsize)
		{
			waveFile.ResetFile();	//�t�@�C���������߂�
		}
	}

	//�o�b�t�@�̃A�����b�N
	pDirectSoundData->Unlock(blockAdd1, blockSize1, blockAdd2, blockSize2);
}


DWORD	WINAPI	StreamSound::MyThreadFunc(LPVOID param)
{
	////�o�b�t�@��1�Ԗڂ̃u���b�N�Ƀf�[�^����������
	//Block_Copy(0);
	//
	//pDirectSoundData->Play(0, 0, DSBPLAY_LOOPING);

	////�f�[�^���������ޖ������[�v�ɓ���
	//while (true)
	//{
	//	//DirectSoundBuffer����̃C�x���g�ʒm��҂�
	//	DWORD i = WaitForMultipleObjects(3, StreamSound::hEvent, FALSE, INFINITE);
	//	//�C�x���g��������A���ꂩ��Đ������u���b�N�̎��̃u���b�N�ɏ�������
	//	switch (i)
	//	{
	//	case WAIT_OBJECT_0:
	//		//�Q�Ԗڂ̃u���b�N�ɏ�������
	//		Block_Copy(1);
	//		break;
	//	case WAIT_OBJECT_0 + 1:
	//		Block_Copy(0);
	//		break;
	//	case WAIT_OBJECT_0 + 2:
	//	default:
	//		//�Đ��I�����ɁA�X���b�h���I������
	//		ExitThread(TRUE);
	//	}
	//}
	return 0L;
}






//------------------------------------------------------
//3D�T�E���h
//------------------------------------------------------

//�R���X�g���N�^
Sound3D::Sound3D() : pPrimaryBuf(NULL)
{

}

//�f�X�g���N�^
Sound3D::~Sound3D()
{
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
}


//�v���C�}���E�o�b�t�@�̍쐬
bool	Sound3D::CreatePrimary(LPTSTR fileName)
{
	sd->DSoundCreate();
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Wave�t�@�C���̃I�[�v���Ɏ��s���܂���"), TEXT("Open"), MB_OK);
		return false;
	}

	DSBUFFERDESC	dsBufDesc;
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//�T�E���h�o�b�t�@���쐬
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pPrimaryBuf, NULL)))
	{
		MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}


	//�T�E���h�o�b�t�@�̍쐬
	LPDIRECTSOUNDBUFFER		pDSBuf = {};
	//SoundBuffer�̃C���^�[�t�F�C�X�̎擾
	HRESULT hr = S_OK;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pPrimaryBuf);
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

	hr = pPrimaryBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);

	//DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�ARestore()�Ńo�b�t�@�𕜌�
	if (hr == DSERR_BUFFERLOST)
	{
		pPrimaryBuf->Restore();
		hr = pPrimaryBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	}
	if (SUCCEEDED(hr))
	{
		//�o�b�t�@�ɏ�������
		DWORD	rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
		if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

		//�������ݏI����AUnlock����
hr = pPrimaryBuf->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
	}

	return true;
}

//�����̍쐬
bool	Sound3D::CreateSource()
{
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DBuffer8,
		(LPVOID*)&pSource)))
	{
		MessageBox(NULL, TEXT("�����̍쐬�Ɏ��s���܂���"), TEXT("CreateSource"), MB_OK);
		return false;
	}
	return true;
}

//�ŏ�����
void	Sound3D::SetMinDistance(float minDist, DWORD apply)
{
	pSource->SetMinDistance(minDist, apply);
}
//�ő勗��
void	Sound3D::SetMaxDistance(float maxDist, DWORD apply)
{
	pSource->SetMaxDistance(maxDist, apply);
}

//3D�T�E���h�������[�h�̐ݒ�
void	Sound3D::SetMode(DWORD mode, DWORD apply)
{
	//�W�����[�h	(D3DMODE_NORMAL)
	//���΃��[�h	(D3DMODE_HEADRELATIVE)
	//�������[�h	(D3DMODE_DISABLE)
	if (FAILED(pSource->SetMode(mode, apply)))
	{
		MessageBox(NULL, TEXT("���[�h�̐ݒ�Ɏ��s���܂���"), TEXT("SetMode"), MB_OK);
		return;
	}
}

//�ʒu�Ƒ��x�̐ݒ�
void	Sound3D::SetPositionSource(float x, float y, float z, DWORD apply)
{
	pSource->SetPosition(x, y, z, apply);
}
void	Sound3D::SetVelocitySource(float vx, float vy, float vz, DWORD apply)
{
	pSource->SetVelocity(vx, vy, vz, apply);
}

//�T�E���h�R�[���̐ݒ�
void	Sound3D::SetConeAngle(DWORD insideConeAngle, DWORD outsideConeAngle, DWORD apply)
{
	pSource->SetConeAngles(insideConeAngle, outsideConeAngle, apply);
}

//�R�[���̌����̐ݒ�
void	Sound3D::SetConeOrientation(float x, float y, float z, DWORD apply)
{
	pSource->SetConeOrientation(x, y, z, apply);
}

//�O���R�[���̉��ʂ̐ݒ�
void	Sound3D::SetConeOutsideVolume(LONG coneOutsideVolume, DWORD apply)
{
	pSource->SetConeOutsideVolume(coneOutsideVolume, apply);
}

//�������特��炷
void	Sound3D::Play(bool loop)
{
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDSBuf8->Play(0, 0, flags);
}


//��-------------------------
bool	Sound3D::PrimaryBufCreate()
{
	//DSBUFFERDESC�\���̂�ݒ�
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//�o�b�t�@�̒��g�̐ݒ�
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;

	//�v���C�}���o�b�t�@�̍쐬
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pPrimaryBuf, NULL)))
	{
		MessageBox(NULL, TEXT("�v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}
	

	//���X�i�[�̍쐬
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&pListener)))
	{
		MessageBox(NULL, TEXT("���X�i�[�̍쐬�Ɏ��s"), TEXT("Error"), MB_OK);
		return false;
	}
	pListener->SetPosition(0, 0, 0, DS3D_IMMEDIATE);
	pListener->SetVelocity(0, 0, 0, DS3D_IMMEDIATE);
	pListener->SetOrientation(0, 0, 1.0f, 0, 1.0f, 0, DS3D_IMMEDIATE);
	pListener->SetRolloffFactor(1.0f, DS3D_IMMEDIATE);
	pListener->SetDopplerFactor(DS3D_MAXDOPPLERFACTOR, DS3D_IMMEDIATE);

	return true;
}


//����Second
bool	Sound3D::SecondaryBufCreate(LPTSTR fileName)
{
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("�v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}

	//�Z�J���_���o�b�t�@�̍쐬
	//DSBUFFERDESC dsbdesc;
	//ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	//dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	//dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRL3D;
	//dsbdesc.dwBufferBytes = waveFile.GetSize();
	//dsbdesc.lpwfxFormat = waveFile.GetFormat();
	//dsbdesc.guid3DAlgorithm = DS3DALG_HRTF_FULL;	// �Ƃ肠�����������̃A���S���Y����v�����Ă���

	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY ;
	dsBufDesc.dwBufferBytes = waveFile.GetSize();
	dsBufDesc.lpwfxFormat = waveFile.GetFormat();

	//�Z�J���_���o�b�t�@�̍쐬
	LPDIRECTSOUNDBUFFER		pDSBuf;
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
	{
		MessageBox(NULL, TEXT("�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}
	
	if (FAILED(pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSBuf8)))
	{
		MessageBox(NULL, TEXT("Sound3D�C���^�[�t�F�C�X�̎擾�Ɏ��s���܂���"), TEXT("Query"), MB_OK);
		return false;
	}
	if (pDSBuf != NULL) { pDSBuf->Release(); pDSBuf = NULL; }

	if (FAILED(pDSBuf8->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pSource)))
	{
		MessageBox(NULL, TEXT("3D�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("Error"), MB_OK);
		return false;
	}
	
	//�Z�J���_���o�b�t�@��Wave�f�[�^����������
	HRESULT hr;
	LPVOID lpvPtr1; 	// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1; 	// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2; 	// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2; 	// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSBuf8->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr)
	{
		pDSBuf8->Restore();
		hr = pDSBuf8->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		DWORD rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwBytes1, &rsize);
		if (0 != dwBytes2)
			waveFile.Read((LPBYTE)lpvPtr2, dwBytes2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSBuf8->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	pSource->SetMinDistance(1.0f, DS3D_IMMEDIATE);
	pSource->SetMaxDistance(10.0f, DS3D_IMMEDIATE);
	pSource->SetPosition(1, 0, 0, DS3D_IMMEDIATE);
	pSource->SetVelocity(2, 2, 2, DS3D_IMMEDIATE);
	pSource->SetConeOutsideVolume(100, DS3D_IMMEDIATE);

	pDSBuf8->Play(0, 0, DSBPLAY_LOOPING);

	return true;
}


/////////////////////////////////////////////////////

//�T�E���h
namespace Audio
{
	bool	CreateSoundDevice(HWND hWnd)
	{
		//1:IDirectSound8�C���^�[�t�F�C�X�̎擾
		if (!sd->DSoundCreate())
		{
			return false;
		}

		//2:�������x���̐ݒ�
		sd->SetCooperativeLevel(hWnd);

		//3:�f�o�C�X�̐��\�̒���
		sd->GetCaps();

		//4:�X�s�[�J�̒���
		sd->GetSpeakerConfig();
		return true;
	}

	//�T�E���h�̍쐬
	bool	CreateAudio(LPTSTR fileName,LPDIRECTSOUNDBUFFER* pBuf)
	{
		CWaveFile	waveFile;
		if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
		{
			MessageBox(NULL, TEXT("Wave�t�@�C���̃I�[�v���Ɏ��s���܂���"), TEXT("Open"), MB_OK);
			return false;
		}

		DSBUFFERDESC	dsBufDesc;
		dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
		dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsBufDesc.dwBufferBytes = 0;
		dsBufDesc.lpwfxFormat = NULL;


		//�T�E���h�o�b�t�@���쐬
		if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, pBuf, NULL)))
		{
			MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuf"), MB_OK);
			return false;
		}


		//�T�E���h�o�b�t�@�̍쐬
		LPDIRECTSOUNDBUFFER		pDSBuf = {};
		//SoundBuffer�̃C���^�[�t�F�C�X�̎擾
		HRESULT hr = S_OK;
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuf);
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

		hr = (*pBuf)->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);

		//DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�ARestore()�Ńo�b�t�@�𕜌�
		if (hr == DSERR_BUFFERLOST)
		{
			(*pBuf)->Restore();
			hr = (*pBuf)->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
		}
		if (SUCCEEDED(hr))
		{
			//�o�b�t�@�ɏ�������
			DWORD	rsize;
			waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
			if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

			//�������ݏI����AUnlock����
			hr = (*pBuf)->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
		}

		return true;
	}


	//�T�E���h�o�b�t�@�̐���
	bool	CreateSoundBuf(DSBUFFERDESC* dsBufDesc, LPDIRECTSOUNDBUFFER* pBuf)
	{
		DSBUFFERDESC	dsBufDesc2;
		dsBufDesc2.dwSize = sizeof(DSBUFFERDESC);
		dsBufDesc2.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsBufDesc2.dwBufferBytes = 0;
		dsBufDesc2.lpwfxFormat = NULL;

		//�T�E���h�o�b�t�@���쐬
		if (FAILED(sd->pDirectSound->CreateSoundBuffer(dsBufDesc,pBuf, NULL)))
		{
			MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("CreateSoundBuf"), MB_OK);
			return false;
		}
		MessageBox(NULL, TEXT("�f�o�C�X�̊m�ۂɂ͐������܂���"), TEXT("�T�E���h�f�o�C�X"), MB_OK);
		return true;
	}

	//�T�E���h�o�b�t�@�̃C���^�[�t�F�C�X�̎擾
	bool	QueryInterface()
	{
		LPDIRECTSOUNDBUFFER		pDSBuf = {};
		if (FAILED(pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)sd->pDirectSound)))
		{
			MessageBox(NULL, TEXT("�T�E���h�o�b�t�@�̃C���^�[�t�F�C�X�̎擾�Ɏ��s���܂���"), TEXT("QueryInterface"), MB_OK);
			return false;
		}
		SAFE_RELEASE(pDSBuf);
		return true;
	}

	LPDIRECTSOUND8*	GetDirectSound()
	{
		return &sd->pDirectSound;
	}

}