#pragma once

#include "../../../Library9/Function.h"

#include <mmsystem.h>
#include <math.h>

//�p�[�e�B�N���N���X
class Particle
{
public:

	Particle();
	~Particle();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

private:

	//���_�o�b�t�@�̒�`
	struct MY_VERTEX
	{
		D3DXVECTOR3	pos;		//�ʒu
		FLOAT		p_sizse;	//�T�C�Y
		DWORD		color;		//�F
	};
#define MY_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)


	//�|�C���g�X�v���C�g�̒�`
	struct PointSprite
	{
		D3DXVECTOR3		pos;	//�����ʒu
		float			psize;	//�T�C�Y
		D3DXVECTOR3		vec;	//�����̊p�x
		DWORD			startTime;	//�J�n����
		float			duration;	//�p������
	};

#define MY_NUM_PSPRITE 128

	PointSprite		m_psprite[MY_NUM_PSPRITE];

	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���摜
	
	LPDIRECT3DVERTEXBUFFER9	m_pVBEffect;	//�G�t�F�N�g�o�b�t�@


	//�}�g���b�N�X
	Mat4X4::Matrix		world;	//���[���h���W�n
};