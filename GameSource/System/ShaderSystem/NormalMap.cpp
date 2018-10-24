#include "NormalMap.h"


//---------------------------------
//生成処理
//---------------------------------
void	NormalMap::Create()
{
	if (!shader.Load("./data/Shader/NormalMap.fx"))
	{
		MessageBoxA(NULL, "シェーダの読み込みに失敗しました", "NormalMap.fx", MB_OK);
		return;
	}

	//テクスチャの読み込み
	LibTexture::Create("./data/Model/NormalModel/NormalMap.dds", &normalMap);
	LibTexture::Create("./data/Model/NormalModel/DiffuseMap.dds", &diffuseMap);

	//シェーダの設定
	worldHandle = shader.GetParameterName("matWorld");
	viewHandle = shader.GetParameterName("matView");
	projHandle = shader.GetParameterName("matProj");
	lightHandle = shader.GetParameterName("lightLocalDir");
	cameraHandle = shader.GetParameterName("cameraVec");
	normalHandle = shader.GetParameterName("normalMap");
	diffuseHandle = shader.GetParameterName("diffuseMap");
	technique = shader.GetParamTechnique("NormalMapShader");
}


//---------------------------------
//設定処理
//---------------------------------
void	NormalMap::SetWorldMatrix(D3DXMATRIX* mat)
{
	matWorld = *mat;
}
void	NormalMap::SetViewMatrix(D3DXMATRIX* mat)
{
	matView = *mat;
}
void	NormalMap::SetProjMatrix(D3DXMATRIX* mat)
{
	matProj = *mat;
}
void	NormalMap::SetCameraVec(D3DXVECTOR3& vec)
{
	cameraVec = vec;
}
void	NormalMap::SetLightDir(D3DXVECTOR3& vec)
{
	lightLocalDir = vec;
}

void	NormalMap::SetShaderParam()
{
	shader.SetMatrix(worldHandle, &matWorld);
	shader.SetMatrix(viewHandle, &matView);
	shader.SetMatrix(projHandle, &matProj);
	shader.SetVector(lightHandle, &D3DXVECTOR4(lightLocalDir, 0));
	shader.SetVector(cameraHandle, &D3DXVECTOR4(cameraVec, 0));
	shader.SetParamTexture(normalHandle, normalMap);
	shader.SetParamTexture(diffuseHandle, diffuseMap);
}



//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void	NormalMap::Begin()
{
	LibDGD::ViewAndStencilClear();

	shader.SetTechnique(technique);

	shader.Begin(0,0);
}
void	NormalMap::End()
{
	shader.End();
}

void	NormalMap::BeginPass()
{
	shader.BeginPass(0);
}
void	NormalMap::EndPass()
{
	shader.EndPass();
}
