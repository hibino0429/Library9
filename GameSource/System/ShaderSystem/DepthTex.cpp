#include "DepthTex.h"


//-----------------------------------------------------
//DepthTexture�N���X
//-----------------------------------------------------

//�R���X�g���N�^
DepthTexture::DepthTexture() : texture(nullptr),zSurface(nullptr),stencilSurface(nullptr)
{

}
DepthTexture::~DepthTexture()
{
	if (texture != nullptr) { texture->Release(); texture = nullptr; }
	if (zSurface != nullptr) { zSurface->Release(); zSurface = nullptr; }
	if (stencilSurface != nullptr) { stencilSurface->Release(); stencilSurface = nullptr; }
}


//��������
void	DepthTexture::Create()
{
	//�[�x�o�b�t�@�̕��ƍ����̌v�Z
	UINT width, height;
	LPDIRECT3DSURFACE9 surface;
	D3DSURFACE_DESC surDesc;

	//�[�x�o�b�t�@�̃T�[�t�F�C�X���擾
	LibDGD::GetDepthStencilSurface(&surface);
	surface->GetDesc(&surDesc);		//�T�[�t�F�C�X���̎擾
	width = surDesc.Width;
	height = surDesc.Height;
	if (surface != nullptr) { surface->Release(); surface = nullptr; }

	//z�l�e�N�X�`���𐶐�
	LibDGD::CreateTexture(width, height, &texture);

	//�T�[�t�F�C�X���x���̎擾
	LibDGD::GetSurfaceLevel(0, &texture,&zSurface);

	//Z�l�����_�����O�p
	//�[�x�o�b�t�@�̐���
	LibDGD::CreateDepthStencilSurface(
		width, height, &zSurface
	);

	LibDGD::CreateDepthStencilSurface(width, height, &stencilSurface);

}


//����������
void	DepthTexture::Initialize()
{
	//�V�F�[�_�̓ǂݍ���
	if (!shader.Load("./data/Shader/DepthShadow.fx"))
	{
		MessageBoxA(NULL, "�V�F�[�_�̃t�@�C���ǂݍ��ݎ��s", "DepthShadow.fx", MB_OK);
		return;
	}

	//�V�F�[�_�n���h���̃Z�b�g
	worldHandle = shader.GetParameterName("matWorld");
	cameraViewHandle = shader.GetParameterName("cameraView");
	cameraProjHandle = shader.GetParameterName("cameraProj");
	lightViewHandle = shader.GetParameterName("lightView");
	lightProjHandle = shader.GetParameterName("lightProj");
	shadowMapTex = shader.GetParameterName("shadowTex");
	diffuseHandle = shader.GetParameterName("diffuse");
	technique = shader.GetParamTechnique("DepthShadowShader");

}

//�������
void	DepthTexture::Finalize()
{

}

//�X�V����
void	DepthTexture::UpDate()
{

}

//�`�揈��
void	DepthTexture::Render()
{
	LPDIRECT3DSURFACE9 backSurface;	//�[�x�o�b�t�@
	LPDIRECT3DSURFACE9 zSurface;	//Z�o�b�t�@
	LibDGD::GetRenderTarget(0, &backSurface);
	LibDGD::GetRenderTarget(0, &zSurface);

	//�G�t�F�N�g�Ƀf�[�^��n��
	D3DXMATRIX world;	//�擾���Ă���
	
	D3DXMatrixIdentity(&world);
	world = world * cameraView * cameraProj;	//���[���h�r���[�ˉe�s��
	
	D3DXMATRIX lightWV, lightWP;
	lightWV = light->PassWorldMatrix() * cameraView;
	lightWP = light->PassWorldMatrix() * cameraProj;

	worldHandle = shader.GetParameterName("matWorld");
	shader.SetMatrix(worldHandle, &world);

	cameraViewHandle = shader.GetParameterName("cameraView");
	shader.SetMatrix(cameraViewHandle, &cameraView);

	cameraProjHandle = shader.GetParameterName("cameraProj");
	shader.SetMatrix(cameraProjHandle, &cameraProj);

	lightViewHandle = shader.GetParameterName("lightView");
	shader.SetMatrix(lightViewHandle, &lightWV);

	lightProjHandle = shader.GetParameterName("lightProj");
	shader.SetMatrix(lightProjHandle, &lightWP);

	diffuseHandle = shader.GetParameterName("diffuse");
	shader.SetVector(diffuseHandle, &diffuse);

	//�e�N�j�b�N�̐ݒ�
	shader.SetTechnique("DepthShadowShader");
}


//���߂�̃}�g���b�N�X���擾���A�ݒ肷��
void	DepthTexture::GetCameraMatrix(Camera* camera)
{
	cameraView = camera->PassViewMatrix();
	cameraProj = camera->PassProjMatrix();
}

//----------------------------------------------
//�擾����
//----------------------------------------------


//�`��ΏۃI�u�W�F�N�g�̃��[���h�ϊ��s��̎擾
void	DepthTexture::GetWorldMatrix(D3DXMATRIX* mat)
{
	world = *mat;
}

//���C�g�̏����擾
void	DepthTexture::GetLightInfo(Light* lightInfo)
{
	light = lightInfo;
}
//���C�g�̃r���[�E�ˉe�s��̃Z�b�g
void	DepthTexture::GetLightViewMatrix(D3DXMATRIX* mat)
{
	lightView = *mat;
}
void	DepthTexture::GetLightProjMatrix(D3DXMATRIX* mat)
{
	lightProj = *mat;
}
//�J�����̃r���[�E�ˉe�s��̃Z�b�g
void	DepthTexture::SetCameraViewMatrix(D3DXMATRIX* mat)
{
	cameraView = *mat;
}
void	DepthTexture::SetCameraProjMatrix(D3DXMATRIX* mat)
{
	cameraProj = *mat;
}


//�e�N�X�`���̃Z�b�g
void	DepthTexture::SetTexture(LPDIRECT3DTEXTURE9* tex)
{
	texture = *tex;
}

//�}�e���A���J���[�̐ݒ�
void	DepthTexture::SetMaterialDiffuse(const D3DXVECTOR4& diffuse_)
{
	diffuse = diffuse_;
}

//-----------------------------------------------
//�G�t�F�N�g�`��̊J�n
void	DepthTexture::Begin(UINT pass,DWORD flags)
{
	LibDGD::ViewAndStencilClear();

	//�e�N�j�b�N�̃Z�b�g
	shader.SetTechnique(technique);
	
	UINT Pass ;
	shader.Begin(&Pass, flags);

}

void	DepthTexture::End()
{
	shader.End();

	//LibDGD::SetVertexShader(nullptr);
	//LibDGD::SetPixelShader(nullptr);
}


void	DepthTexture::BeginPass()
{
	shader.BeginPass(0);	//�p�X�͂P�̂�
}

void	DepthTexture::EndPass()
{
	shader.EndPass();
}


//�p�����[�^�̏����G�t�F�N�g�ɃZ�b�g
void	DepthTexture::SetEffectParam()
{
	shader.SetMatrix(worldHandle, &world);
	shader.SetMatrix(cameraViewHandle, &cameraView);
	shader.SetMatrix(cameraProjHandle, &cameraProj);
	shader.SetMatrix(lightViewHandle, &lightView);
	shader.SetMatrix(lightProjHandle, &lightProj);
	shader.SetVector(diffuseHandle, &diffuse);
	shader.SetParamTexture(shadowMapTex, texture);
}