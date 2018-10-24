#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Light.h"
#include "../../../Library9/Model/Model.h"

//---------------------------------------------------------
//�X���I�u�W�F�N�g
//---------------------------------------------------------
class StreetLight
{
public:
	StreetLight();
	~StreetLight();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	//���̂ق��̋@�\
	void	GetPos(const D3DXVECTOR3& pos);		//�X���̈ʒu���擾
	void	SetUseLight(int number);		//�g�p���郉�C�g�̔ԍ�

public:
	//�萔

	//�ϐ�
	//���C�g�̕ω�
	float	frameCnt;
	float	timeCnt;
	Box3D	hitBox;			//�Փ˔���

public:
	//�I�u�W�F�N�g
	Model	streetLight;
	Light			light;		//���C�g�I�u�W�F�N�g
	
public:
	Mat4X4::Matrix	world;
};