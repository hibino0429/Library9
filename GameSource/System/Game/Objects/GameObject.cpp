#include "GameObject.h"


//コンストラクタ
GameObject::GameObject()
{

}

//デストラクタ
GameObject::~GameObject()
{
	model.Erase();
}


//取得処理
//モデルの取得
Model&	GameObject::GetModel()
{
	return model;
}
//マトリックスの取得
Mat4X4::Matrix& GameObject::GetMatrix()
{
	return matrix;
}
//当たり判定Boxの取得
Box3D&	GameObject::GetBox3D()
{
	return hitBase;
}

//設定処理
void	GameObject::SetModel(const Model& model)
{
	this->model = model;
}

void	GameObject::SetMatrix(const Mat4X4::Matrix& mat)
{
	this->matrix = mat;
}

void	GameObject::SetHitBase(const Box3D& hitBox)
{
	this->hitBase = hitBox;
}

//モデルの生成
void	GameObject::CreateModel(const std::string& filePath,
								const D3DXVECTOR3& pos,
								const D3DXVECTOR3& angle,
								const D3DXVECTOR3& size)
{
	model.Load(filePath.c_str());
	model.SetPos(pos);
	model.SetAngle(angle);
	model.SetSize(size);

	this->AdjustBox();
}


//モデルの描画
//ZTexの描画
void	GameObject::ZTexRender(ZTexture* zTex)
{
	MatrixProcess();
	zTex->SetWorldMatrix(&matrix.mat);
	model.ZTexRender(zTex);
}
//深度テクスチャの描画
void	GameObject::DepthRender(DepthTexture* depTex)
{
	MatrixProcess();
	hitBase.Offset(model.GetPos());
	depTex->GetWorldMatrix(&matrix.mat);
	model.DepthRender(depTex);
}

//マトリックスに関して
//マトリックス処理の実行
void	GameObject::MatrixProcess()
{
	D3DXMATRIX	matT;
	D3DXMATRIX	matR;
	D3DXMATRIX	matS;

	D3DXMatrixTranslation(&matT, model.GetPos().x, model.GetPos().y, model.GetPos().y);
	D3DXMatrixRotationYawPitchRoll(&matR, D3DXToRadian(model.GetAngle().y), D3DXToRadian(model.GetAngle().x), D3DXToRadian(model.GetAngle().z));
	D3DXMatrixScaling(&matS, model.GetSize().x, model.GetSize().y, model.GetSize().z);

	matrix.mat = matS * matR * matT;
	matrix.SetMatrix(D3DTS_WORLD);
}


//private:
//モデルの大きさと当たり判定の大きさを合わせる
void	GameObject::AdjustBox()
{
	this->hitBase = Box3D(-model.GetSize().x / 2, -model.GetSize().y / 2, -model.GetSize().z / 2, 
		model.GetSize().x, model.GetSize().y, model.GetSize().z);
}