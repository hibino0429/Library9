#pragma once

#include "../../Library9/Light.h"
#include "../../Library9/Camera.h"
#include "../../Library9/Shader.h"


class Light;
class Camera;
//----------------------------------
//�[�x�o�b�t�@�e�N�X�`�����쐬����
//----------------------------------
class DepthTexture
{
public:
	DepthTexture();
	virtual ~DepthTexture();

	void	Create();

	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//�p�X�𗘗p���ĕ`��
	void	Begin(UINT pass, DWORD flags);
	void	End();
	void	BeginPass();
	void	EndPass();

	void	SetEffectParam();


	void	GetLightInfo(Light* lightInfo);
	void	GetWorldMatrix(D3DXMATRIX* mat);
	void	GetLightViewMatrix(D3DXMATRIX* mat);
	void	GetLightProjMatrix(D3DXMATRIX* mat);
	void	SetCameraViewMatrix(D3DXMATRIX* mat);
	void	SetCameraProjMatrix(D3DXMATRIX* mat);

	void	GetCameraMatrix(Camera* camera);
	void	SetTexture(LPDIRECT3DTEXTURE9* tex);
	void	SetMaterialDiffuse(const D3DXVECTOR4& diffuse_);

private:

	D3DXMATRIX		world;
	D3DXMATRIX		cameraView;
	D3DXMATRIX		cameraProj;
	D3DXMATRIX		lightView;
	D3DXMATRIX		lightProj;

	D3DXVECTOR4		lightVec;
	D3DXVECTOR4		pos;
	D3DXVECTOR4		diffuse;

private:


	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 zSurface;
	LPDIRECT3DSURFACE9 stencilSurface;
	Shader			   shader;


	//�G�t�F�N�g�t�@�C���Ŏg�p����f�[�^
	Light*				light;					//���C�g

	D3DXHANDLE			worldHandle;			//���[���h�s��
	D3DXHANDLE			cameraViewHandle;		//�r���[�s��
	D3DXHANDLE			cameraProjHandle;		//�ˉe�s��
	D3DXHANDLE			lightViewHandle;		//���C�g�r���[�s��
	D3DXHANDLE			lightProjHandle;		//���C�g�ˉe�s��
	D3DXHANDLE			shadowMapTex;			//�V���h�E�}�b�v�e�N�X�`���n���h��
	D3DXHANDLE			diffuseHandle;			//�}�e���A�����
	D3DXHANDLE			technique;
	
};

