#include "LibDepthTex.h"



//namespace DepthTex
//{
//	void	Create()
//	{
//		depTex->Create();
//		depTex->Initialize();
//	}
//
//	void	SetShaderParam()
//	{
//		depTex->SetEffectParam();
//	}
//
//	void	SetWorldMatrix(D3DXMATRIX* mat)
//	{
//		depTex->GetWorldMatrix(mat);
//	}
//
//	void	SetCameraManInfo(Camera* cameraMan)
//	{
//		depTex->GetCameraMatrix(cameraMan);
//	}
//	void	SetLightInfo(Light* lightInfo)
//	{
//		depTex->GetLightInfo(lightInfo);
//	}
//
//	//使ってはいけない
//	void	SetMatrix()
//	{
//		depTex->Render();
//	}
//
//	//---------------------------------------
//	//描画
//	void	Begin(UINT pass, DWORD flags)
//	{
//		depTex->Begin(pass, flags);
//	}
//	void	End()
//	{
//		depTex->End();
//	}
//	void	BeginPass()
//	{
//		depTex->BeginPass();
//	}
//	void	EndPass()
//	{
//		depTex->EndPass();
//	}
//}