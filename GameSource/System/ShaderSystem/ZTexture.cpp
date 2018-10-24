#include "ZTexture.h"



//�R���X�g���N�^
ZTexture::ZTexture() : zTexture(nullptr), zSurface(nullptr), depthSurface(nullptr),
deviceZSurface(nullptr), deviceDepthSurface(nullptr)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	worldHandle = nullptr;
	viewHandle = nullptr;
	projHandle = nullptr;
	techniqueHandle = nullptr;
}

//�f�X�g���N�^
ZTexture::~ZTexture()
{
	SAFE_RELEASE(zTexture);
	SAFE_RELEASE(zSurface);
	SAFE_RELEASE(depthSurface);
	SAFE_RELEASE(deviceZSurface);
	SAFE_RELEASE(deviceDepthSurface);
}



//����������
void	ZTexture::Initialize()
{
	//�G�t�F�N�g�t�@�C����ǂݍ���
	if (!zTexShader.Load("./data/Shader/zTexCreator.fx"))
	{
		MessageBoxA(NULL, "�ǂݍ��ݎ��s", "zTexShader.Load", MB_OK);
		return;
	}
	
	//�G�t�F�N�g�n���h���̎擾
	worldHandle = zTexShader.GetParameterName("matWorld");
	viewHandle = zTexShader.GetParameterName("matView");
	projHandle = zTexShader.GetParameterName("matProj");
	techniqueHandle = zTexShader.GetParameterName("ZValueShader");

	//Z�l�e�N�X�`���̐���
	UINT width = 1024, height = 1024;
	LibDGD::CreateTexture(width, height, &zTexture);
	//Z�l�e�N�X�`���̃T�[�t�F�C�X�̎擾
	//LibDGD::GetSurfaceLevel(0,&zTexture, &zSurface);
	zTexture->GetSurfaceLevel(0, &zSurface);

	//�`��f�o�C�X�ɒ�`����Ă���o�b�t�@�̔\�͂��擾
	LPDIRECT3DSURFACE9	pSurface;
	LibDGD::GetDepthStencilSurface(&pSurface);
	D3DSURFACE_DESC surfDesc;
	pSurface->GetDesc(&surfDesc);
	pSurface->Release();

	//�Ǝ��[�x�o�b�t�@���쐬
	//LibDGD::CreateDepthStencilSurface(width, height, &depthSurface);
	LibDGD::CreateDepthStencilSurface(width, height,
		surfDesc.Format, surfDesc.MultiSampleType, surfDesc.MultiSampleQuality,
		&depthSurface);

}

//�������
void	ZTexture::Finalize()
{

}

//�X�V����
void	ZTexture::UpDate()
{

}

//�`�揈��
void	ZTexture::Render()
{

}


//�r���[�s��̐ݒ�
void	ZTexture::SetViewMatrix(D3DXMATRIX* mat)
{
	matView = *mat;
}

//�ˉe�s��̐ݒ�
void	ZTexture::SetProjMatrix(D3DXMATRIX* mat)
{
	matProj = *mat;
}

//���[���h�s��̐ݒ�
void	ZTexture::SetWorldMatrix(D3DXMATRIX* mat)
{
	matWorld = *mat;
}

//�e�N�X�`���̏��̎擾
LPDIRECT3DTEXTURE9* ZTexture::GetTexture()
{
	return &zTexture;
}

LPDIRECT3DSURFACE9*	ZTexture::GetZSurface()
{	
	return &zSurface;
}


//�`��̊J�n
void	ZTexture::Begin()
{
	//�f�o�C�X�̃o�b�t�@���ꎞ�ۑ�
	LibDGD::GetRenderTarget(0, &deviceZSurface);
	LibDGD::GetDepthStencilSurface(&deviceDepthSurface);

	//�f�o�C�X��Z�l�e�N�X�`���T�[�t�F�C�X�Ɛ[�x�o�b�t�@�̐ݒ�
	LibDGD::SetRenderTarget(0, &zSurface);
	LibDGD::SetDepthStencilSurface(&depthSurface);

	//�e�T�[�t�F�C�X�̏�����
	LibDGD::ViewAndStencilClear();

	//�V�F�[�_�̃e�N�j�b�N��ݒ�
	techniqueHandle = zTexShader.GetParamTechnique("ZValueShader");
	zTexShader.SetTechnique(techniqueHandle);

	//�V�F�[�_�̊J�n
	UINT tmp ;
	zTexShader.Begin(&tmp, 0);
}

//�`��̏I��
void	ZTexture::End()
{
	zTexShader.End();


	//�f�o�C�X�����Ƃ̃T�[�t�F�C�X�ɖ߂�
	LibDGD::SetRenderTarget(0, &deviceZSurface);
	LibDGD::SetDepthStencilSurface(&deviceDepthSurface);

	deviceZSurface = nullptr;
	deviceDepthSurface = nullptr;

	//�Œ�@�\�ɖ߂�
	//LibDGD::SetVertexShader(nullptr);
	//LibDGD::SetPixelShader(nullptr);
}

//�p�X�̊J�n�̐錾
void	ZTexture::BeginPass()
{
	zTexShader.BeginPass(0);	//Z�l�v�Z�͂P�p�X
}

//�p�X�̏I���̐錾
void	ZTexture::EndPass()
{
	zTexShader.EndPass();
}

//�p�����[�^�̏����G�t�F�N�g�ɃZ�b�g
void	ZTexture::SetEffectParam()
{
	zTexShader.SetMatrix(worldHandle,&matWorld);
	zTexShader.SetMatrix(viewHandle, &matView);
	zTexShader.SetMatrix(projHandle, &matProj);
}


//�V�F�[�_�̎擾
void	ZTexture::GetShader(Shader* shader)
{
	zTexShader = *shader;
}