#include "Shader.h"

//�R���X�g���N�^
Shader::Shader() : m_pEffect(NULL), m_pErr(NULL)
{

}

//�f�X�g���N�^
Shader::~Shader()
{
	if (m_pEffect != NULL) { m_pEffect->Release(); m_pEffect = NULL; }
	if (m_pErr != NULL) { m_pErr->Release(); m_pErr = NULL; }
}

//���[�h����
bool	Shader::Load(LPCWSTR fileName)
{
	if (!LibShader::LoadShaderFile(fileName, &m_pEffect, m_pErr)) { return false; }
	LibDGD::CreateVertexShader(vertexShader, (DWORD*)vertexShader->GetBufferPointer(), &vertexHandler);
	return true;
}
bool	Shader::Load(LPCSTR fileName)
{
	if (!LibShader::LoadShaderFile(fileName, &m_pEffect, m_pErr)) { return false; }
	return true;
}

//�e�N�j�b�N���̐ݒ�
void	Shader::SetTechnique(const char* technique)
{
	m_pEffect->SetTechnique(technique);
}
//�e�N�j�b�N�����n���h���ɃZ�b�g
void	Shader::SetTechniqueParam(const char* tecName)
{
	tecHandle = m_pEffect->GetTechniqueByName(tecName);
}

//�V�F�[�_�f�o�C�X�̃��X�g
void	Shader::DeviceLost()
{
	if (m_pEffect != NULL) { m_pEffect->OnLostDevice(); }
}
//�V�F�[�_�f�o�C�X�̕���
void	Shader::DeviceReset()
{
	if (m_pEffect != NULL) { m_pEffect->OnResetDevice(); }
}

//�V�F�[�_�t�@�C���̐ݒ�
void	Shader::Set()
{
	//���[�J�� - �ˉe�ϊ��s��
	D3DXMATRIX	playerMat;		//�v���C���[�̃��[���h�}�g���b�N�X
	D3DXMATRIX	worldMat;		//���[���h�}�g���b�N�X
	D3DXMatrixInverse(&playerMat, NULL, &worldMat);
	D3DXMatrixTranspose(&playerMat, &worldMat);

	//���[�J�� - �ˉe�ϊ��s��
	D3DXMATRIX	cameraView, cameraProj;
	playerMat = worldMat * cameraView * cameraProj;

	//���C�g�̕���
	D3DXVECTOR4	lightPos(0, 0, 0, 1);
	m_pEffect->SetVector(NULL, &lightPos);

}

//�V�F�[�_�̕`��
void	Shader::Render()
{

	if (m_pEffect == NULL) { return; }

	//�V�F�[�_�̐ݒ�
	m_pEffect->SetTechnique(tecHandle);
	m_pEffect->Begin(NULL, 0);
	m_pEffect->BeginPass(0);
	LibDGD::SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	Set();

	//�`��
	m_pEffect->End();
}

//�ʒu�E�}�g���b�N�X�̐ݒ�
void	Shader::SetMatrix(D3DXMATRIX* mat)
{
	m_pEffect->SetMatrix(NULL, mat);
}
void	Shader::SetVector(D3DXVECTOR4* vec)
{
	m_pEffect->SetVector(NULL, vec);
}
void	Shader::SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat)
{
	m_pEffect->SetMatrix(handle, mat);
}
void	Shader::SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec)
{
	m_pEffect->SetVector(handle, vec);
}


//�V�F�[�_�̃p�����[�^�ݒ�
//�V�F�[�_�̃e�N�j�b�N�̐ݒ�
D3DXHANDLE	Shader::GetParamTechnique(const char* technique)
{
	return m_pEffect->GetTechniqueByName(technique);
}
//�V�F�[�_�̕ϐ��̐ݒ�
D3DXHANDLE	Shader::GetParameterName(const char* shaderName)
{
	return m_pEffect->GetParameterByName(NULL, shaderName);
}

//�e�N�X�`���̐ݒ�
bool	Shader::SetParamTexture(const char* texName, LPDIRECT3DTEXTURE9 tex)
{
	if (FAILED(m_pEffect->SetTexture(texName, tex)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`�����V�F�[�_�ɃZ�b�g�ł��܂���"), TEXT("SetParamTexture"), MB_OK);
		return false;
	}
	return true;
}


//�`��֌W
void	Shader::BeginPass(UINT pass)
{
	m_pEffect->BeginPass(pass);
}
void	Shader::EndPass()
{
	m_pEffect->EndPass();
}
void	Shader::Begin(UINT* pass, DWORD flags)
{
	m_pEffect->Begin(pass, flags);
}
void	Shader::End()
{
	m_pEffect->End();
}








/////////////////////////
//���_�V�F�[�_���擾����
