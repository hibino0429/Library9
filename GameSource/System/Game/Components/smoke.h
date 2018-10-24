#pragma once
#include "../../../Library9/Function.h"

//-----------------------------------------------------------------------------
//煙1つのクラス
//-----------------------------------------------------------------------------
class OneSmoke
{
public:
	OneSmoke();
	~OneSmoke();

	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	Create();

	void	ReceiveViewMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);	//ビューマトリックスを受け取る
	Mat4X4::Matrix	Inverse;
	Mat4X4::Matrix	world;
	
public:
	void	ReceivePos(D3DXVECTOR3&);
	void	ReceiveAngle(D3DXVECTOR3&);
	void	ReceiveSize(D3DXVECTOR3&);

	void	SetLifeTime(int lifeTime);		//生きている時間
	void	SetVelocity(D3DXVECTOR3& vel);			//初速度


	bool	LimitLifeTime();
	void	ActiveFlag(bool flag);
	bool	GetActiveFlag();

private:

	//ビルボードのデータ
	struct Vertex
	{
		D3DXVECTOR3		pos;		//頂点座標
		DWORD			diffuse;	//ディヒューズ色
		D3DXVECTOR2		tex;		//テクスチャ座標
	};
	#define SMOKE_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0))

	LPDIRECT3DTEXTURE9	texture;

	LPDIRECT3DVERTEXBUFFER9		m_pVerBuf;


private:

	//それ以外の変数
	D3DXVECTOR3			pos, angle, size;
	int		lifeTimeCnt;
	int		lifeTime;
	bool	active;
	D3DXVECTOR3	velocity;

	//ランダム変数
	int		randPos;		//位置
	int		randAngle;		//角度
	int		randSize;		//大きさ
	int		randVel;		//初速度
	int		randLifeTime;	//生存時間
};

//-----------------------------------------------
//煙クラス
//-----------------------------------------------
class Smoke
{
public:
	Smoke();


	//基本処理
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	Matrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);
	void	SetViewMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

	void	Create(int i);
	void	Destroy();

private:
	//定数
	const	int		maxSmokeCnt = 30;
private:
	Mat4X4::Matrix	world;

	OneSmoke		oneSmoke[30];
private:

	D3DXVECTOR3			pos, angle, size;

	int		smokeCnt;		//煙を出せる数
};