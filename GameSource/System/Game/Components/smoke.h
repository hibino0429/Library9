#pragma once
#include "../../../Library9/Function.h"

//-----------------------------------------------------------------------------
//��1�̃N���X
//-----------------------------------------------------------------------------
class OneSmoke
{
public:
	OneSmoke();
	~OneSmoke();

	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	Create();

	void	ReceiveViewMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);	//�r���[�}�g���b�N�X���󂯎��
	Mat4X4::Matrix	Inverse;
	Mat4X4::Matrix	world;
	
public:
	void	ReceivePos(D3DXVECTOR3&);
	void	ReceiveAngle(D3DXVECTOR3&);
	void	ReceiveSize(D3DXVECTOR3&);

	void	SetLifeTime(int lifeTime);		//�����Ă��鎞��
	void	SetVelocity(D3DXVECTOR3& vel);			//�����x


	bool	LimitLifeTime();
	void	ActiveFlag(bool flag);
	bool	GetActiveFlag();

private:

	//�r���{�[�h�̃f�[�^
	struct Vertex
	{
		D3DXVECTOR3		pos;		//���_���W
		DWORD			diffuse;	//�f�B�q���[�Y�F
		D3DXVECTOR2		tex;		//�e�N�X�`�����W
	};
	#define SMOKE_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0))

	LPDIRECT3DTEXTURE9	texture;

	LPDIRECT3DVERTEXBUFFER9		m_pVerBuf;


private:

	//����ȊO�̕ϐ�
	D3DXVECTOR3			pos, angle, size;
	int		lifeTimeCnt;
	int		lifeTime;
	bool	active;
	D3DXVECTOR3	velocity;

	//�����_���ϐ�
	int		randPos;		//�ʒu
	int		randAngle;		//�p�x
	int		randSize;		//�傫��
	int		randVel;		//�����x
	int		randLifeTime;	//��������
};

//-----------------------------------------------
//���N���X
//-----------------------------------------------
class Smoke
{
public:
	Smoke();


	//��{����
	void	Initialize();
	void	Finalize();
	void	UpDate();
	void	Render();

	void	Matrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);
	void	SetViewMatrix(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);

	void	Create(int i);
	void	Destroy();

private:
	//�萔
	const	int		maxSmokeCnt = 30;
private:
	Mat4X4::Matrix	world;

	OneSmoke		oneSmoke[30];
private:

	D3DXVECTOR3			pos, angle, size;

	int		smokeCnt;		//�����o���鐔
};