#include "Animation.h"


//�R���X�g���N�^
Animation::Animation() : m_numKey(0),m_keys(0),m_values(0),m_isLoop(TRUE),
m_startTime(0),m_duration(0)
{

}

//�f�X�g���N�^
Animation::~Animation()
{
	if (m_keys != 0) { delete[] m_keys; }
	if (m_values != 0) { delete[] m_values; }
}


//�L�[�t���[���̐���
void	Animation::CreateKey(int numberKey)
{
	//�L�[�t���[�����������o�ϐ��ɕۑ�
	m_numKey = numberKey;

	//�����̌Â��f�[�^���폜
	if (m_keys != 0)
	{
		delete[] m_keys;
	}
	if (m_values != 0)
	{
		delete[] m_values;
	}

	//�V�����z��̐���
	m_keys	= new float[numberKey];
	m_values	= new float[numberKey];
}



//���������z��ɒl��ݒ�
void	Animation::SetKeyValue(int index, float key, float value)
{
	//�C���f�b�N�X��0��菬�����A�܂��͌��݂̃L�[�̐��ȏ�Ȃ牽�����Ȃ�
	if ((index < 0) || (index >= m_numKey))
	{
		return;
	}

	m_keys[index]		= key;
	m_values[index]	= value;
}


//�A�j���[�V�����S�̂̌p�����Ԃ̐ݒ�
void	Animation::SetDuration(DWORD duration)
{
	//�A�j���[�V�����S�̂̌p�����Ԃ������o�ϐ��ɕۑ�
	m_duration = duration;
}



//�A�j���[�V���������[�v�����邩�̐ݒ�
void	Animation::SetLoopFlag(DWORD isLoop)
{
	m_isLoop = isLoop;
}


//�A�j���[�V�����̊J�n�����̐ݒ�
void	Animation::SetStartTime(DWORD start)
{
	m_startTime = start;
}


//�����ɑΉ�����l���擾
bool	Animation::GetValue(DWORD time, float* value, bool* isEnd)
{
	//�s���̏ꍇ�̏���
	if (value == 0) { return false; }
	if (isEnd == 0) { return false; }
	if (m_numKey <= 0) { return false; }

	//�A�j���[�V�������I�����Ă������̏���
	DWORD	endTime = m_startTime + m_duration;

	if (!m_isLoop)
	{
		if (time < m_startTime)
		{
			//�������J�n���������������Ȃ�ŏ��̒l��Ԃ�
			*value = m_values[0];
			*isEnd = true;
			return true;
		}
		else if (time > endTime)
		{
			//�������I�����������傫���Ȃ�Ō�̒l��Ԃ�
			*value = m_values[m_numKey - 1];
			*isEnd = true;
			return true;
		}
	}

	//�A�j���[�V�����̌v�Z
	int		beginIndex;
	int		endIndex;
	float	fraction;
	float	slope;

	//���ݎ����������ɕϊ�
	fraction = GetFraction(time);
	//���ݎ����ɍł��߂����O�̃L�[�t���[���擾
	beginIndex = GetBeginIndex(fraction);
	//���ݎ����ɍł��߂�����̃L�[�t���[���擾
	endIndex = beginIndex + 1;

	//�l�̌v�Z
	if (beginIndex < 0)		//�A�j���[�V�����̊J�n�O
	{
		*value = m_values[0];	//�ŏ��̃L�[�t���[���̒l��Ԃ�
	}
	else if (beginIndex >= m_numKey - 1)	//�A�j���[�V�����I����
	{
		*value = m_values[m_numKey - 1];	//�Ō�̃L�[�t���[���̒l��Ԃ�
	}
	else
	{
		//�X���̌v�Z
		float	diffValue = m_values[endIndex] - m_values[beginIndex];	//�L�[�t���[���Ԃ̒l�̍�
		float	diffTime = m_keys[endIndex] - m_keys[beginIndex];		//�L�[�t���[���Ԃ̌p������
		slope = diffValue / diffTime;	//�X��

		//���ݒl�����߂�
		float	fPastFromPrev = fraction - m_keys[beginIndex];	//���O�̃L�[�t���[������̌p������
		*value = slope * fPastFromPrev + m_values[beginIndex];	//���ݒl�̌v�Z
	}

	*isEnd = false;
	return true;
}



//�����������ɕϊ�
float	Animation::GetFraction(DWORD time)
{
	DWORD	diffTime;
	float	fraction;

	//�������犄�������߂�
	if (m_duration == 0)
	{
		fraction = 1.0f;
	}
	else
	{
		if (time > m_startTime)
		{
			//���ݎ�������X�^�[�g����������
			diffTime = time - m_startTime;
			//���[�v�Ή�
			diffTime = diffTime % m_duration;
			//�����̌v�Z
			fraction = (float)diffTime / (float)m_duration;
			//�������������g�p
			fraction = fraction - (int)fraction;
		}
		else
		{
			//���ݎ������A�X�^�[�g������菬�����Ƃ�
			//�^�C�}�[��������Ă��܂����Ƃ�����
			diffTime = m_startTime - time;
			diffTime = diffTime % m_duration;
			fraction = (float)diffTime / (float)m_duration;
			fraction = 1.0f - (fraction - (int)fraction);
		}
	}

	return fraction;
}



//�����ɑΉ�����C���f�b�N�X���擾
int		Animation::GetBeginIndex(float fraction)
{
	if (fraction < m_keys[0]) { return -1; }

	//�����Ɏw�肳�ꂽ�����ƃL�[�t���[���̊������r
	int	index = 0;
	for (int i = 0; i < m_numKey; i++)
	{
		//�L�[�t���[�����傫���Ȃ����甭��
		if (m_keys[i] <= fraction)
		{
			index = i;
		}
		else
		{
			break;
		}
	}
	return index;
}