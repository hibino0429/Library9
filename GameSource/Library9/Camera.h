#pragma once

#include "Function.h"
#include "../Library9/Input/Input.h"

//�J����
class Camera
{
public:

	Camera();
	~Camera();

	//��{����
	void	Initialize();
	void	UpDate();
	void	Render();

	void	SetPos(const D3DXVECTOR3& pos_);		//���_�̃Z�b�g
	void	SetTargetPos(const D3DXVECTOR3& targetPos_);	//�����_�̃Z�b�g
	void	SetUpVec(const D3DXVECTOR3& upVec_);			//��x�N�g���̃Z�b�g

	D3DXVECTOR3	GetPos();		//�ʒu��Ԃ�
	D3DXVECTOR3	GetTarget();	//�����_��Ԃ�
	D3DXVECTOR3	GetUpVec();		//��x�N�g����Ԃ�

	D3DXMATRIX	PassViewMatrix();	//�r���[�}�g���b�N�X
	D3DXMATRIX	PassProjMatrix();	//�v���W�F�N�g�V�����}�g���b�N�X

private:
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		targetPos;	//�����_
	D3DXVECTOR3		upVec;		//��x�N�g��

private:
	float			fovy;		//�J�����̉�p
	//float			aspect;		//�J�����̃A�X�y�N�g��
	float			zMin;		//�J����near�v���[��
	float			zMax;		//�J����far�v���[��

	Mat4X4::Matrix	m_view;		//�r���[�}�g���b�N�X
	Mat4X4::Matrix	m_proj;		//�v���W�F�N�V�����}�g���b�N�X

};