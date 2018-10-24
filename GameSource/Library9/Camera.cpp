#include "Camera.h"


//----------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------
Camera::Camera()
{
	D3DXMatrixIdentity(&m_view.mat);
	D3DXMatrixIdentity(&m_proj.mat);
}

//----------------------------------------------------------
//デストラクタ
//----------------------------------------------------------
Camera::~Camera()
{
	
}


//----------------------------------------------------------
//カメラの初期化
//----------------------------------------------------------
void	Camera::Initialize()
{
	this->pos = D3DXVECTOR3(300, 10, 10);
	this->targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->upVec		= D3DXVECTOR3(0, 1, 0);

	this->fovy = 45.0f;
	this->zMin = 1.0f;
	this->zMax = 4000.0f;

	D3DXMatrixLookAtLH(&m_view.mat, &pos, &targetPos, &upVec);

	m_view.SetMatrix(D3DTS_VIEW);
}


//---------------------------------------------------------
//カメラの更新
//---------------------------------------------------------
void	Camera::UpDate()
{
	D3DVIEWPORT9	vp;
	if (!LibDGD::SetViewPort(&vp)) { return; }

	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveLH(&m_proj.mat,
		D3DXToRadian(fovy),
		aspect,
		zMin,
		zMax);

	m_proj.SetMatrix(D3DTS_PROJECTION);

	D3DXMatrixLookAtLH(&m_view.mat, &pos, &targetPos, &upVec);

	m_view.SetMatrix(D3DTS_VIEW);

}


//-----------------------------------------------------
//カメラの描画
//-----------------------------------------------------
void	Camera::Render()
{
	this->UpDate();

}


//カメラの位置を変更する
void	Camera::SetPos(const D3DXVECTOR3& pos_)
{
	this->pos = pos_;
}

//カメラの注視点を変更する
void	Camera::SetTargetPos(const D3DXVECTOR3& targetPos_)
{
	this->targetPos = targetPos_;
}

//カメラの上ベクトルを変更する
void	Camera::SetUpVec(const D3DXVECTOR3& upVec_)
{
	this->upVec = upVec_;
}


//カメラの位置を返す
D3DXVECTOR3	Camera::GetPos()
{
	return this->pos;
}

//カメラの注視点を返す
D3DXVECTOR3	Camera::GetTarget()
{
	return this->targetPos;
}

//カメラの上ベクトルを返す
D3DXVECTOR3	Camera::GetUpVec()
{
	return this->upVec;
}

//ビューマトリックス
D3DXMATRIX	Camera::PassViewMatrix()
{
	return this->m_view.mat;
}

//プロジェクションマトリックス
D3DXMATRIX	Camera::PassProjMatrix()
{
	return this->m_proj.mat;
}