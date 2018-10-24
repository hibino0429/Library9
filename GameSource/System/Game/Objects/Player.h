#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Input/Input.h"

//�ǉ�
#include "CameraMan.h"
#include "../../../Library9/Sound/SoundManager.h"
#include "Map.h"
#include "../../../Library9/Texture/Texture.h"
#include "../../../Library9/Font/Font.h"
#include <string>
#include "../../../Library9/Model/Model.h"

#include "../../ShaderSystem/ZTexture.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/NormalMap.h"
#include "../../ShaderSystem/DiffuseMap.h"

//�Q�Ƃ���N���X--------------------------------------------
class CameraMan;
class Map;

//----------------------------------------------------------
//�v���C���[�N���X
//----------------------------------------------------------
class Player
{
public:

	Player();
	~Player();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//�v���C���[�̐���
	static Player*	Create(bool flag);

	//�v���C���[�̔j��
	void	Destroy();


	void	GetKey(int key);
	void	GetKeyboard(char*);

	//�����蔻��
	bool	Hit(D3DXVECTOR3* min, D3DXVECTOR3* max);


	//�J�����}���̌������擾
	void	GetCameraManAngle(CameraMan* cameraMan);

	void	GetCameraManAngle(D3DXVECTOR3& angle);
	D3DXVECTOR3	GetPos();

	//�߂荞�܂Ȃ��ړ�
	void	CheckMove(D3DXVECTOR3& est_,Map* map);


	//�ړ�����
	void	Move(Map* map);
	void	Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size);

public:
	
	//���̕ϐ�-----------------------------------------------
	D3DXVECTOR3		cameraManAngle = D3DXVECTOR3(0,0,0);	//�J�����}���̌���


public:
	Texture			tex;
	Font			font;
	//�T�E���h
	//Sounds			shot;
	//Sounds			jump;

	//�v���C���[�̏��
	bool			active;
	int				key;

	char*			keys;
	float		turnSpeed;		//�J�����̐��񑬓x
	float			speed;		//�X�s�[�h

	PolyBox			polyBox;		//�|���S���{�b�N�X
	Box3D			hitBox;			//�����蔻��{�b�N�X

	Model	model;
	Mat4X4::Matrix	matW;		//�}�g���b�N�X
	
	void		ZRendere(ZTexture* zTex);
	void		DepthRender(DepthTexture* depTex);

	//�f�B�t���[�Y�}�b�v
	DiffuseMap		diffuseMap;
	D3DXVECTOR3		lightDir;
	D3DXVECTOR3		lightColor;
	D3DXMATRIX		view;
	D3DXMATRIX		proj;
	void	GetLightInfo(Light* light);	//���C�g�̏��
	void	GetCameraInfo(CameraMan* cameraMan);
};

