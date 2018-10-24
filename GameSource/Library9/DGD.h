#pragma once

#include <d3dx9.h>
#include <d3d9.h>

#pragma comment( lib, "d3d9.lib" )
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

//DirectX Graphics Device
class DGD
{

	//�V���O���g���N���X�ɂ���
	//1:DGD�𐶐����郁�\�b�h�̍쐬
	//2:DGD�̏����̍쐬
	//3:protected �̃R���X�g���N�^
	//4:private �̎��ȃN���X�̃|�C���^

public:
	static	DGD*	Instance();	//DGD�������\�b�h
	//����

protected:
	DGD();

private:
	

	static DGD*		instance;


public:

	//�f�o�C�X�̏�����
	HRESULT		DeviceInit(HWND, BOOL, int, int);

	//�f�o�C�X�̉��
	void		DeviceFinal();


public:

	//�f�o�C�X�̋@�\
	////
	bool	ViewAndStencilClear();	//�r���[�|�[�g�Ɛ[�x�o�b�t�@�̃N���A
	bool	ZBufClear();			//Z�o�b�t�@�̃N���A

	bool	BeginRender();
	void	EndRender();
	void	PresentRender();


	////
	//���_�o�b�t�@�̍쐬
	HRESULT	CreateVertexBuf(UINT, DWORD, IDirect3DVertexBuffer9**);
	//���_�o�b�t�@�̕`����s���o�b�t�@���w��
	void	SetVertexBufRender(UINT, IDirect3DVertexBuffer9*, UINT, UINT);
	//���_��FVF�t�H�[�}�b�g�̐ݒ�
	void	SetVertexFVF(DWORD);
	//���_�̕`��
	void	VertexRender(D3DPRIMITIVETYPE, UINT, UINT);
	//���_�ɒ���t����e�N�X�`���̃Z�b�g
	void	SetVertexTexture(DWORD, LPDIRECT3DTEXTURE9);
	//���_�̃f�R���[�V�������쐬
	bool	CreateVertexDecration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl);

	////
	//�����_�����O�X�e�[�g�p�����[�^
	void	CullMode(bool);		//�O�p�`�̔w�ʂ�`�悷�邩
	void	ZEnable(bool);		//Z��r���邩
	void	DitherEnable(bool);	//�f�B�U�����O(���i���`��)���邩
	void	LightMode(bool);	//���C�g���e�������邩

	//�����_�����O�p�C�v���C���ɃZ�b�g
	void	SetRenderState(D3DRENDERSTATETYPE, DWORD);

	//�e�N�X�`���X�e�[�W�̐ݒ�
	void	SetTextureStageState(DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);

	//�e�N�X�`�����b�s���O���[�h
	void	SetSamplerState(DWORD, D3DSAMPLERSTATETYPE, DWORD);


	////
	//�}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	void	SetMatrixToRender(D3DTRANSFORMSTATETYPE, D3DXMATRIX*);

	////
	//�r���[�|�[�g�̐ݒ�
	bool	SetViewPort(D3DVIEWPORT9*);


	////
	//���C�g
	void	SetLight(int num, D3DLIGHT9*);	//���C�g�������_�����O�֒ǉ�
	void	LightEnable(int num, bool use);	//���C�g���g����

	//�摜�̓ǂݍ���
	bool	CretateTexture(LPCWSTR, LPDIRECT3DTEXTURE9*);
	bool	CretateTexture(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex);
	//�摜�̓ǂݍ���Ex
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);
	bool	CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);


	//�X�v���C�g�̐���
	bool	CreateSprite(LPD3DXSPRITE*);

	//��
	//�T�[�t�F�C�X�̍쐬
	bool	CreateOffScreenPlainSurface(UINT, UINT, D3DPOOL, IDirect3DSurface9**, HANDLE*);
	
	//�T�[�t�F�C�X�̕`��
	void	SurfaceRender(IDirect3DSurface9*,const RECT*,IDirect3DSurface9*,const POINT*);

	//��
	//�o�b�N�o�b�t�@�̃T�[�t�F�C�X
	void	GetRenderTarget(DWORD,LPDIRECT3DSURFACE9*);
	//�X�e���V���o�b�t�@�̎擾
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9*);
	//�e�N�X�`���̍쐬
	bool	TextureCreate(LPDIRECT3DTEXTURE9* tex,UINT width,UINT height);
	//�X�e���V���o�b�t�@�̍쐬
	bool	StencilBufCreate(LPDIRECT3DSURFACE9* surface,UINT width,UINT height);
	bool	StencilBufCreate(LPDIRECT3DSURFACE9* surf, UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality);

	//�X�e���V���o�b�t�@�̐ݒ�
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9*);
	//�T�[�t�F�C�X���Z�b�g����
	void	SetRenderTarget(DWORD, LPDIRECT3DSURFACE9*);

	//�t�H���g�̐���
	bool	CreateFont2D(float, float, UINT, UINT, bool, UINT, DWORD, DWORD, DWORD, LPCWSTR, LPD3DXFONT*);
	bool	CreateFont2DA(float, float, UINT, UINT, bool, UINT, DWORD, DWORD, DWORD, LPCSTR, LPD3DXFONT*);

	//���f���̓ǂݍ���
	bool	LoadModel(LPCWSTR, LPD3DXBUFFER*, DWORD*, LPD3DXMESH*);
	bool	LoadModel(LPCSTR, LPD3DXBUFFER*, DWORD*, LPD3DXMESH*);

	//�}�e���A���̃Z�b�g
	void	SetMaterial(D3DMATERIAL9*);


	//--------------------------
	//�V�F�[�_�֘A����
	//--------------------------
	bool	LoadEffectFile(LPCWSTR fileName,LPD3DXEFFECT* pEffect,LPD3DXBUFFER pErr);
	bool	LoadEffectFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	bool	CreateVertexShader(LPD3DXBUFFER pShader,DWORD*,LPDIRECT3DVERTEXSHADER9*);
	bool	CreatePixelShader(LPD3DXBUFFER pShader,DWORD*,LPDIRECT3DPIXELSHADER9*);
	bool	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader);
	bool	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader);
public:

	D3DXMATRIX	world;

private:
	public:
	//�f�o�C�X
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DPRESENT_PARAMETERS	m_D3DPP;

};