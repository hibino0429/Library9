#pragma once

#include "Function.h"


//�A�j���[�V�����N���X
class Animation
{
public:

	Animation();
	~Animation();

	//�L�[�t���[���̐���
	void	CreateKey(int numkey);

	//���������z��ɒl��ݒ�
	void	SetKeyValue(int index,float key,float value);

	//�A�j���[�V�����S�̂̌p�����Ԃ̐ݒ�
	void	SetDuration(DWORD duration);

	//�A�j���[�V���������[�v���邩�ǂ����̐ݒ�
	void	SetLoopFlag(DWORD isLoop);

	//�A�j���[�V�����̊J�n�����̐ݒ�
	void	SetStartTime(DWORD start);


	//�����ɑΉ�����l���擾
	bool	GetValue(DWORD time, float* value, bool* isEnd);

	//�����������ɕϊ�
	float	GetFraction(DWORD time);

	//�����ɑΉ�����C���f�b�N�X���擾
	int		GetBeginIndex(float fraction);



private:
	int		m_numKey;		//�L�[�̐�
	float*	m_keys;			//�L�[���i�[����z��̃|�C���^
	float*	m_values;		//�L�[�ɑ΂���l���i�[����z��̃|�C���^
	DWORD	m_duration;		//�p������
	DWORD	m_isLoop;		//���[�v�����邩�̃t���O
	DWORD	m_startTime;	//�X�^�[�g����
};