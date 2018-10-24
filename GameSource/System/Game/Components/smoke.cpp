#include "smoke.h"

//===========================================================================================
//-------------------------------------------------------------------------------------------
//��1�̃N���X
//-------------------------------------------------------------------------------------------
//===========================================================================================
OneSmoke::OneSmoke() : texture(NULL), m_pVerBuf(NULL)
{
	
}

OneSmoke::~OneSmoke()
{
	
}

//�r���{�[�h�̐���
void	OneSmoke::Create()
{
	//------------------------------------------
	//�r���{�[�h�Ɋւ��鏈��
	LibDGD::CreateVertexBuffer(
		4 * sizeof(Vertex),
		SMOKE_FVF,
		&m_pVerBuf);

	LibDGD::CreateTexVertexBuf("./data/Image/Hig.png", &texture);

	Vertex* smokeVertex;
	if (FAILED(m_pVerBuf->Lock(0, 0, (void**)&smokeVertex, 0))) { return; }

	smokeVertex[0].tex = D3DXVECTOR2(0, 0);
	smokeVertex[1].tex = D3DXVECTOR2(1, 0);
	smokeVertex[2].tex = D3DXVECTOR2(0, 1);
	smokeVertex[3].tex = D3DXVECTOR2(1, 1);

	smokeVertex[0].diffuse = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	smokeVertex[1].diffuse = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	smokeVertex[2].diffuse = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	smokeVertex[3].diffuse = (DWORD)D3DXCOLOR(1, 1, 1, 1);

	smokeVertex[0].pos = D3DXVECTOR3(-0.5f, -0.5f, 0);
	smokeVertex[1].pos = D3DXVECTOR3(0.5f, -0.5f, 0);
	smokeVertex[2].pos = D3DXVECTOR3(-0.5f, 0.5f, 0);
	smokeVertex[3].pos = D3DXVECTOR3(0.5f, 0.5f, 0);

	m_pVerBuf->Unlock();
}
//����������
void	OneSmoke::Initialize()
{
	//------------------------------------
	//��{�����Ɋւ��鏈��
	int	posRand = rand() % 20 - 20 / 2;		//20�͔͈͂̕�������(�ϐ��ɂ���)
	int VelRand = rand() % 5;				//�����x�͈̔͂�����
	int sizeRand = rand() % 6 - 6 / 2;		//�傫���̕�������
	int	timeRand = rand() % 60 - 60 / 2;	//������t���[����������

	lifeTime = 0;
	lifeTimeCnt = 0;
	pos = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(10, 10, 10);
	velocity = D3DXVECTOR3(0, 0, 0);
	active = false;
}

//�������
void	OneSmoke::Finalize()
{
	if (m_pVerBuf != NULL) { m_pVerBuf->Release(); m_pVerBuf = NULL; }
	if (texture != NULL) { texture->Release(); texture = NULL; }
}

//�X�V����
void	OneSmoke::UpDate()
{
	if (!active) { return; }
	//���x�Ȃǂ�
	//�ړ��E��]�E�g�又��
	pos += velocity;
	
	//�������ԂɂȂ�����A���̈ʒu�ɖ߂�悤�ɂ���

	//��������
	lifeTimeCnt++;
	if (LimitLifeTime())
	{
		ActiveFlag(false);
	}
}

//�`�揈��
void	OneSmoke::Render()
{
	if (!active) { return; }

	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);
	D3DXMatrixRotationY(&mRot, D3DXToRadian(angle.y));
	mRot = Inverse.mat;	//�`�F�b�N
	world.mat = mScale * mRot *  mMove;
	world.SetMatrix(D3DTS_WORLD);

	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	
	LibDGD::SetTexStageState(1, D3DTSS_ALPHAOP, D3DTSS_ALPHAARG1);
	LibDGD::SetTexStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	LibDGD::SetVertexBuf(0, m_pVerBuf, 0, sizeof(Vertex));
	LibDGD::SetTexture(0, texture);
	LibDGD::SetFVF(SMOKE_FVF);
	LibDGD::VertexRender(D3DPT_TRIANGLESTRIP, 0, 2);
	LibDGD::SetTexture(0, NULL);
}


