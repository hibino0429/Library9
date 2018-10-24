#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Camera.h"
#include "Player.h"


//�Q�Ƃ���N���X------------------------------------------------------
class Player;



//--------------------------------------------------------------------
//�J�����}���N���X
//--------------------------------------------------------------------
class CameraMan
{
public:
	CameraMan();
	~CameraMan();


	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	
	//�v���C���[�̈ʒu���擾
	void	GetPlayerPos(Player* player);
	
	//�v���C���[�̈ʒu���Z�b�g
	void	GetKeyboard(char* key);
	char*	keys;

	//�J�����}���̈ړ�
	void	CircleMove(Player* player);
	int		angleAxis;

	
	//�n������
	D3DXMATRIX	PassViewMatrix();		//�r���[�}�g���b�N�X��n��
	D3DXMATRIX	PassProjMatrix();		//�v���W�F�N�V�����}�g���b�N�X��n��

public:
	Camera			camera;

public:

	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	float			dist;				//����
	float			viewPointHeight;	//���_�̍���
	float			pointOfGazeHeight;	//�����_�̍���
};