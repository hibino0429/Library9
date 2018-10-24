#include "GameObject.h"


//�R���X�g���N�^
GameObject::GameObject()
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{
	model.Erase();
}


//�擾����
//���f���̎擾
Model&	GameObject::GetModel()
{
	return model;
}
//�}�g���b�N�X�̎擾
Mat4X4::Matrix& GameObject::GetMatrix()
{
	return matrix;
}
//�����蔻��Box�̎擾
Box3D&	GameObject::GetBox3D()
{
	return hitBase;
}

//�ݒ菈��
void	GameObject::SetModel(const Model& model)
{
	this->model = model;
}

void	GameObject::SetMatrix(const Mat4X4::Matrix& mat)
{
	this->matrix = mat;
}

void	GameObject::SetHitBase(const Box3D& hitBox)
{
	this->hitBase = hitBox;
}

//���f���̐���
void	GameObject::CreateModel(const std::string& filePath,
								const D3DXVECTOR3& pos,
								const D3DXVECTOR3& angle,
								const D3DXVECTOR3& size)
{
	model.Load(filePath.c_str());
	model.SetPos(pos);
	model.SetAngle(angle);
	model.SetSize(size);

	this->AdjustBox();
}


//���f���̕`��
//ZTex�̕`��
void	GameObject::ZTexRender(ZTexture* zTex)
{
	MatrixProcess();
	zTex->SetWorldMatrix(&matrix.mat);
	model.ZTexRender(zTex);
}
//�[�x�e�N�X�`���̕`��
void	GameObject::DepthRender(DepthTexture* depTex)
{
	MatrixProcess();
	hitBase.Offset(model.GetPos());
	depTex->GetWorldMatrix(&matrix.mat);
	model.DepthRender(depTex);
}

//�}�g���b�N�X�Ɋւ���
//�}�g���b�N�X�����̎��s
void	GameObject::MatrixProcess()
{
	D3DXMATRIX	matT;
	D3DXMATRIX	matR;
	D3DXMATRIX	matS;

	D3DXMatrixTranslation(&matT, model.GetPos().x, model.GetPos().y, model.GetPos().y);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(model.GetAngle().y), D3DXToRadian(model.GetAngle().x), D3DXToRadian(model.GetAngle().z));
	D3DXMatrixScaling(&matS, model.GetSize().x, model.GetSize().y, model.GetSize().z);

	matrix.mat = matS * matR * matT;
	matrix.SetMatrix(D3DTS_WORLD);
}


//private:
//���f���̑傫���Ɠ����蔻��̑傫�������킹��
void	GameObject::AdjustBox()
{
	this->hitBase = Box3D(-model.GetSize().x / 2, -model.GetSize().y / 2, -model.GetSize().z / 2, 
		model.GetSize().x, model.GetSize().y, model.GetSize().z);
}