#pragma once
//
//#include "DepthTex.h"
//
//
////-----------------------------------------------------------------------
////深度バッファテクスチャ
////-----------------------------------------------------------------------
//namespace DepthTex
//{
//	void	Create();
//	void	SetShaderParam();
//
//	//-------------------
//	//マトリックスのセット
//	void	SetViewMatrix(D3DXMATRIX* mat);
//	void	SetProjMatrix(D3DXMATRIX* mat);
//	void	SetLightViewMatrix(D3DXMATRIX* mat);
//	void	SetLightProjMatrix(D3DXMATRIX* mat);
//	void	SetWorldMatrix(D3DXMATRIX* mat);
//
//	void	SetCameraManInfo(Camera* cameraMan);
//	void	SetLightInfo(Light* lightInfo);
//
//	void	SetMatrix();
//	//-------------------
//	//描画
//	void	Begin(UINT pass, DWORD flags);
//	void	End();
//
//	void	BeginPass();
//	void	EndPass();
//
//}