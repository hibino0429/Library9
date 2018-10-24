#include "Light.h"


//--------------------------------------------------------------
//�R���X�g���N�^
//--------------------------------------------------------------
Light::Light()
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	number = 0;
	useFlag = false;

	D3DXMatrixIdentity(&world.mat);

}


//--------------------------------------------------------------
//�f�X�g���N�^
//--------------------------------------------------------------
Light::~Light()
{

}


//--------------------------------------------------------------
//���C�g�̏�����
//--------------------------------------------------------------
void	Light::Initalize()
{
	//���C�g�̋��ʏ���
	LibDGD::SetLight(number, &m_light);					//���C�g�ɃZ�b�g����
	LibDGD::SetUseLight(number, useFlag);				//���C�g�̎g�p�ݒ�
	LibDGD::SetRenderState(D3DRS_LIGHTING, useFlag);	//���C�e�B���O���[�h�̐ݒ�

	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(1, 1, 1);
}

//--------------------------------------------------------------
//���C�g���
//--------------------------------------------------------------
void	Light::Finalize()
{

}

//--------------------------------------------------------------
//���C�g�̍X�V
//--------------------------------------------------------------
void	Light::UpDate()
{
	
}

//--------------------------------------------------------------
//���C�g�̕`��
//--------------------------------------------------------------
void	Light::Render()
{
	SetMatrix(position, angle, size);
}


void	Light::SetMatrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x,pos.y,pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale,size.x,size.y,size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);
}


//�ԍ��̎w��
void	Light::SetNumber(int num)
{
	this->number = num;
}

//�g�p���邩�̎w��
void	Light::SetUse(bool flag)
{
	this->useFlag = flag;
}

//�^�C�v�̐ݒ�
void	Light::SetType(D3DLIGHTTYPE type)
{
	m_light.Type = type;
}

//�f�B�t���[�Y�F�̐ݒ�
void	Light::SetDiffuse(D3DXCOLOR diffuse)
{
	m_light.Diffuse = diffuse;
}

//�X�y�L�����[�F�̐ݒ�
void	Light::SetSpecular(D3DXCOLOR specular)
{
	m_light.Specular = specular;
}

//�A���r�G���g�F�̐ݒ�
void	Light::SetAmbient(D3DXCOLOR ambient)
{
	m_light.Ambient = ambient;
}

//�����̈ʒu�̐ݒ�
void	Light::SetPosition(D3DXVECTOR3 pos)
{
	m_light.Position = pos;
}

//���̕���
void	Light::SetDirection(D3DXVECTOR3 dir)
{
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &dir);
}

//�����̗L���͈�
void	Light::SetRange(float range)
{
	m_light.Range = range;
}

//�X�|�b�g���C�g�̊O���R�[���̌���
void	Light::SetFalloff(float falloff = 1.0f)
{
	m_light.Falloff = falloff;
}

//���̌���
void	Light::SetAttenuation(float attenuation)
{
	m_light.Attenuation0 = attenuation;
	m_light.Attenuation1 = attenuation;
	m_light.Attenuation2 = attenuation;
}

//�X�|�b�g���C�g�̓����R�[���̊p�x
void	Light::SetTheta(float theta)
{
	m_light.Theta = theta;
}

//�X�|�b�g���C�g�̊O���R�[���̊p�x
void	Light::SetPhi(float phi)
{
	m_light.Phi = phi;
}

//���[���h�}�g���b�N�X��n��
D3DXMATRIX	Light::PassWorldMatrix()
{
	return this->world.mat;
}