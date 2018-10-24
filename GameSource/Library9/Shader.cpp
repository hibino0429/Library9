#include "Shader.h"

//コンストラクタ
Shader::Shader() : m_pEffect(NULL), m_pErr(NULL)
{

}

//デストラクタ
Shader::~Shader()
{
	if (m_pEffect != NULL) { m_pEffect->Release(); m_pEffect = NULL; }
	if (m_pErr != NULL) { m_pErr->Release(); m_pErr = NULL; }
}

//ロード処理
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

//テクニック名の設定
void	Shader::SetTechnique(const char* technique)
{
	m_pEffect->SetTechnique(technique);
}
//テクニック名をハンドルにセット
void	Shader::SetTechniqueParam(const char* tecName)
{
	tecHandle = m_pEffect->GetTechniqueByName(tecName);
}

//シェーダデバイスのロスト
void	Shader::DeviceLost()
{
	if (m_pEffect != NULL) { m_pEffect->OnLostDevice(); }
}
//シェーダデバイスの復元
void	Shader::DeviceReset()
{
	if (m_pEffect != NULL) { m_pEffect->OnResetDevice(); }
}

//シェーダファイルの設定
void	Shader::Set()
{
	//ローカル - 射影変換行列
	D3DXMATRIX	playerMat;		//プレイヤーのワールドマトリックス
	D3DXMATRIX	worldMat;		//ワールドマトリックス
	D3DXMatrixInverse(&playerMat, NULL, &worldMat);
	D3DXMatrixTranspose(&playerMat, &worldMat);

	//ローカル - 射影変換行列
	D3DXMATRIX	cameraView, cameraProj;
	playerMat = worldMat * cameraView * cameraProj;

	//ライトの方向
	D3DXVECTOR4	lightPos(0, 0, 0, 1);
	m_pEffect->SetVector(NULL, &lightPos);

}

//シェーダの描画
void	Shader::Render()
{

	if (m_pEffect == NULL) { return; }

	//シェーダの設定
	m_pEffect->SetTechnique(tecHandle);
	m_pEffect->Begin(NULL, 0);
	m_pEffect->BeginPass(0);
	LibDGD::SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	Set();

	//描画
	m_pEffect->End();
}

//位置・マトリックスの設定
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


//シェーダのパラメータ設定
//シェーダのテクニックの設定
D3DXHANDLE	Shader::GetParamTechnique(const char* technique)
{
	return m_pEffect->GetTechniqueByName(technique);
}
//シェーダの変数の設定
D3DXHANDLE	Shader::GetParameterName(const char* shaderName)
{
	return m_pEffect->GetParameterByName(NULL, shaderName);
}

//テクスチャの設定
bool	Shader::SetParamTexture(const char* texName, LPDIRECT3DTEXTURE9 tex)
{
	if (FAILED(m_pEffect->SetTexture(texName, tex)))
	{
		MessageBox(NULL, TEXT("テクスチャをシェーダにセットできません"), TEXT("SetParamTexture"), MB_OK);
		return false;
	}
	return true;
}


//描画関係
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
//頂点シェーダを取得する
