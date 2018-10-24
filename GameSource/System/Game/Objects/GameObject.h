#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Model/Model.h"
#include <string>

//--------------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g
//--------------------------------------------------------------------------------
class GameObject
{

	//���J���\�b�h
public:
	GameObject();
	~GameObject();

	//�擾����
	Model&	GetModel();
	Mat4X4::Matrix& GetMatrix();
	Box3D&	GetBox3D();

	//�ݒ菈��
	void	SetModel(const Model& model);
	void	SetMatrix(const Mat4X4::Matrix& mat);
	void	SetHitBase(const Box3D& hitBox);

	//���f���Ɋւ���
	//���f���̐���
	void	CreateModel(const std::string& filePath,
						const D3DXVECTOR3& pos,
						const D3DXVECTOR3& angle,
						const D3DXVECTOR3& size);

	//���f���̕`��
	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);

	//�}�g���b�N�X�Ɋւ���
	//�}�g���b�N�X�����̎��s
	void	MatrixProcess();

	//�����蔻��{�b�N�X�Ɋւ���

	//����J���\�b�h
private:
	
	//���f���̑傫���Ɠ����蔻��̑傫�������킹��
	void	AdjustBox();

private:
	Model			model;		//���f��
	Mat4X4::Matrix	matrix;		//�}�g���b�N�X
	Box3D			hitBase;	//�����蔻��
};