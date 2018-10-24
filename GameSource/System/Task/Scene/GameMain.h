#pragma once

//�ǉ�--------------------
#include "../../../Library9/Camera.h"
#include "../../../Library9/Light.h"
#include "../../Game/Objects/Player.h"
#include "../../Game/Objects/Map.h"
#include "../../Game/Objects/Enemy.h"
#include "../../Game/Objects/Enemy2.h"
#include "../../Game/Effects/Particle.h"
#include "../../Game/Effects/Magic.h"
#include "../../Game/Objects/CameraMan.h"
#include "../../Game/Components/Sample.h"		//�T���v���p
#include "../TaskManager.h"
#include "../../Game/Objects/Object.h"
#include "../../Game/Components/smoke.h"
#include "../../Game/Objects/Obj.h"
#include "../../ShaderSystem/DepthTex.h"
#include "../../ShaderSystem/ZTexture.h"

//�Q�[�����C��
class GameMain
{
public:


	//��{����
	void	Initailize();
	void	Finalize();
	Task	UpDate();
	void	Render();


	//���C�g�̏���
	void	LightInit();
	void	LightUpDate();
	void	SetLightView(D3DXMATRIX* mat,D3DXVECTOR3& pos);

public:

	Light		light[4];

	//�v���C���[-----------
	Player		player;
	
	//�}�b�v---------------
	Map			map;

	//�G-------------------
	//Enemy		enemy;
	//Enemy2		enemy2;
	
	//����-----------------
	Input		input;
	char*		key;

	//�p�[�e�B�N��---------
	//Particle	particle;
	//MagicEffect	magicEff;

	//�T���v���p
	Samp		samp;
	Obj			obj;

	//�J�����}��
	CameraMan	cameraMan;
	
	//�I�u�W�F�N�g
	Object		object;

	//��
	//Smoke		smoke;

	ZTexture		zTexture;
	DepthTexture	depthTexture;
	
};