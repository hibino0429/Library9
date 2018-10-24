#pragma once

#include "../../../Library9/Function.h"
#include "../../../Library9/Camera.h"
#include "../../../Library9/Model/PolygonBox.h"
#include "../Objects/StreetLight.h"


//----------------------------------------------------------------------------------------
//�}�b�v
//----------------------------------------------------------------------------------------
class Map
{
public:

	Map();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();


	//�}�g���b�N�X����
	void	WorldMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);


	//�ʒu�̐ݒ�
	void	SetPos(D3DXVECTOR3&);
	void	SetAngle(D3DXVECTOR3&);
	void	SetSize(D3DXVECTOR3&);


	//�J�����̈ʒu���擾����
	void	GetCameraPos(Camera* camera);

	//�}�b�v�Ƃ̓����蔻��
	bool	CheckHit(Box3D& object);



public:

	Texture2::Image	image;	//�摜
	Text::Font		font;	//�t�H���g

	VertexBuf::Billboard	bill;	//���_�o�b�t�@
	Mat4X4::Matrix			matW;	//�}�g���b�N�X


	//�}�b�v�ɂ���I�u�W�F�N�g
	Model	ground;	//�}�b�v
	Model	block;	//�{�b�N�X
	Model	tree;	//�؂̃I�u�W�F�N�g
	Model	house;	//�Ƃ̃I�u�W�F�N�g
	Model	stone;	//�΂̃I�u�W�F�N�g
	StreetLight		stLight;//�X���I�u�W�F�N�g


	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);

public:

	//���f���̓����蔻��
	Box3D					blockHitBox;	//��̓����蔻��{�b�N�X
	Box3D					treeHitBox;		//�؂̓����蔻��{�b�N�X
	Box3D					groundHitBox;	//�n�ʂ̓����蔻��{�b�N�X
	Box3D					houseHitBox;	//�Ƃ̓����蔻��{�b�N�X
	Box3D					stoneHitBox;	//�΂̓����蔻��{�b�N�X
	Box3D					stLightHitBox;	//�X���I�u�W�F�N�g�����蔻��{�b�N�X

	//���f���̓����蔻��͈�
	PolyBox					polyBox;		

public:
	//�}�b�v�̏��
	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	D3DXVECTOR3		size;

	D3DXMATRIX		Inv;	//�t�s��p�}�g���b�N�X
};