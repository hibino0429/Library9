#pragma once
#include "../Function.h"
#include "../Collision/Box.h"



//-----------------------------------------------------------------------
//�|���S���{�b�N�X�̃N���X
//-----------------------------------------------------------------------
class PolyBox
{
public:
	PolyBox();
	~PolyBox();

	//�|���S���{�b�N�X�̏�����
	bool	CreateHitBox(Box3D& hitbox);
	//�|���S���{�b�N�X�̕`��
	void	DrawHitBox();

	//�}�g���b�N�X����
	void	WorldMat(Box3D hitbox);
	

private:

	//���_�o�b�t�@�̍\����
	struct VertexBox
	{
		D3DXVECTOR3		pos;		//�ʒu
		DWORD			diffuse;	//�F
	};
#define BoxFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE )

	LPDIRECT3DVERTEXBUFFER9		pVB;	//�o�[�e�b�N�X�o�b�t�@

	//���[���h�}�g���b�N�X
	Mat4X4::Matrix	matWorld;




public:
	//�ǉ�
	//���_�o�b�t�@�̍쐬�̒ǉ�����
	struct Box3DVertex
	{
		D3DXVECTOR3		pos;
		DWORD			color;
	};
#define Box3DVertexBuf (D3DFVF_XYZ | D3DFVF_DIFFUSE)

	LPDIRECT3DVERTEXBUFFER9		lpvb;

	void	VertexInit();
	void	VertexRender();
	


	//���S�_�̒��_
	struct Box3DPoint
	{
		D3DXVECTOR3		pos;
		DWORD			color;
	};

	LPDIRECT3DVERTEXBUFFER9		pointVB;

	void	PointInit();
	void	PointRender();
	void	SetMatrix(const D3DXVECTOR3& pos);
};