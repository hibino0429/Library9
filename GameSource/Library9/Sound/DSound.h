#pragma once
#pragma comment(lib,"dsound.lib")


#include <dsound.h>
#include <dmusicc.h>
#include <objbase.h>
#include "WaveFile.h"

//�T�E���h�N���X
class Sound
{
public:
	Sound();
	~Sound();
public:

	//1:�T�E���h�E�f�o�C�X�̗�
	bool	DSoundEnumCallBack();
	BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext);

	//2:DirectSound�I�u�W�F�N�g�̍쐬
	bool	DSoundCreate();

	//3:�������x���̐ݒ�
	bool	SetCooperativeLevel(HWND hWnd);

	//4:�f�o�C�X�̐��\�̒���
	bool	GetCaps();

	//5:�X�s�[�J�[�̒���
	bool	GetSpeakerConfig();

	//6:�v���C�}���E�o�b�t�@�̍쐬
	bool	CreateSoundBuffer();

	//7:�Z�J���_���E�o�b�t�@�̍쐬
	bool	CreateSecondaryBuffer();

	//8:�Z�J���_���E�o�b�t�@�ւ̏�������
	bool	WriteSecondaryBuffer();

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

	//13:�I�u�W�F�N�g�̍폜
	void	BufRelease();
	void	InterfaceRelease();

private:

	LPGUID			pDSoundGuid;	//�擾����GUID(�f�t�H���g��NULL)
	LPDIRECTSOUND8	pDirectSound;	//�T�E���h�������C���^�[�t�F�C�X

	DSCAPS			dsCaps;				//�f�o�C�X�̐��\���
	DWORD			dwSpeakerConfig;	//�X�s�[�J�[�̏��

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//�v���C�}���o�b�t�@�̃C���^�[�t�F�C�X
	DSBUFFERDESC			dsBufDesc;			//�T�E���h�o�b�t�@

	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

public:
	LPTSTR					waveFileName;
};



//---------------------------------------------------------
//�T�E���h�f�o�C�X�̃V���O���g���N���X
//---------------------------------------------------------
class SoundDevice
{
public:
	static SoundDevice* Instance();

protected:
	SoundDevice();

private:
	static SoundDevice* instance;

public:
	//�����o�ϐ�
	LPGUID				pDSoundGuid;		//�T�E���hGUID
	LPDIRECTSOUND8		pDirectSound;		//�T�E���h�f�o�C�X

	DSCAPS				dsCaps;				//�f�o�C�X�̐��\���
	DWORD				dwSpeakerConfig;	//�X�s�[�J�[�̏��

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//�v���C�}���o�b�t�@�̃C���^�[�t�F�C�X
	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

	DSBUFFERDESC			dsBufDesc;			//�T�E���h�o�b�t�@

public:
	//�����o�֐�
	
	//1:�T�E���h�E�f�o�C�X�̗�
	bool	DSoundEnumCallBack();
	BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext);

	//2:DirectSound�I�u�W�F�N�g�̍쐬
	bool	DSoundCreate();

	//3:�������x���̐ݒ�
	bool	SetCooperativeLevel(HWND hWnd);

	//4:�f�o�C�X�̐��\�̒���
	bool	GetCaps();

	//5:�X�s�[�J�[�̒���
	bool	GetSpeakerConfig();

	//6:�v���C�}���E�o�b�t�@�̍쐬
	//bool	CreateSoundBuffer();
};