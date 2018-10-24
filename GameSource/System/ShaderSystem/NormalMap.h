#pragma once
#include "../../Library9/Shader.h"

//-------------------------------------------------------------/
//�@���}�b�v���g�p���A��胊�A���Ȏ�����\������
//-------------------------------------------------------------/


//-------------------------------------------------------------
//�@���}�b�v�N���X
//-------------------------------------------------------------
class NormalMap
{
public:

	void	Create();

	//�ݒ菈��
	void	SetWorldMatrix(D3DXMATRIX* mat);
	void	SetViewMatrix(D3DXMATRIX* mat);
	void	SetProjMatrix(D3DXMATRIX* mat);
	void	SetLightDir(D3DXVECTOR3& vec);
	void	SetCameraVec(D3DXVECTOR3& vec);

	//�V�F�[�_�̐ݒ菈��
	void	SetShaderParam();

	//�`�揈��
	void	Begin();
	void	End();
	void	BeginPass();
	void	EndPass();

private:
	D3DXHANDLE		worldHandle;
	D3DXHANDLE		viewHandle;
	D3DXHANDLE		projHandle;
	D3DXHANDLE		lightHandle;
	D3DXHANDLE		cameraHandle;
	D3DXHANDLE		normalHandle;
	D3DXHANDLE		diffuseHandle;
	D3DXHANDLE		technique;

	D3DXMATRIX		matWorld;
	D3DXMATRIX		matView;
	D3DXMATRIX		matProj;
	D3DXVECTOR3		lightLocalDir;
	D3DXVECTOR3		cameraVec;
	LPDIRECT3DTEXTURE9	normalMap;
	LPDIRECT3DTEXTURE9	diffuseMap;

	Shader			shader;
};