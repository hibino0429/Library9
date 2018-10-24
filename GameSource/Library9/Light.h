#pragma once

#include "DGD.h"
#include "Function.h"

//���C�g
class Light
{
public:

	Light();
	~Light();

	//���C�g�̐ݒ�
	void	SetNumber(int);				//�ԍ��̎w��
	void	SetUse(bool);				//�g�p���邩�w��

	void	SetType(D3DLIGHTTYPE);		//�^�C�v
	void	SetDiffuse(D3DXCOLOR);		//�f�B�t���[�Y�F
	void	SetSpecular(D3DXCOLOR);		//�X�y�L�����F
	void	SetAmbient(D3DXCOLOR);		//�A���r�G���g�F
	void	SetPosition(D3DXVECTOR3);	//�����̈ʒu
	void	SetDirection(D3DXVECTOR3);	//���̕���
	void	SetRange(float);			//�����̗L������
	void	SetFalloff(float);			//�O���R�[���̌���
	void	SetAttenuation(float);		//���̌���
	void	SetTheta(float);			//�X�|�b�g���C�g�̓����R�[���̊p�x
	void	SetPhi(float);				//�X�|�b�g���C�g�̊O���R�[���̊p�x

	//��{����
	void	Initalize();
	void	Finalize();
	void	UpDate();
	void	Render();
	

	//�n������
	D3DXMATRIX	PassWorldMatrix();	//���[���h�}�g���b�N�X��n��
	void	SetMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

private:

	//���C�g
	D3DLIGHT9		m_light;

	//�}�g���b�N�X
	Mat4X4::Matrix	world;

public:

	//���C�g���ʂ̕ϐ�
	int				number;		//�ԍ�
	bool			useFlag;	//���C�g���g�p���邩
	

	//���C�g�̕ϐ�
	D3DLIGHTTYPE	type;		//�^�C�v
	D3DXCOLOR		diffuse;	//�f�B�t���[�Y�F
	D3DXCOLOR		specular;	//�X�y�L�����F
	D3DXCOLOR		ambient;	//�A���r�G���g�F
	D3DXVECTOR3		position;	//�����̈ʒu
	D3DXVECTOR3		angle;		//�����̊p�x
	D3DXVECTOR3		size;		//�����̑傫��
	D3DXVECTOR3		direction;	//���̕���
	float			range;		//�����̗L������
	float			falloff;	//�O���R�[���̌���
	float			attenuation;//���̌���
	float			theta;		//�X�|�b�g���C�g�̓����R�[���̊p�x
	float			phi;		//�X�|�b�g���C�g�̊O���R�[���̊p�x

};

/////////////////
//���C�g�̎��
//�_�����E�X�|�b�g���C�g�E�f�B���N�V���i�����C�g�E����


//�_�����̏��
//�^�C�v�E�ʒu�E���̗L�������E���̌����E�f�B�t���[�Y�F , (�X�y�L�����[�F)


//�X�|�b�g���C�g�̏��
//


//�f�B���N�V���i�����C�g
//�^�C�v�E���̕����E�f�B�t���[�Y�F , (�X�y�L�����[�F)


//�����̏��
//�^�C�v�E�f�B�t���[�Y�F , (�X�y�L�����[�F)

