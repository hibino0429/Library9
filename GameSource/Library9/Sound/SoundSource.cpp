#include "SoundSource.h"


//�R���X�g���N�^
SoundSource::SoundSource() : pSource(NULL),pPrimaryBuf(NULL),pDSBuf(NULL)
{

}
//�f�X�g���N�^
SoundSource::~SoundSource()
{
	if (pSource != NULL) { pSource->Release(); pSource = NULL; }
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
	if (pDSBuf != NULL) { pDSBuf->Release(); pDSBuf = NULL; }
}

//���̐���
bool	SoundSource::CreateSound(LPTSTR fileName)
{
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Wave�t�@�C���̃I�[�v���Ɏ��s���܂���"), TEXT("Open"), MB_OK);
		return false;
	}


	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRL3D;
	//dsBufDesc.dwBufferBytes = waveFile.GetSize();
	//dsBufDesc.lpwfxFormat = waveFile.GetFormat();
	//dsBufDesc.guid3DAlgorithm = DS3DALG_HRTF_FULL;	// �Ƃ肠�����������̃A���S���Y����v�����Ă���


	//�T�E���h�o�b�t�@�̍쐬
	Audio::CreateSoundBuf(&dsBufDesc, &pDSBuf);
	

	//�T�E���h�o�b�t�@�̍쐬
	//SoundBuffer�̃C���^�[�t�F�C�X�̎擾
	HRESULT hr;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pPrimaryBuf);
	SAFE_RELEASE(pDSBuf);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("SoundBuf�̃C���^�[�t�F�C�X�̎擾�Ɏ��s"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	

	hr = pPrimaryBuf->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pSource);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Sound3DBuf�̎擾�Ɏ��s���܂���"), TEXT("pPrimary"), MB_OK);
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
bool	SoundSource::CreateSource()
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
void	SoundSource::SetMinDistance(float minDist, DWORD apply)
{
	pSource->SetMinDistance(minDist, apply);
}
//�ő勗��
void	SoundSource::SetMaxDistance(float maxDist, DWORD apply)
{
	pSource->SetMaxDistance(maxDist, apply);
}

//3D�T�E���h�������[�h�̐ݒ�
void	SoundSource::SetMode(DWORD mode, DWORD apply)
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
void	SoundSource::SetPositionSource(float x, float y, float z, DWORD apply)
{
	pSource->SetPosition(x, y, z, apply);
}
void	SoundSource::SetVelocitySource(float vx, float vy, float vz, DWORD apply)
{
	pSource->SetVelocity(vx, vy, vz, apply);
}

//�T�E���h�R�[���̐ݒ�
void	SoundSource::SetConeAngle(DWORD insideConeAngle, DWORD outsideConeAngle, DWORD apply)
{
	pSource->SetConeAngles(insideConeAngle, outsideConeAngle, apply);
}

//�R�[���̌����̐ݒ�
void	SoundSource::SetConeOrientation(float x, float y, float z, DWORD apply)
{
	pSource->SetConeOrientation(x, y, z, apply);
}
//�O���R�[���̉��ʂ̐ݒ�
void	SoundSource::SetConeOutsideVolume(LONG coneOutsideVolume, DWORD apply)
{
	pSource->SetConeOutsideVolume(coneOutsideVolume, apply);
}

//�������特��炷
void	SoundSource::Play(bool loop)
{
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pPrimaryBuf->Play(0, 0, flags);
}


//�v���C�}���o�b�t�@�̎擾
void	SoundSource::GetPrimaryBuf(LPDIRECTSOUNDBUFFER8& pBuf)
{
	this->pPrimaryBuf = pBuf;
}


