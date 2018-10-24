#pragma once
#include "../../Library9/Shader.h"

//------------------------------------------------------------------------/
//�I�u�W�F�N�g�̐F�����߂�
//���C�g�̕����A���̋����A��������I�u�W�F�N�g�̐F������
//------------------------------------------------------------------------/

//--------------------------------------------------
//�f�B�t���[�Y�}�b�v�N���X
//--------------------------------------------------
class DiffuseMap
{
public:

	void	Create();		//��������

	//�V�F�[�_�̐ݒ菈��------------------------
	void	SetShaderParam();
	void	BeginPass();
	void	EndPass();
	void	Begin();
	void	End();

	//�擾����-------------------
	void	GetWorldMatrix(D3DXMATRIX* mat);
	void	GetViewMatrix(D3DXMATRIX* mat);
	void	GetProjMatrix(D3DXMATRIX* mat);
	void	GetLightDir(D3DXVECTOR3& dir);
	void	GetLightColor(D3DXVECTOR3& color);


private:
	D3DXHANDLE		worldHandle;		//���[���h�s��n���h��
	D3DXHANDLE		viewHandle;			//�r���[�s��n���h��
	D3DXHANDLE		projHandle;			//�ˉe�s��n���h��
	D3DXHANDLE		lightDirHandle;		//���C�g�����̃n���h��
	D3DXHANDLE		lightColorHandle;	//���C�g�̐F�̃n���h��
	D3DXHANDLE		texHandle;			//�e�N�X�`���n���h��
	D3DXHANDLE		technique;			//�e�N�j�b�N

	D3DXMATRIX			matWorld;		//���[���h�s��
	D3DXMATRIX			matView;		//�r���[�s��
	D3DXMATRIX			matProj;		//�ˉe�s��
	LPDIRECT3DTEXTURE9	diffuseTex;		//�e�N�X�`��
	D3DXVECTOR3			lightDir;		//���C�g�̕���
	D3DXVECTOR3			lightColor;		//���C�g�̐F

	Shader			shader;				//�V�F�[�_
};