#include "Box.h"

//------------------------------------------------------------------
//�񎟌��̃{�b�N�X
//------------------------------------------------------------------

//�f�t�H���g�R���X�g���N�^
Box2D::Box2D()
{
	this->x = this->y = 0.0f;
	this->sizeX = this->sizeY = 0.0f;
}

//�����t���R���X�g���N�^
Box2D::Box2D(float x,float y,float sizeX,float sizeY)
{
	this->x = x;	this->y = y;
	this->sizeX = sizeX;	this->sizeY = sizeY;
}


//�����蔻��
bool Box2D::Hit(Box2D box)
{
	if (box.x <= this->x && this->x < box.x + box.sizeX)
	{
		if (box.y <= this->y && this->y < box.y + box.sizeY)
		{
			return true;
		}
	}
	return false;
}

//�ʒu�̃I�t�Z�b�g
Box2D	Box2D::OffSetCopy(D3DXVECTOR2& pos)
{
	Box2D	temp;
	temp.x = pos.x;
	temp.y = pos.y;
	temp.sizeX = pos.x + sizeX;
	temp.sizeY = pos.y + sizeY;
	
	return temp;
}

void	Box2D::OffSet(D3DXVECTOR2& pos)
{
	this->x = pos.x;
	this->y = pos.y;
}




//--------------------------------------------------------------------
//3D�{�b�N�X�̍쐬
//--------------------------------------------------------------------

Box3D::Box3D()
{
	this->x = this->y = this->z = 0.0f;
	this->sizeX = this->sizeY = this->sizeZ = 0.0f;
}

//�{�b�N�X�̍쐬
Box3D::Box3D(float x, float y, float z, float sizeX, float sizeY, float sizeZ)
{
	this->x = x;	this->y = y;	this->z = z;
	this->sizeX = sizeX;	this->sizeY = sizeY;	this->sizeZ = sizeZ;
}

//�f�X�g���N�^
Box3D::~Box3D()
{
	
}


//�����蔻��
bool Box3D::Hit(Box3D&	box)
{
	struct Box3DRect
	{
		float	fx, fy, fz;
		float	bx, by, bz;
	};

	Box3DRect	me = {
		x			,y			,z,
		x + sizeX	,y + sizeY	,z + sizeZ
	};

	Box3DRect	you = {
		box.x				,box.y				,box.z,
		box.x + box.sizeX	,box.y + box.sizeY	,box.z + box.sizeZ
	};

	/*if (me.fy < you.by && you.fy < me.by) {
		if (me.fx < you.bx && you.fx < me.bx) {
			if (me.fz < you.bz && you.fz < me.bz) {
				return true;
			}
		}
	}*/

	if (x <= box.x + box.sizeX && box.x <= x + sizeX) {
		if (y <= box.y + box.sizeY && box.y <= y + sizeY) {
			if (z <= box.z + box.sizeZ && box.z <= z + sizeZ) {
				return true;
			}
		}
	}

	return false;
}




//�����蔻��
bool	Box3D::HitCheck(Box3D& box)
{
	struct Box3DRect
	{
		float	fx, fy, fz;
		float	bx, by, bz;
	};

	Box3DRect	me = {
		x			,y			,z,
		x + sizeX	,y + sizeY	,z + sizeZ
	};

	Box3DRect	you = {
		box.x				,box.y				,box.z,
		box.x + box.sizeX	,box.y + box.sizeY	,box.z + box.sizeZ
	};


	//�����蔻��
	if (me.fy < you.by && you.fy < me.by) {
		if (me.fx < you.bx && you.fx < me.bx) {
			if (me.fz < you.bz && you.fz < me.bz) {
				//MessageBox(NULL, TEXT("�Փ˃I�b�P�["), TEXT("�听��"),MB_OK);
				return true;
			}
		}
	}
	return false;
}