//�r���[�}�g���b�N�X���󂯎��
void	OneSmoke::ReceiveViewMatrix(D3DXVECTOR3& eyePos, D3DXVECTOR3& targetPos, D3DXVECTOR3& upVec)
{
	D3DXMatrixIdentity(&Inverse.mat);
	D3DXMatrixLookAtLH(&Inverse.mat, &this->pos, &targetPos, &upVec);
	D3DXMatrixInverse(&Inverse.mat, NULL, &Inverse.mat);
	Inverse.mat._41 = 0;
	Inverse.mat._42 = 0;
	Inverse.mat._43 = 0;
}


//�󂯎�鏈��
void	OneSmoke::ReceivePos(D3DXVECTOR3& pos)
{
	this->pos = pos;
}
void	OneSmoke::ReceiveAngle(D3DXVECTOR3& angle)
{
	this->angle = angle;
}
void	OneSmoke::ReceiveSize(D3DXVECTOR3& size)
{
	this->size = size;
}

void	OneSmoke::SetLifeTime(int lifeTime)
{
	this->lifeTime = lifeTime;
}
void	OneSmoke::SetVelocity(D3DXVECTOR3& vel)
{
	velocity = vel;
}

bool	OneSmoke::LimitLifeTime()
{
	if (lifeTimeCnt >= lifeTime)
	{
		return true;
	}
	return false;
}

void	OneSmoke::ActiveFlag(bool flag)
{
	active = flag;
}

bool	OneSmoke::GetActiveFlag()
{
	return active;
}


//-------------------------------------------------------------------------------------------
//���N���X
//-------------------------------------------------------------------------------------------
//�R���X�g���N�^
Smoke::Smoke() 
{
	
}


//����������
void	Smoke::Initialize()
{
	pos = D3DXVECTOR3(-100, 20, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(1, 1, 1);

	for (int i = 0; i < maxSmokeCnt; ++i)
	{
		oneSmoke[i].Create();
	}
}

//�������
void	Smoke::Finalize()
{
	Destroy();
}

//�X�V����
void	Smoke::UpDate()
{
	for (int i = 0; i < maxSmokeCnt; ++i)
	{
		//������o��
		if (!oneSmoke[i].GetActiveFlag())
		{
			Create(i);
		}
		//���̍X�V
		oneSmoke[i].UpDate();
	}
}

//�`�揈��
void	Smoke::Render()
{
	Matrix(pos, angle, size);
	for (int i = 0; i < maxSmokeCnt; ++i)
	{
		//���̕`��
		oneSmoke[i].Render();
	}
}



void	Smoke::Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	world.mat = mScale * mRot * mMove;
	world.SetMatrix(D3DTS_WORLD);
}


void	Smoke::Create(int i)
{
	int ranPos = rand() % 20 - 10;
	int ransize = rand() % 10 - 10 / 2;
	int ranVel = rand() % 4 - 4 / 2;

	D3DXVECTOR3 rpos(pos.x + ranPos, pos.y, pos.z);
	D3DXVECTOR3 rangle(0, -45, 0);
	D3DXVECTOR3 rsize(50, 50, 50);
	D3DXVECTOR3	rvel((float)ranVel, (float)ranVel, (float)ranVel);

	oneSmoke[i].Initialize();

	oneSmoke[i].ActiveFlag(true);	//�A�N�e�B�u�ɂ���
	oneSmoke[i].SetLifeTime(300);	//5�b
	oneSmoke[i].SetVelocity(rvel);	//����
	oneSmoke[i].ReceivePos(rpos);
	oneSmoke[i].ReceiveAngle(rangle);
	oneSmoke[i].ReceiveSize(rsize);
}

void	Smoke::Destroy()
{
	for (int i = 0; i < maxSmokeCnt; ++i)
	{
		if (oneSmoke[i].LimitLifeTime())
		{
			oneSmoke[i].ActiveFlag(false);
		}
	}
}


//�r���[�}�g���b�N�X���󂯎��
void	Smoke::SetViewMatrix(D3DXVECTOR3& eyePos, D3DXVECTOR3& targetPos, D3DXVECTOR3& upVec)
{
	for (int i = 0; i < maxSmokeCnt; ++i)
	{
		oneSmoke[i].ReceiveViewMatrix(eyePos, targetPos, upVec);
	}
}