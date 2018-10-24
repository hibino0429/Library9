#pragma once
#include "DSound.h"



//-----------------------------------------------------------
//�T�E���h�E���X�i�[
//-----------------------------------------------------------
class SoundListener
{
public:
	SoundListener();
	~SoundListener();

	bool	CreateListener();							//���X�i�[�̍쐬

	void	SetListener(float dist);					//���X�i�[�̐ݒ�
	void	SetDoppler(float doppler);					//�h�b�v���[�̐ݒ�
	void	SetPosition(float, float, float, DWORD);	//�ʒu�̐ݒ�
	void	SetVelocity(float, float, float, DWORD);	//���x�̐ݒ�
	void	SetOrientation(float, float, float, float, float, float, DWORD);	//�����̐ݒ�
	void	SetRolloff(float rolloff, DWORD);			//���[���E�I�t�̐ݒ�
	void	SetCommitDefferred();						//DS_3D_DEFFRRED�̐ݒ�𔽉f������

	void	GetPrimaryBuf(LPDIRECTSOUNDBUFFER* pBuf);	//�v���C�}���o�b�t�@�̊m��

public:
	LPDIRECTSOUND3DLISTENER8	pListener;			//���X�i�[
	LPDIRECTSOUNDBUFFER			pPrimaryBuf;		//�v���C�}���o�b�t�@

};