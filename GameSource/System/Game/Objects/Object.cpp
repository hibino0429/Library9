#include "Object.h"


//--------------------------------------------------------------------------
//初期化処理
//--------------------------------------------------------------------------
void	Object::Initialize()
{

	myObject.Load(TEXT("./data/Model/NormalModel/Sphere.x"));
	myObject.pos = D3DXVECTOR3(0, 0, 0);
	myObject.angle = D3DXVECTOR3(0, 0, 0);
	myObject.size = D3DXVECTOR3(50, 70, 50);

	normalMap.Create();
}



//--------------------------------------------------------------------------
//解放処理
//--------------------------------------------------------------------------
void	Object::Finalize()
{
	myObject.Erase();
}


//--------------------------------------------------------------------------
//更新処理
//--------------------------------------------------------------------------
void	Object::UpDate()
{

}


//--------------------------------------------------------------------------
//描画処理
//--------------------------------------------------------------------------
void	Object::Render()
{
	normalMap.SetWorldMatrix(&matWorld.mat);
	normalMap.SetShaderParam();		//シェーダのパラメータセット

	Matrix(myObject.pos, myObject.angle, myObject.size);

	normalMap.Begin();
	normalMap.BeginPass();
	myObject.Render();
	normalMap.EndPass();
	normalMap.End();
	
}

void	Object::ZTexRender(ZTexture* zTex)
{
	Matrix(myObject.pos, myObject.angle, myObject.size);
	zTex->SetWorldMatrix(&matWorld.mat);
	myObject.ZTexRender(zTex);
}

void	Object::DepthRender(DepthTexture* depTex)
{
	Matrix(myObject.pos, myObject.angle, myObject.size);
	depTex->GetWorldMatrix(&matWorld.mat);
	myObject.DepthRender(depTex);
}






//マトリックスの処理
void	Object::Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	matWorld.mat = mScale * mRot * mMove;
	matWorld.SetMatrix(D3DTS_WORLD);
}

//3Dボックスとの当たり判定
bool	Object::CheckHit(Box3D& box)
{
	if (hitBox.Hit(box))
	{
		return true;
	}
	return false;
}



//シェーダの取得処理
//マトリックス処理
void	Object::GetMatrix(D3DXMATRIX* mat, D3DXMATRIX* getmat)
{
	mat = getmat;
}
//位置・ベクトルの処理
void	Object::GetVector4(D3DXVECTOR4* vec, D3DXVECTOR4* getvec)
{
	vec = getvec;
}