#pragma once
#include "Function.h"


//------------------------------------------------------
//�V�F�[�_�N���X
//------------------------------------------------------
class Shader
{
public:
	Shader();
	~Shader();

	bool	Load(LPCWSTR fileName);	//�V�F�[�_�t�@�C���̓ǂݍ���
	bool	Load(LPCSTR fileName);	//�V�F�[�_�t�@�C���̓ǂݍ���
	void	DeviceLost();			//�V�F�[�_�f�o�C�X��������
	void	DeviceReset();			//�V�F�[�_�f�o�C�X�̕���
	void	Set();					//�V�F�[�_�̐ݒ�
	void	Render();				//�V�F�[�_�̕`��


	//�e�N�j�b�N�̐ݒ�
	void	SetTechnique(const char* techniqueName);		//�e�N�j�b�N���̐ݒ�
	void	SetTechniqueParam(const char* tecName);			//�e�N�j�b�N�̃p�����[�^�̃Z�b�g

	//���W�E�}�g���b�N�X�̐ݒ�
	void	SetMatrix(D3DXMATRIX* mat);
	void	SetVector(D3DXVECTOR4* vec);
	//���W�E�}�g���b�N�X�̐ݒ�(�n���h���t��)
	void	SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat);
	void	SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec);

	//�V�F�[�_�̃p�����[�^�ݒ�
	D3DXHANDLE	GetParamTechnique(const char* technique);	//�e�N�j�b�N�̐ݒ�
	D3DXHANDLE	GetParameterName(const char* shaderName);	//�V�F�[�_�̕ϐ��̐ݒ�
	bool		SetParamTexture(const char* texName, LPDIRECT3DTEXTURE9 tex);	//�e�N�X�`���̐ݒ�

	//�`��p�X�̊J�n
	void	BeginPass(UINT pass);
	void	EndPass();
	void	Begin(UINT* pass, DWORD flags);
	void	End();


	//���_�V�F�[�_��^����
	LPDIRECT3DVERTEXSHADER9*	GetVertexShader();
	LPDIRECT3DPIXELSHADER9*		GetPixelShader();

	LPD3DXBUFFER				vertexShader;
	LPD3DXBUFFER				pixelShader;
	LPDIRECT3DVERTEXSHADER9		vertexHandler;		//�o�[�e�b�N�X�n���h���[
	LPDIRECT3DPIXELSHADER9		pixelHandler;		//�s�N�Z���n���h���[


private:
	LPD3DXEFFECT	m_pEffect;		//�V�F�[�_�̃f�o�C�X
	LPD3DXBUFFER	m_pErr;			//�o�b�t�@

	D3DXHANDLE		tecHandle;		//�e�N�j�b�N�n���h��
};