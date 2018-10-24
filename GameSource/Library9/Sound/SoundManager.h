#pragma once
#include "DSound.h"

#include "SoundListener.h"
#include "SoundSource.h"

//----------------------------------------------------
//�T�E���h�Ǘ��N���X
//----------------------------------------------------
class SoundManager
{
public:
	//�����̎菇

	//1:�T�E���h�E�f�o�C�X�̗�

	//2:IDirectSound8�C���^�[�t�F�C�X�̎擾

	//3:�������x���̐ݒ�

	//4:�f�o�C�X�̐��\�̒���

	//5:�X�s�[�J�̒���

	//6:�v���C�}���o�b�t�@�̍쐬

	//7:�Z�J���_���o�b�t�@�̍쐬

	//8:�Z�J���_���o�b�t�@�ւ̏�������

	//9:�Z�J���_���o�b�t�@�̍Đ�


	bool	Create(HWND hWnd);	//�T�E���h�̐���

	void	LoadSound(LPTSTR fileName);

	void	Play(bool loop);
	void	Stop();

	void	SetVolume(LONG volume);
	void	SetPan(LONG pan);
	void	SetFrequency(DWORD frequency);

private:
	Sound	sound;

};



//���O��Ԃɂ̂݊i�[����
namespace SE2
{
	bool	Create(HWND hWnd);	//�T�E���h�̐���

	void	LoadSound(LPTSTR fileName);

	void	Play(bool loop);
	void	Stop();

	void	SetVolume(LONG volume);
	void	SetPan(LONG pan);
	void	SetFrequency(DWORD frequency);

	static Sound	se;
}



//------------------------------------------------------
//�T�E���h�̊Ǘ��N���X
//------------------------------------------------------
//�Z�J���_���o�b�t�@���g�p���āA�T�E���h�̍Đ��Ȃǂ̏���������

class Sounds
{
public:

	Sounds();
	~Sounds();

	//9:�o�b�t�@�̃t�H�[�}�b�g�̐ݒ�
	bool	SecondarySetFormat(LPTSTR fileName);

	//10:�T�E���h�����������L����Z�J���_���o�b�t�@
	bool	DuplicateSoundBuf();

	//11:�Z�J���_���o�b�t�@�̍Đ��E��~
	bool	Play(bool loop);
	bool	Stop();

	//12:�{�����[���E�p���E�Đ����g���̐ݒ�
	bool	SetVolume(LONG);
	bool	SetPan(LONG);
	bool	SetFrequency(DWORD);

	
	//�T�E���h�t�@�C���̓ǂݍ���
	bool	LoadSound(LPTSTR fileName);


	//�v���C�}���o�b�t�@�̍쐬
	bool	CreateSoundBuffer();

public:
	LPTSTR		waveFileName;

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//�v���C�}���o�b�t�@�̃C���^�[�t�F�C�X
	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

	DSBUFFERDESC			dsBufDesc;			//�T�E���h�o�b�t�@
};



//�T�E���h�f�o�C�X�̏���
namespace SE
{
	//�T�E���h�f�o�C�X�̐���
	bool	Create(HWND hWnd);

}



//-----------------------------------------------------------------
//�X�g���[���Đ�
//XXX:���݉��ǒ�
//-----------------------------------------------------------------
class StreamSound
{
public:
	bool	CreateNotify(LPTSTR fileName);	//�ʒm�C�x���g�𔭍s

	bool	CreateThreadNotify();				//�X���b�h�̍쐬

	void	Block_Copy(UINT i);			//�T�E���h�o�b�t�@�փR�s�[


	StreamSound();
	~StreamSound();

	static DWORD WINAPI MyThreadFunc(LPVOID param);

public:
	LPDIRECTSOUNDBUFFER8	pDirectSoundData;	//�T�E���h�o�b�t�@
	LPDIRECTSOUNDNOTIFY8	pDirectSoundNotify;	//�ʒm�C�x���g�f�o�C�X

	HANDLE		hEvent[3];		//�C�x���g�n���h��
	HANDLE		hThreadHandle;	//�X���b�h�E�n���h��
	DWORD		dwThreadID;		//�X���b�hID
	DWORD		dwBlockSize;	//�T�E���h�o�b�t�@�̃T�C�Y
	DWORD		dwPlayAdd;		//���݂̍Đ��ʒu
	
	CWaveFile	waveFile;		//WAVE�t�@�C��
};




//-----------------------------------------------------
//3D�T�E���h
//-----------------------------------------------------
class Sound3D
{
public:

	Sound3D();
	~Sound3D();

	bool	CreatePrimary(LPTSTR fileName);		//�v���C�}���o�b�t�@�̍쐬
	

	bool	CreateSource();			//�����̍쐬
	void	SetMinDistance(float minDist, DWORD apply);		//�ŏ�����
	void	SetMaxDistance(float maxDist, DWORD apply);		//�ő勗��
	void	SetMode(DWORD mode, DWORD apply);				//3D�T�E���h�������[�h�̐ݒ�
	void	SetPositionSource(float, float, float, DWORD);		//�ʒu
	void	SetVelocitySource(float, float, float, DWORD);		//���x
	void	SetConeAngle(DWORD, DWORD, DWORD);					//�T�E���h�E�R�[���̐ݒ�
	void	SetConeOrientation(float x, float y, float z, DWORD);
	void	SetConeOutsideVolume(LONG, DWORD);
	void	Play(bool loop);


	//��-----------------
	//�v���C�}���o�b�t�@
	bool	PrimaryBufCreate();
	bool	SecondaryBufCreate(LPTSTR fileName);

public:

public:
	LPDIRECTSOUND3DBUFFER8		pSource;			//����(�\�[�X)
	LPDIRECTSOUND3DLISTENER8	pListener;			//���X�i�[

	LPDIRECTSOUNDBUFFER8		pDSBuf8;
	LPDIRECTSOUNDBUFFER			pPrimaryBuf;		//�T�E���h�o�b�t�@(�v���C�}��)

	DSBUFFERDESC				dsBufDesc;


};


//3D�T�E���h
namespace Audio
{
	bool	CreateSoundDevice(HWND hWnd);

	bool	CreateAudio(LPTSTR fileName,LPDIRECTSOUNDBUFFER* pBuf);

	bool	CreateSoundBuf(DSBUFFERDESC* desBufDesc,LPDIRECTSOUNDBUFFER* pBuf);

	bool	QueryInterface();

	LPDIRECTSOUND8*	GetDirectSound();
}