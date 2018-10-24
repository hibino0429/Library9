#pragma once

#include "../Function.h"
#include "../../System/ShaderSystem/ZTexture.h"
#include "../../System/ShaderSystem/DepthTex.h"


//----------------------------------------------------
//���f���̃N���X
//----------------------------------------------------
class Model
{
public:
	Model();
	~Model();

	//����1:���f���̃t�@�C���p�X
	void		Load(LPCWSTR);		//���f���̓ǂݍ���
	void		Load(LPCSTR);
	void		Erase();			//���f���̉��
	void		Render();			//���f���̕`��

	void		ZTexRender(ZTexture* zTex);
	void		DepthRender(DepthTexture* depTex);

	//�ݒ菈��
	void		SetPos(const D3DXVECTOR3& pos);
	void		SetAngle(const D3DXVECTOR3& angle);
	void		SetSize(const D3DXVECTOR3& size);

	//�擾����
	D3DXVECTOR3	GetPos();
	D3DXVECTOR3	GetAngle();
	D3DXVECTOR3	GetSize();

private:
	bool		BoundingBox();		//���f���̂����蔻��

	bool		CloneModel();		//���f���̍č쐬

private:
	//X�t�@�C�����
	LPD3DXMESH			m_pMesh;		//���b�V���̃C���^�[�t�F�C�X
	LPD3DXBUFFER		m_pMtrlBuf;		//���b�V���̃}�e���A��
	DWORD				m_MtrlNum;		//�}�e���A���̐�

public:
	LPDIRECT3DTEXTURE9*	m_texture;		//�e�N�X�`�����

public:
	D3DXVECTOR3			pos;
	D3DXVECTOR3			angle;
	D3DXVECTOR3			size;
private:
	D3DXVECTOR3			minB;
	D3DXVECTOR3			maxB;

	LPD3DXMESH			cloneMesh;		//�N���[�����b�V��
public:

};