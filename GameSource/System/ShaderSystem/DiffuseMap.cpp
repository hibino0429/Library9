#include "DiffuseMap.h"



//------------------------------------------------------------
//生成処理
//------------------------------------------------------------
void	DiffuseMap::Create()
{
	//シェーダのファイルの読み込み
	if (!shader.Load("./data/Shader/ModelMaterial.fx"))
	{
		MessageBoxA(NULL, "シェーダファイルの読み込みに失敗", "DiffuseMap.fx", MB_OK);
		return;
	}

	//テクスチャの読み込み
	LibTexture::Create("./data/Model/Earth_Diffuse.dds", &diffuseTex);

	//シェーダハンドルのセット
	worldHandle			= shader.GetParameterName("matWorld");
	viewHandle			= shader.GetParameterName("matView");
	projHandle			= shader.GetParameterName("matProj");
	lightDirHandle		= shader.GetParameterName("lightDir");
	lightColorHandle	= shader.GetParameterName("lightColor");
	texHandle			= shader.GetParameterName("diffuseMap");
	technique			= shader.GetParamTechnique("DiffuseShader");
}

//------------------------------------------------------------
//取得処理
//------------------------------------------------------------
void	DiffuseMap::GetWorldMatrix(D3DXMATRIX* mat)
{
	matWorld = *mat;
}
void	DiffuseMap::GetViewMatrix(D3DXMATRIX* mat)
{
	matView = *mat;
}
void	DiffuseMap::GetProjMatrix(D3DXMATRIX* mat)
{
	matProj = *mat;
}
void	DiffuseMap::GetLightDir(D3DXVECTOR3& dir)
{
	lightDir = dir;
}
void	DiffuseMap::GetLightColor(D3DXVECTOR3& color)
{
	lightColor = color;
}


//---------------------------------------------------------------
//シェーダの設定処理
//---------------------------------------------------------------
void	DiffuseMap::SetShaderParam()
{
	shader.SetMatrix(worldHandle, &matWorld);
	shader.SetMatrix(viewHandle, &matView);
	shader.SetMatrix(projHandle, &matProj);
	shader.SetVector(lightDirHandle, &D3DXVECTOR4(lightDir,0));
	shader.SetVector(lightColorHandle, &D3DXVECTOR4(lightColor, 1));
	shader.SetParamTexture(texHandle, diffuseTex);
}


void	DiffuseMap::BeginPass()
{
	shader.SetTechnique(technique);		//テクニックのセット
	shader.BeginPass(0);
}
void	DiffuseMap::EndPass()
{
	shader.EndPass();
}

void	DiffuseMap::Begin()
{
	UINT pass;
	shader.Begin(&pass, 0);
}
void	DiffuseMap::End()
{
	shader.End();
}