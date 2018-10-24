#pragma once
#include "../../Library9/Shader.h"

//-------------------------------------------------------------/
//法線マップを使用し、よりリアルな質感を表現する
//-------------------------------------------------------------/


//-------------------------------------------------------------
//法線マップクラス
//-------------------------------------------------------------
class NormalMap
{
public:

	void	Create();

	//設定処理
	void	SetWorldMatrix(D3DXMATRIX* mat);
	void	SetViewMatrix(D3DXMATRIX* mat);
	void	SetProjMatrix(D3DXMATRIX* mat);
	void	SetLightDir(D3DXVECTOR3& vec);
	void	SetCameraVec(D3DXVECTOR3& vec);

	//シェーダの設定処理
	void	SetShaderParam();

	//描画処理
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