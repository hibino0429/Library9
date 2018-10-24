#pragma once

//�g�p����@�\------------------------------------------
#include "../../../Library9/Function.h"

#include "../../../Library9/Model/Model.h"
#include "../../ShaderSystem/ZTexture.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/NormalMap.h"
//------------------------------------------------------
//�I�u�W�F�N�g�̋��ʃN���X
//------------------------------------------------------
class Object
{
public:

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


public:


	//�}�g���b�N�X����
	//����1:�ʒu
	//����2:����
	//����3:�T�C�Y
	void	Matrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

	//�����蔻�菈��
	//����1:Box3D�̃{�b�N�X
	bool	CheckHit(Box3D& box);

public:

	Box3D	hitBox;				//�{�b�N�X
	Mat4X4::Matrix	matWorld;	//���[���h�}�g���b�N�X
public:
	Model	myObject;

	//�m�[�}���}�b�v
	NormalMap	normalMap;

	//�V�F�[�_�̏���
public:
	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);


public:
	//�擾����
	void	GetMatrix(D3DXMATRIX* mat, D3DXMATRIX* getmat);		//�}�g���b�N�X
	void	GetVector4(D3DXVECTOR4* vec, D3DXVECTOR4* getvec);	//�ʒu�E�x�N�g��
};