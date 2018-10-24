#include "Object.h"


//--------------------------------------------------------------------------
//����������
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
//�������
//--------------------------------------------------------------------------
void	Object::Finalize()
{
	myObject.Erase();
}


//--------------------------------------------------------------------------
//�X�V����
//--------------------------------------------------------------------------
void	Object::UpDate()
{

}


//--------------------------------------------------------------------------
//�`�揈��
//--------------------------------------------------------------------------
void	Object::Render()
{
	normalMap.SetWorldMatrix(&matWorld.mat);
	normalMap.SetShaderParam();		//�V�F�[�_�̃p�����[�^�Z�b�g

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






//�}�g���b�N�X�̏���
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

//3D�{�b�N�X�Ƃ̓����蔻��
bool	Object::CheckHit(Box3D& box)
{
	if (hitBox.Hit(box))
	{
		return true;
	}
	return false;
}



//�V�F�[�_�̎擾����
//�}�g���b�N�X����
void	Object::GetMatrix(D3DXMATRIX* mat, D3DXMATRIX* getmat)
{
	mat = getmat;
}
//�ʒu�E�x�N�g���̏���
void	Object::GetVector4(D3DXVECTOR4* vec, D3DXVECTOR4* getvec)
{
	vec = getvec;
}