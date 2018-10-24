#pragma once
#include "DSound.h"
#include "SoundManager.h"


//------------------------------------------------------
//�T�E���h�E�\�[�X	(����)
//------------------------------------------------------
class	SoundSource
{
public:
	SoundSource();
	~SoundSource();

	bool	CreateSound(LPTSTR fileName);
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

	void	GetPrimaryBuf(LPDIRECTSOUNDBUFFER8& pBuf);		//�v���C�}���o�b�t�@�̎擾


	
public:
	LPDIRECTSOUND3DBUFFER8		pSource;			//����(�\�[�X)
	LPDIRECTSOUNDBUFFER8		pPrimaryBuf;		//�v���C�}���o�b�t�@
	LPDIRECTSOUNDBUFFER			pDSBuf;				//8�ɑΉ����邽�߂̃o�b�t�@
	DSBUFFERDESC				dsBufDesc;			//�T�E���h�o�b�t�@

};