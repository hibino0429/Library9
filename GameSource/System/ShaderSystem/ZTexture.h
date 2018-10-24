#pragma once
#include "../../Library9/Shader.h"
#include "../../Library9/Function.h"


//----------------------------------
//Z�l�e�N�X�`���N���X
//----------------------------------
class ZTexture
{
public:
	ZTexture();
	virtual ~ZTexture();


public:
	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	GetShader(Shader* shader);	//�V�F�[�_�̎擾

	void	SetViewMatrix(D3DXMATRIX* mat);	//�r���[�s��̐ݒ�
	void	SetProjMatrix(D3DXMATRIX* mat);	//�ˉe�s��̐ݒ�
	void	SetWorldMatrix(D3DXMATRIX* mat);//���[���h�s��̐ݒ�

	LPDIRECT3DTEXTURE9*	GetTexture();		//�e�N�X�`�����̎擾
	LPDIRECT3DSURFACE9*	GetZSurface();		//Z�l�e�N�X�`���T�[�t�F�C�X�̎擾


	void	Begin();	//�`��̊J�n
	void	End();		//�`��̏I��
	void	BeginPass();	//�p�X�̊J�n�̐錾
	void	EndPass();		//�p�X�̏I���̐錾

	void	SetEffectParam();	//�p�����[�^�̏����G�t�F�N�g�ɃZ�b�g
	

private:
	LPDIRECT3DTEXTURE9	zTexture;			//Z�l�e�N�X�`��
	LPDIRECT3DSURFACE9	zSurface;			//Z�l�e�N�X�`���T�[�t�F�C�X
	LPDIRECT3DSURFACE9	depthSurface;		//�[�x�o�b�t�@�T�[�t�F�C�X
	LPDIRECT3DSURFACE9	deviceZSurface;		//�f�o�C�X�̃T�[�t�F�C�X
	LPDIRECT3DSURFACE9	deviceDepthSurface;	//�f�o�C�X�̐[�x�T�[�t�F�C�X

	Shader				zTexShader;		//Z�l���Z�o����V�F�[�_

private:
	D3DXMATRIX			matWorld;	//���[���h�ϊ��s��
	D3DXMATRIX			matView;	//�r���[�ϊ��s��
	D3DXMATRIX			matProj;	//�ˉe�ϊ��s��
	D3DXHANDLE			worldHandle;	//���[���h�s��̃n���h��
	D3DXHANDLE			viewHandle;		//�r���[�s��̃n���h��
	D3DXHANDLE			projHandle;		//�ˉe�s��̃n���h��
	D3DXHANDLE			techniqueHandle;//�e�N�j�b�N�̃n���h��
};