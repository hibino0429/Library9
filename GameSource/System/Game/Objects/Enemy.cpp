#include "Enemy.h"

#include <string>


Enemy::Enemy()
{
	D3DXMatrixIdentity(&matW.mat);
}

Enemy::~Enemy()
{
	Finalize();
}


//�G�̏�����
void	Enemy::Initialize()
{
	model.Load(TEXT("./data/Model/Enemy/enemy1.x"));

	enemyLifeFont.Create(TEXT("MS �S�V�b�N"), 16, 16);

	model.pos = D3DXVECTOR3(0, 10, 100);
	model.angle = D3DXVECTOR3(0, 0, 0);
	model.size = D3DXVECTOR3(100, 100, 100);

	this->moveCnt = 0.0f;
	this->shotCnt = 0.0f;

	this->life = 10;

	this->active = true;

	point[0].pos = D3DXVECTOR3(100, 10, 10);
	point[1].pos = D3DXVECTOR3(200, 10, -40);
	point[2].pos = D3DXVECTOR3(-20, 10, -100);
	point[3].pos = D3DXVECTOR3(-400, 10, 200);
	point[4].pos = D3DXVECTOR3(50, 10, -500);
	point[5].pos = D3DXVECTOR3(-200, 10, 300);
	point[6].pos = D3DXVECTOR3(300, 10, 100);
	point[7].pos = D3DXVECTOR3(-600, 10, 100);
	point[8].pos = D3DXVECTOR3(0, 10, -300);
	point[9].pos = D3DXVECTOR3(70, 10, 500);
	
	setPoint = true;
	randPoint = 6;

	playerPos = D3DXVECTOR3(0, 0, 0);
	moveVec = D3DXVECTOR3(0, 0, 0);
	searchAngle = D3DXToRadian(120/2);
	searchDist = 30;
}

void	Enemy::Finalize()
{
	model.Erase();

	enemyLifeFont.Destory();

}

void	Enemy::UpDate()
{
	this->Chase();
}


void	Enemy::Render()
{

	//���f���̕`��
	D3DXMATRIX		mMove;
	D3DXMATRIX		mRot;
	D3DXMATRIX		mScale;

	D3DXMatrixTranslation(&mMove, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(model.angle.y), D3DXToRadian(model.angle.x), D3DXToRadian(model.angle.z));
	D3DXMatrixScaling(&mScale, model.size.x, model.size.y, model.size.z);

	matW.mat = mScale * mRot * mMove;

	matW.SetMatrix(D3DTS_WORLD);

	model.Render();


	enemyLifeFont.Render(TEXT("�G1"), Box2D(0, 0, 100, 100), D3DXCOLOR(1, 1, 1, 1));
}





//�_���[�W����
void	Enemy::LifeDecrease()
{
	if (this->life > 0)
	{
		this->life--;
	}
}



//�G�̏��񏈗�
void	Enemy::Patrol()
{
	//�G�̍X�V
	if (setPoint) {
		randPoint = rand() % 10;
		setPoint = false;
	}
	//1:�n�_�̈ʒu�ƓG�̈ʒu�̃x�N�g�����Z�o
	D3DXVECTOR3	vec = point[randPoint].pos - model.pos;
	//2:�x�N�g���̋�����ۑ����Ă����A���̕���(angle)�ֈړ�������

	//�x�N�g������p�x�𓾂�
	float angle = atan2(vec.z, vec.x);
	//���̊p�x�ֈړ�
	model.pos.x += cos(angle) * 1;
	model.pos.z += sin(angle) * 1;

	//3:�x�N�g���̋������A30���������ɂȂ�����A���̒n�_�ւ̃����_���ʒu�����߂�
	float dist = vec.x * vec.x + vec.z * vec.z;

	if (dist <= 30 && !setPoint)
	{
		setPoint = true;
	//	MessageBox(NULL, TEXT("���̒n�_�֐i�݂܂�"), TEXT("Let's�@Go"), MB_OK);
	}

}


//�G�̒ǐՏ���
void	Enemy::Chase()
{
	if (this->SearchAngle())
	{
		this->moveVec = D3DXVECTOR3(cos(this->angle.y), 0, sin(this->angle.y)) * 10.0f;
	}
	else
	{
		//Patrol();
	}
}


//�ʒu�̎擾
void		Enemy::GetPos(D3DXVECTOR3& pos)
{
	this->playerPos = pos;
}

//����p�����𒲂ׂ�
bool		Enemy::SearchAngle()
{
	//�G�̎���Ƀv���C���[�����������A�m�F����

	//1:�O�ς𗘗p���āA���E���������
	//�O�ς̌v�Z�́Ax1y2 - x2y1
	//�O�ς̌v�Z���ʂ́A
	float cross = 0.0f;

	//�G����v���C���[�ւ̋���
	//D3DXVECTOR3	toTarget = model.pos - playerPos;	//����
	D3DXVECTOR3	toTarget = playerPos - model.pos;
													//����p�͈͂ɂ���^�[�Q�b�g��Ώۂɂ���
	float	dist = toTarget.x * toTarget.x + toTarget.z * toTarget.z;

	if (dist < searchDist * searchDist)
	{
		D3DXVECTOR3	toTargetN;
		D3DXVec3Normalize(&toTargetN, &toTarget);	//���K��
		D3DXVECTOR3		moveVecN = D3DXVECTOR3(cos(this->angle.y), 0, sin(this->angle.y));

		//���ςō��E�ǂ��炩�̔���
		float dot = moveVecN.x * moveVecN.x + moveVecN.z * moveVecN.z;
		//����p������p�͈͂��傫���ꍇ
		if (dot > cos(searchAngle)) {
			//�ړ��̒���
			if (dot > cos(D3DXToRadian(4))) {
				
			//MessageBox(NULL, TEXT("�ǐՒ�"), TEXT("now chase"), MB_OK);
			}
			else {
				float cr = moveVecN.x * toTargetN.z - moveVecN.z * toTargetN.x;
				//���E�ɍ��킹�Đ��񂷂�
				if (cr >= 0) { this->angle.y += D3DXToRadian(4); }
				else { this->angle.y -= D3DXToRadian(4); }
				MessageBox(NULL, TEXT("���ς��܂�"), TEXT("������[�["), MB_OK);
				return true;
			}
		}
	}
	return false;
}




//�n�_�̏���
D3DXVECTOR3		Point::SendPos()
{
	return this->pos;
}

void			Point::ReceivePos(D3DXVECTOR3& pos)
{
	this->pos = pos;
}




