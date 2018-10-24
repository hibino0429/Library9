#include "CameraMan.h"


//�R���X�g���N�^
CameraMan::CameraMan()
{

}


//�f�X�g���N�^
CameraMan::~CameraMan()
{
	
}


//---------------------------------------------------------------------------
//����������
//---------------------------------------------------------------------------
void	CameraMan::Initialize()
{
	camera.Initialize();


	this->pos = D3DXVECTOR3(0, 0, 0);
	this->angle = D3DXVECTOR3(0, 0, 0);
	this->size = D3DXVECTOR3(1, 1, 1);

	dist = 300.0f;
	viewPointHeight = +250.0f;
	pointOfGazeHeight = +150.0f;

	angleAxis = 0;
}



//---------------------------------------------------------------------------
//�������
//---------------------------------------------------------------------------
void	CameraMan::Finalize()
{
	
}



//---------------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------------
void	CameraMan::UpDate()
{
	//���E�̐���
	//if (keys[DIK_A] & 0x80) { this->angle.y += 2.0f; }
	//if (keys[DIK_S] & 0x80) { this->angle.y -= 2.0f; }

	angleAxis = 0;
	if (keys[DIK_A] & 0x80) { angleAxis = 1; }
	if (keys[DIK_S] & 0x80) { angleAxis = -1; }

	
	
	camera.UpDate();
}


//---------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------
void	CameraMan::Render()
{
	camera.Render();
}






//�J�����̎擾
void	CameraMan::GetPlayerPos(Player* player)
{
	//���E�̐���
	this->angle.y += player->turnSpeed * D3DXToRadian(30);

	D3DXVECTOR3		vec(0, 0, -dist);
	D3DXMATRIX		matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(this->angle.y));
	D3DXVec3TransformCoord(&vec, &vec, &matR);
	this->pos = player->model.pos + vec;

	//�J�����̈ʒu�E�����̌���
	camera.SetTargetPos(player->model.pos + D3DXVECTOR3(0,+100,0));
	camera.SetPos(pos + D3DXVECTOR3(0, 300, 0));
}





//�L�[�{�[�h�̓��͂��擾
void	CameraMan::GetKeyboard(char* key)
{
	this->keys = key;
}


//�J�����}���̉~���ړ�
void	CameraMan::CircleMove(Player* player)
{
	//���E�̐���
	this->angle.y += this->angleAxis * D3DXToRadian(30);

	D3DXVECTOR3		vec(0, 0, -dist);
	D3DXMATRIX		matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(this->angle.y));
	D3DXVec3TransformCoord(&vec, &vec, &matR);
	this->pos = player->model.pos + vec;


	//�J�����̈ʒu�E�����̌���
	camera.SetTargetPos(player->model.pos + D3DXVECTOR3(0, +30, 0));
	camera.SetPos(this->pos + D3DXVECTOR3(0, 200, 0));
}


//�r���[�}�g���b�N�X��n��
D3DXMATRIX	CameraMan::PassViewMatrix()
{
	return	this->camera.PassViewMatrix();
}

//�v���W�F�N�V�����}�g���b�N�X��n��
D3DXMATRIX	CameraMan::PassProjMatrix()
{
	return	this->camera.PassProjMatrix();
}