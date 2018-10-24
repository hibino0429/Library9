#include "Sample.h"

//�R���X�g���N�^
Samp::Samp() 
{
	D3DXMatrixIdentity(&world.mat);
}

//�f�X�g���N�^
Samp::~Samp()
{

}



//-----------------------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------------------
void	Samp::Initialize()
{



	//���[���h��Ԃ̍��W���������
	Arrow.Load(TEXT("./data/Model/Map/arrow.x"));
	Arrow.pos = D3DXVECTOR3(0, 0, 0);
	Arrow.angle = D3DXVECTOR3(0, 0, 0);
	Arrow.size = D3DXVECTOR3(30, 30, 30);


	//��
	fire.Load(TEXT("./data/Model/Map/fire4.x"));
	fire.pos = D3DXVECTOR3(-300, 0, 0);
	fire.angle = D3DXVECTOR3(0, 0, 0);
	fire.size = D3DXVECTOR3(30, 30, 30);

	hitModel = Box3D(-20, -60, -20, 40, 120, 40);

	//���C�g�̐ݒ�
	light.SetNumber(3);
	light.SetUse(true);
	//�|�C���g���C�g
	//�K�v�Ȃ���
	//�^�C�v�E�ʒu�E���̗L�������E���̌����E�f�B�t���[�Y�F, (�X�y�L�����[�F)
	light.SetType(D3DLIGHT_POINT);
	light.SetDiffuse(D3DXCOLOR(1.0f, 0.2f, 0, 1));
	light.SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	light.SetPosition(D3DXVECTOR3(fire.pos.x, fire.pos.y + 20, fire.pos.z));
	light.SetPosition(D3DXVECTOR3(-300, 10, 0));
	light.SetAttenuation((1.0f / 2000.0f) * (1.0f / 2000.0f));
	light.SetRange(750.0f);

	light.Initalize();

	frameCnt = 0.0f;
	timeCnt = 0.0f;



	//�X��
	streetLight.Initialize();
	streetLight.GetPos(D3DXVECTOR3(300, 0, -20));


}


//�������
void	Samp::Finalize()
{

	Arrow.Erase();
	fire.Erase();

	light.SetUse(false);

}


//-----------------------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------------------
void	Samp::UpDate()
{
	frameCnt++;
	int randam = 0;
	if (frameCnt >= 10.0f)
	{
		frameCnt = 0;
		randam = rand() % 20;
		timeCnt += 1 + randam;
	}
	if (timeCnt >= 60.0f)
	{
		timeCnt = 2.0f + randam;
	}

	//�X��
	streetLight.UpDate();

}


//-----------------------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------------------
void	Samp::Render()
{

	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	Arrow.Render();


	Matrix(fire.pos, fire.angle, fire.size);
	fire.Render();
	
	//���C�g
	light.SetAttenuation((sinf(2 * 3.14f/180 * (timeCnt)) + 0.02f) * ((1.0f / 2000.0f) * (1.0f / 2000.0f)));
	light.Initalize();


	//�X��
	streetLight.Render();

	hitModel.Offset(fire.pos);

	
}



//Z�l�e�N�X�`���̕`��
void	Samp::ZTexRender(ZTexture* zTex)
{
	//���̃I�u�W�F�N�g
	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	zTex->SetWorldMatrix(&world.mat);
	Arrow.ZTexRender(zTex);

	//���̃I�u�W�F�N�g
	Matrix(fire.pos, fire.angle, fire.size);
	zTex->SetWorldMatrix(&world.mat);
	fire.ZTexRender(zTex);
}

void	Samp::DepthRender(DepthTexture* depTex)
{
	//���̃I�u�W�F�N�g
	Matrix(Arrow.pos, Arrow.angle, Arrow.size);
	depTex->GetWorldMatrix(&world.mat);
	Arrow.DepthRender(depTex);

	//���̃I�u�W�F�N�g
	Matrix(fire.pos, fire.angle, fire.size);
	depTex->GetWorldMatrix(&world.mat);
	fire.DepthRender(depTex);

	//���C�g
	light.SetAttenuation((sinf(2 * 3.14f / 180 * (timeCnt)) + 0.02f) * ((1.0f / 2000.0f) * (1.0f / 2000.0f)));
	light.Initalize();
}



//�}�g���b�N�X����
void	Samp::Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y),D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);
}

//�{�b�N�X�Ƃ̓����蔻��
bool	Samp::BoxHitCheck(Box3D& box)
{
	if (hitModel.HitCheck(box))
	{
		//MessageBox(NULL, TEXT("�Փ˂��܂���"), TEXT("�I�b�P�["), MB_OK);
		return true;
	}
	return false;
}





