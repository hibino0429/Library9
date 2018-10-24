#include "Camera.h"


//----------------------------------------------------------
//�R���X�g���N�^
//----------------------------------------------------------
Camera::Camera()
{
	D3DXMatrixIdentity(&m_view.mat);
	D3DXMatrixIdentity(&m_proj.mat);
}

//----------------------------------------------------------
//�f�X�g���N�^
//----------------------------------------------------------
Camera::~Camera()
{
	
}


//----------------------------------------------------------
//�J�����̏�����
//----------------------------------------------------------
void	Camera::Initialize()
{
	this->pos = D3DXVECTOR3(300, 10, 10);
	this->targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->upVec		= D3DXVECTOR3(0, 1, 0);

	this->fovy = 45.0f;
	this->zMin = 1.0f;
	this->zMax = 4000.0f;

	D3DXMatrixLookAtLH(&m_view.mat, &pos, &targetPos, &upVec);

	m_view.SetMatrix(D3DTS_VIEW);
}


//---------------------------------------------------------
//�J�����̍X�V
//---------------------------------------------------------
void	Camera::UpDate()
{
	D3DVIEWPORT9	vp;
	if (!LibDGD::SetViewPort(&vp)) { return; }

	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveLH(&m_proj.mat,
		D3DXToRadian(fovy),
		aspect,
		zMin,
		zMax);

	m_proj.SetMatrix(D3DTS_PROJECTION);

	D3DXMatrixLookAtLH(&m_view.mat, &pos, &targetPos, &upVec);

	m_view.SetMatrix(D3DTS_VIEW);

}


//-----------------------------------------------------
//�J�����̕`��
//-----------------------------------------------------
void	Camera::Render()
{
	this->UpDate();

}


//�J�����̈ʒu��ύX����
void	Camera::SetPos(const D3DXVECTOR3& pos_)
{
	this->pos = pos_;
}

//�J�����̒����_��ύX����
void	Camera::SetTargetPos(const D3DXVECTOR3& targetPos_)
{
	this->targetPos = targetPos_;
}

//�J�����̏�x�N�g����ύX����
void	Camera::SetUpVec(const D3DXVECTOR3& upVec_)
{
	this->upVec = upVec_;
}


//�J�����̈ʒu��Ԃ�
D3DXVECTOR3	Camera::GetPos()
{
	return this->pos;
}

//�J�����̒����_��Ԃ�
D3DXVECTOR3	Camera::GetTarget()
{
	return this->targetPos;
}

//�J�����̏�x�N�g����Ԃ�
D3DXVECTOR3	Camera::GetUpVec()
{
	return this->upVec;
}

//�r���[�}�g���b�N�X
D3DXMATRIX	Camera::PassViewMatrix()
{
	return this->m_view.mat;
}

//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX	Camera::PassProjMatrix()
{
	return this->m_proj.mat;
}