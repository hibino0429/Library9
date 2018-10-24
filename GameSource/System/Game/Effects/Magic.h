#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Animation.h"

#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>


//���@�G�t�F�N�g�N���X
class MagicEffect
{
public:

	MagicEffect();
	~MagicEffect();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();



private:

	Animation*	m_animAngle;
	Animation*	m_animRadius;
	Animation*	m_animHeight;
	int			m_numAnimArrayElem;	//�I�u�W�F�N�g�̐�


	//���_�o�b�t�@
	struct Vertex1
	{
		D3DXVECTOR3		pos;	//�ʒu
		float			p_size;	//�T�C�Y
		DWORD			color;	//�F
	};
	
#define VERTEX_FVF (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)

	LPDIRECT3DVERTEXBUFFER9		m_VBEffect;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9			m_TexEffect;	//�e�N�X�`��


	Mat4X4::Matrix		world;
};