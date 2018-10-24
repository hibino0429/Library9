#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Model/PolygonBox.h"
#include "../Objects/StreetLight.h"
#include "../../../Library9/Sound/SoundManager.h"
#include "../../../Library9/Model/Model.h"

//�T���v���N���X
//DirectX�̎������s��
class Samp
{
public:

	Samp();
	~Samp();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//�}�b�v�Ƃ̓����蔻��
	bool	BoxHitCheck(Box3D& box);

	//�}�g���b�N�X����
	void	Matrix(D3DXVECTOR3& pos, D3DXVECTOR3& angle, D3DXVECTOR3& size);

public:
	
	//���[���h��Ԃ�XYZ�̕������߂����f��
	Model	Arrow;
	Model	fire;	//��

	Mat4X4::Matrix	world;

public:
	
	//���C�g
	Light		light;

public:

	//���f���̏��
	Model		model;
	Box3D		hitModel;


	//���C�g�̔g�̒���
	float	frameCnt;	//�t���[���J�E���g
	float	timeCnt;	//�b
	float	value;		//�ψʒl



	StreetLight	streetLight;	//�X��

public:
	
	PolyBox			obj1Box;
	PolyBox			obj2Box;
	Box3D			obj1HitBox;
	Box3D			obj2HitBox;

	D3DXVECTOR3		vertexPos;
	D3DXVECTOR3		vertexSize;


	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);
};