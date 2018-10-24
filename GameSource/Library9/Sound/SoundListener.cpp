#include "SoundListener.h"


//�R���X�g���N�^
SoundListener::SoundListener() : pListener(NULL), pPrimaryBuf(NULL)
{

}

//�f�X�g���N�^
SoundListener::~SoundListener()
{
	if (pListener != NULL) { pListener->Release(); pListener = NULL; }
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
}


//���X�i�[�̍쐬
bool	SoundListener::CreateListener()
{
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DListener8,
		(LPVOID*)&pListener)))
	{
		MessageBox(NULL, TEXT("���X�i�[�̍쐬�Ɏ��s���܂���"), TEXT("CreateListener"), MB_OK);
		return false;
	}
	return true;
}


//�����̐ݒ�
void	SoundListener::SetListener(float dist)
{
	pListener->SetDistanceFactor(dist, DS3D_IMMEDIATE);
}

//�h�b�v���[���ʂ̐ݒ�
void	SoundListener::SetDoppler(float doppler)
{
	//DS3D_MINDOPPLERFACTOR(0.0)		//�ŏ�
	//DS3D_MAXDOPPLERFACTOR(10.0)		//�ő�
	//1���W��
	pListener->SetDopplerFactor(doppler, DS3D_IMMEDIATE);
}

//�ʒu�̐ݒ�
void	SoundListener::SetPosition(float x, float y, float z, DWORD apply)
{
	pListener->SetPosition(x, y, z, apply);
}

//���x�̐ݒ�
void	SoundListener::SetVelocity(float vx, float vy, float vz, DWORD apply)
{
	pListener->SetVelocity(vx, vy, vz, apply);
}

//�����̐ݒ�
void	SoundListener::SetOrientation(float xFront, float yFront, float zFront, float xTop, float yTop, float zTop, DWORD apply)
{
	pListener->SetOrientation(xFront, yFront, zFront, xTop, yTop, zTop, apply);
}

//���[���E�I�t�̐ݒ�
void	SoundListener::SetRolloff(float rolloff, DWORD apply)
{
	//���X�i�[�Ɖ����Ƃ̋����ɂ��A�����̓x����
	//DS3D_MINROLLOFFFACTOR(0.0f)	//�ŏ�
	//DS3D_MAXROLLOFFFACTOR(10.0f)	//�ő�
	//1���W��
	pListener->SetRolloffFactor(rolloff, apply);
}

//DS3D_DEFEREED�̐ݒ�𔽉f������
void	SoundListener::SetCommitDefferred()
{
	pListener->CommitDeferredSettings();
}


//�v���C�}���o�b�t�@�̊m��
void	SoundListener::GetPrimaryBuf(LPDIRECTSOUNDBUFFER* pBuf)
{
	this->pPrimaryBuf = *pBuf;
	MessageBox(NULL, TEXT("pPrimary�̐ݒ�"), TEXT("�v���C�}���o�b�t�@�̐����Ɏ��s"), MB_OK);
}