//�I�t�Z�b�g
void	Box3D::Offset(const D3DXVECTOR3& pos)
{
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

Box3D	Box3D::OffsetCopy(const D3DXVECTOR3& pos)
{
	Box3D	tmp;
	tmp.x = pos.x;
	tmp.y = pos.y;
	tmp.z = pos.z;
	tmp.sizeX = this->sizeX;
	tmp.sizeY = this->sizeY;
	tmp.sizeZ = this->sizeZ;
	return tmp;
}






//------------------------------------------------------------
//����
//------------------------------------------------------------

//�����ݒ�
Sphere::Sphere()
{
	this->pos = D3DXVECTOR3(0, 0, 0);
	this->r = 1;
}
Sphere::Sphere(D3DXVECTOR3& pos, float r)
{
	this->pos = pos;
	this->r = r;
}


//�I�u�W�F�N�g�Ԃ̋�����2������߂�
//���������߂�
float	Sphere::ObjDirection(Sphere& sp)
{
	D3DXVECTOR3 tmp;
	tmp.x = sp.pos.x - this->pos.x;
	tmp.y = sp.pos.y - this->pos.y;
	tmp.z = sp.pos.z - this->pos.z;

	//������2��
	return tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z;
	//return tmp.x + tmp.y + tmp.z;
}

//���a�̋�����2���Ԃ�
float	Sphere::rDirection(Sphere& sp)
{
	float tmp;
	tmp = sp.r - this->r;

	return tmp * tmp;
}


//�����蔻��
bool	Sphere::Hit(Sphere& sp)
{
	float dir = ObjDirection(sp);	//�I�u�W�F�N�g�Ԃ̋���
	float rDir = rDirection(sp);	//���a�̋���

	//�I�u�W�F�N�g�Ԃ̋��������a�̋��������������Ȃ�A�������Ă���
	if (dir <= rDir)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------
//���C
//-----------------------------------------------------
Ray::Ray()
{
	startPos = D3DXVECTOR2(0, 0);
	dirVector = D3DXVECTOR2(1, 1);
}

Ray::Ray(D3DXVECTOR2& start, D3DXVECTOR2& vec)
{
	startPos = start;
	dirVector = vec;
}

//�x�N�g����0���ǂ����𔻒�
bool	Ray::ZeroVector()
{
	if (dirVector.x == 0.0f && dirVector.y == 0.0f) { return true; }
	return false;
}

//�n�_�̎擾����
D3DXVECTOR2	Ray::GetStartPos()
{
	return startPos;
}
//�����x�N�g���̎擾����
D3DXVECTOR2	Ray::GetDirVector()
{
	return dirVector;
}

//���K��
void		Ray::Normalize()
{
	float length = sqrtf(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	dirVector.x /= length;
	dirVector.y /= length;
}

//����
float		Ray::Dot(const D3DXVECTOR2& pos,const  D3DXVECTOR2& vec)
{
	return pos.x * vec.x + pos.y * vec.y;
}
//����
float		Ray::Length(const D3DXVECTOR2& pos)
{
	return pos.x * pos.x + pos.y * pos.y;
}




//-----------------------------------------------------
//�~
//-----------------------------------------------------
Circle::Circle()
{
	center = D3DXVECTOR2(0, 0);
	radius = 1.0f;
}

Circle::Circle(D3DXVECTOR2& pos, float rad)
{
	center = pos;
	radius = rad;
}


//���C�Ƃ̏Փ˔���
bool	Circle::HitRay(Ray* ray)
{
	if (radius < 0.0f) { return false; }		//���a���}�C�i�X�Ȃ�G���[
	if (ray->ZeroVector()) { return false; }	//�w�N�g����0�Ȃ�A�G���[

	//�~�̒��S�_�����_�ɂȂ�悤�Ɏn�_���I�t�Z�b�g
	center -= ray->GetStartPos();

	//���C�̕����x�N�g���𐳋K��
	ray->Normalize();

	//�W��t�̎Z�o
	float dotAV = ray->Dot(ray->GetStartPos(), ray->GetDirVector());
	float dotAA = ray->Length(ray->GetStartPos());
	float s = dotAV * dotAV - dotAA + radius * radius;
	if (fabs(s) < 0.000001f) { s = 0.0f; }		//�덷�C��

	if (s < 0.0f) { return false; }		//�Փ˂��Ă��Ȃ�

	float sq = sqrtf(s);
	float t1 = -dotAV - sq;
	float t2 = -dotAV + sq;

	//����t1�����t2���}�C�i�X�Ȃ�
	//�n�_���~���ɂ߂荞��ł���̂ŃG���[
	if (t1 < 0.0f || t2 < 0.0f) { return false; }

	//�Փˍ��W�̏o��
	if (nearColPos.x != 0.0f && nearColPos.y != 0.0f)
	{
		nearColPos.x = ray->GetStartPos().x + t1 * ray->GetDirVector().x + center.x;
		nearColPos.y = ray->GetStartPos().y + t1 * ray->GetDirVector().y + center.y;
	}
	if (farColPos.x != 0.0f && farColPos.y != 0.0f)
	{
		farColPos.x = ray->GetStartPos().x + t2 * ray->GetDirVector().x + center.x;
		farColPos.y = ray->GetStartPos().y + t2 * ray->GetDirVector().y + center.y;
	}
	return true;
}