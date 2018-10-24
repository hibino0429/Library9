#pragma once
#include "../Function.h"


//-----------------------------------------------------------------------------------------
//2D�{�b�N�X
//-----------------------------------------------------------------------------------------
class Box2D
{
public:
	Box2D();							//�R���X�g���N�^
	Box2D(float,float,float,float);		//�����t���R���X�g���N�^

	//�����蔻��
	bool	Hit(Box2D);	
	Box2D	OffSetCopy(D3DXVECTOR2& pos);		//�I�t�Z�b�g�̃R�s�[
	void	OffSet(D3DXVECTOR2& pos);			//�I�t�Z�b�g

public:
	float x, y;
	float sizeX, sizeY;
};



//----------------------------------------------------------------------------------------
//float�^�̃{�b�N�X���쐬
//3D�{�b�N�X
//----------------------------------------------------------------------------------------
class Box3D
{
public:
	Box3D();
	Box3D(float, float, float, float, float, float);
	~Box3D();

	//�����蔻��
	bool	Hit(Box3D&);
	bool	HitCheck(Box3D&);

	//�I�t�Z�b�g
	void	Offset(const D3DXVECTOR3&);
	Box3D	OffsetCopy(const D3DXVECTOR3&);


public:
	float	x, y, z;
	float	sizeX, sizeY, sizeZ;
	D3DXVECTOR3	minB;
	D3DXVECTOR3	maxB;


};




//----------------------------------------------------------
//����
//----------------------------------------------------------
class Sphere
{
public:
	Sphere();
	Sphere(D3DXVECTOR3& pos, float r);

	//���������߂�
	float	ObjDirection(Sphere&);	//�I�u�W�F�N�g�Ԃ̋���2��
	float	rDirection(Sphere&);	//���a�̋�����2��

	//�����蔻��
	bool	Hit(Sphere&);

public:
	D3DXVECTOR3		pos;	//�ʒu
	float			r;		//���a
};


//----------------------------------------------------
//���C�N���X
//----------------------------------------------------
class Ray
{
public:
	Ray();
	Ray(D3DXVECTOR2& start, D3DXVECTOR2& vec);

	//���菈��
	bool			ZeroVector();		//�x�N�g����0���ǂ����𒲂ׂ�

										//�擾����
	D3DXVECTOR2		GetStartPos();		//�n�_�̎擾����
	D3DXVECTOR2		GetDirVector();		//�����x�N�g���̎擾����

										//�������g�̏���
	void			Normalize();		//���K��
	float			Dot(const D3DXVECTOR2& pos, const D3DXVECTOR2& vec);	//����
	float			Length(const D3DXVECTOR2& pos);			//�傫��

private:
	D3DXVECTOR2		startPos;		//�n�_
	D3DXVECTOR2		dirVector;		//�����x�N�g��

};



//---------------------------------------------------
//�~�N���X
//---------------------------------------------------
class Circle
{
public:
	Circle();
	Circle(D3DXVECTOR2& pos, float rad);

	//�~�ƃ��C�Ƃ̏Փ˔���
	bool	HitRay(Ray* ray);

private:
	D3DXVECTOR2		center;	//���S�_
	float			radius;	//���a

	D3DXVECTOR2		nearColPos;		//�߂��Փˍ��W
	D3DXVECTOR2		farColPos;		//�����Փˍ��W
};



