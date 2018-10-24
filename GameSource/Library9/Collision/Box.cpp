#include "Box.h"

//------------------------------------------------------------------
//二次元のボックス
//------------------------------------------------------------------

//デフォルトコンストラクタ
Box2D::Box2D()
{
	this->x = this->y = 0.0f;
	this->sizeX = this->sizeY = 0.0f;
}

//引数付きコンストラクタ
Box2D::Box2D(float x,float y,float sizeX,float sizeY)
{
	this->x = x;	this->y = y;
	this->sizeX = sizeX;	this->sizeY = sizeY;
}


//当たり判定
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

//位置のオフセット
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
//3Dボックスの作成
//--------------------------------------------------------------------

Box3D::Box3D()
{
	this->x = this->y = this->z = 0.0f;
	this->sizeX = this->sizeY = this->sizeZ = 0.0f;
}

//ボックスの作成
Box3D::Box3D(float x, float y, float z, float sizeX, float sizeY, float sizeZ)
{
	this->x = x;	this->y = y;	this->z = z;
	this->sizeX = sizeX;	this->sizeY = sizeY;	this->sizeZ = sizeZ;
}

//デストラクタ
Box3D::~Box3D()
{
	
}


//当たり判定
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




//当たり判定
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


	//当たり判定
	if (me.fy < you.by && you.fy < me.by) {
		if (me.fx < you.bx && you.fx < me.bx) {
			if (me.fz < you.bz && you.fz < me.bz) {
				//MessageBox(NULL, TEXT("衝突オッケー"), TEXT("大成功"),MB_OK);
				return true;
			}
		}
	}
	return false;
}


//オフセット
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
//球体
//------------------------------------------------------------

//初期設定
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


//オブジェクト間の距離の2乗を求める
//距離を求める
float	Sphere::ObjDirection(Sphere& sp)
{
	D3DXVECTOR3 tmp;
	tmp.x = sp.pos.x - this->pos.x;
	tmp.y = sp.pos.y - this->pos.y;
	tmp.z = sp.pos.z - this->pos.z;

	//距離の2乗
	return tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z;
	//return tmp.x + tmp.y + tmp.z;
}

//半径の距離の2乗を返す
float	Sphere::rDirection(Sphere& sp)
{
	float tmp;
	tmp = sp.r - this->r;

	return tmp * tmp;
}


//当たり判定
bool	Sphere::Hit(Sphere& sp)
{
	float dir = ObjDirection(sp);	//オブジェクト間の距離
	float rDir = rDirection(sp);	//半径の距離

	//オブジェクト間の距離が半径の距離よりも小さいなら、当たっている
	if (dir <= rDir)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------
//レイ
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

//ベクトルが0かどうかを判定
bool	Ray::ZeroVector()
{
	if (dirVector.x == 0.0f && dirVector.y == 0.0f) { return true; }
	return false;
}

//始点の取得処理
D3DXVECTOR2	Ray::GetStartPos()
{
	return startPos;
}
//方向ベクトルの取得処理
D3DXVECTOR2	Ray::GetDirVector()
{
	return dirVector;
}

//正規化
void		Ray::Normalize()
{
	float length = sqrtf(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	dirVector.x /= length;
	dirVector.y /= length;
}

//内積
float		Ray::Dot(const D3DXVECTOR2& pos,const  D3DXVECTOR2& vec)
{
	return pos.x * vec.x + pos.y * vec.y;
}
//長さ
float		Ray::Length(const D3DXVECTOR2& pos)
{
	return pos.x * pos.x + pos.y * pos.y;
}




//-----------------------------------------------------
//円
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


//レイとの衝突判定
bool	Circle::HitRay(Ray* ray)
{
	if (radius < 0.0f) { return false; }		//半径がマイナスならエラー
	if (ray->ZeroVector()) { return false; }	//ヘクトルが0なら、エラー

	//円の中心点が原点になるように始点をオフセット
	center -= ray->GetStartPos();

	//レイの方向ベクトルを正規化
	ray->Normalize();

	//係数tの算出
	float dotAV = ray->Dot(ray->GetStartPos(), ray->GetDirVector());
	float dotAA = ray->Length(ray->GetStartPos());
	float s = dotAV * dotAV - dotAA + radius * radius;
	if (fabs(s) < 0.000001f) { s = 0.0f; }		//誤差修正

	if (s < 0.0f) { return false; }		//衝突していない

	float sq = sqrtf(s);
	float t1 = -dotAV - sq;
	float t2 = -dotAV + sq;

	//もしt1およびt2がマイナスなら
	//始点が円内にめり込んでいるのでエラー
	if (t1 < 0.0f || t2 < 0.0f) { return false; }

	//衝突座標の出力
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