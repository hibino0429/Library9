#include "Explode.h"

//�R���X�g���N�^
Explode::Explode() : active(false)
{
	D3DXMatrixIdentity(&world.mat);
}

//�f�X�g���N�^
Explode::~Explode()
{
	this->Finalize();
}




//----------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------
void	Explode::Initialize()
{
	//��
	//this->pos = D3DXVECTOR3(0, 0, 0);	
	//this->angle = D3DXVECTOR3(0, 0, 0);
	//this->size = D3DXVECTOR3(5, 5, 5);

	this->timeCnt = 0.0f;
	this->active = true;


	//���f���̓ǂݍ���
	model.Load(TEXT("explodeX.x"));

}

//----------------------------------------------------------------------------
//�������
//----------------------------------------------------------------------------
void	Explode::Finalize()
{
	model.Erase();
}


//----------------------------------------------------------------------------
//�X�V����
//----------------------------------------------------------------------------
void	Explode::UpDate()
{
	if (!this->active) { return; }

	//��
	this->timeCnt++;
	if (timeCnt >= 180) { this->active = false; this->timeCnt = 0; }
	

	//this->timeCnt++;
	//if (timeCnt > 120.0f) { this->active = false; this->timeCnt = 0; }
	//this->angle.y++;

	//if (timeCnt <= 60.0f)
	//{
	//	//MessageBox(NULL, TEXT("�g�債�܂�"), TEXT("UpDate"), MB_OK);
	//	this->size.x += 1.0f;
	//	this->size.y += 1.0f;
	//	this->size.z += 1.0f;
	//}
	//else if (timeCnt <= 120.0f)
	//{
	//	//MessageBox(NULL, TEXT("�k�����܂�"), TEXT("UpDate"), MB_OK);
	//	this->size.x -= 1.0f;
	//	this->size.y -= 1.0f;
	//	this->size.z -= 1.0f;
	//}

}


//----------------------------------------------------------------------------
//�`�揈��
//----------------------------------------------------------------------------
void	Explode::Render()
{
	if (!this->active) { return; }

	//scene�̃N���A
	LibDGD::ZBufClear();

	//�}�g���b�N�X����
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;

	world.SetMatrix(D3DTS_WORLD);

	model.Render();
}



