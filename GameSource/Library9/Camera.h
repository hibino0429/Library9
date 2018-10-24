#pragma once

#include "Function.h"
#include "../Library9/Input/Input.h"

//カメラ
class Camera
{
public:

	Camera();
	~Camera();

	//基本処理
	void	Initialize();
	void	UpDate();
	void	Render();

	void	SetPos(const D3DXVECTOR3& pos_);		//視点のセット
	void	SetTargetPos(const D3DXVECTOR3& targetPos_);	//注視点のセット
	void	SetUpVec(const D3DXVECTOR3& upVec_);			//上ベクトルのセット

	D3DXVECTOR3	GetPos();		//位置を返す
	D3DXVECTOR3	GetTarget();	//注視点を返す
	D3DXVECTOR3	GetUpVec();		//上ベクトルを返す

	D3DXMATRIX	PassViewMatrix();	//ビューマトリックス
	D3DXMATRIX	PassProjMatrix();	//プロジェクトションマトリックス

private:
	D3DXVECTOR3		pos;		//位置
	D3DXVECTOR3		targetPos;	//注視点
	D3DXVECTOR3		upVec;		//上ベクトル

private:
	float			fovy;		//カメラの画角
	//float			aspect;		//カメラのアスペクト比
	float			zMin;		//カメラnearプレーン
	float			zMax;		//カメラfarプレーン

	Mat4X4::Matrix	m_view;		//ビューマトリックス
	Mat4X4::Matrix	m_proj;		//プロジェクションマトリックス

};