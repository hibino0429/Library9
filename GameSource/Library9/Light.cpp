#include "Light.h"


//--------------------------------------------------------------
//コンストラクタ
//--------------------------------------------------------------
Light::Light()
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	number = 0;
	useFlag = false;

	D3DXMatrixIdentity(&world.mat);

}


//--------------------------------------------------------------
//デストラクタ
//--------------------------------------------------------------
Light::~Light()
{

}


//--------------------------------------------------------------
//ライトの初期化
//--------------------------------------------------------------
void	Light::Initalize()
{
	//ライトの共通処理
	LibDGD::SetLight(number, &m_light);					//ライトにセットする
	LibDGD::SetUseLight(number, useFlag);				//ライトの使用設定
	LibDGD::SetRenderState(D3DRS_LIGHTING, useFlag);	//ライティングモードの設定

	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(1, 1, 1);
}

//--------------------------------------------------------------
//ライト解放
//--------------------------------------------------------------
void	Light::Finalize()
{

}

//--------------------------------------------------------------
//ライトの更新
//--------------------------------------------------------------
void	Light::UpDate()
{
	
}

//--------------------------------------------------------------
//ライトの描画
//--------------------------------------------------------------
void	Light::Render()
{
	SetMatrix(position, angle, size);
}


void	Light::SetMatrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x,pos.y,pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale,size.x,size.y,size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);
}


//番号の指定
void	Light::SetNumber(int num)
{
	this->number = num;
}

//使用するかの指定
void	Light::SetUse(bool flag)
{
	this->useFlag = flag;
}

//タイプの設定
void	Light::SetType(D3DLIGHTTYPE type)
{
	m_light.Type = type;
}

//ディフューズ色の設定
void	Light::SetDiffuse(D3DXCOLOR diffuse)
{
	m_light.Diffuse = diffuse;
}

//スペキュラー色の設定
void	Light::SetSpecular(D3DXCOLOR specular)
{
	m_light.Specular = specular;
}

//アンビエント色の設定
void	Light::SetAmbient(D3DXCOLOR ambient)
{
	m_light.Ambient = ambient;
}

//光源の位置の設定
void	Light::SetPosition(D3DXVECTOR3 pos)
{
	m_light.Position = pos;
}

//光の方向
void	Light::SetDirection(D3DXVECTOR3 dir)
{
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &dir);
}

//光源の有効範囲
void	Light::SetRange(float range)
{
	m_light.Range = range;
}

//スポットライトの外部コーンの減衰
void	Light::SetFalloff(float falloff = 1.0f)
{
	m_light.Falloff = falloff;
}

//光の減衰
void	Light::SetAttenuation(float attenuation)
{
	m_light.Attenuation0 = attenuation;
	m_light.Attenuation1 = attenuation;
	m_light.Attenuation2 = attenuation;
}

//スポットライトの内部コーンの角度
void	Light::SetTheta(float theta)
{
	m_light.Theta = theta;
}

//スポットライトの外部コーンの角度
void	Light::SetPhi(float phi)
{
	m_light.Phi = phi;
}

//ワールドマトリックスを渡す
D3DXMATRIX	Light::PassWorldMatrix()
{
	return this->world.mat;
}