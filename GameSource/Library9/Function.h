#pragma once
#include "DGD.h"
#include "../Library9/Collision/Box.h"

#define DELETE_SAFE_ARRAY(me) {if(me){delete[] (me); (me) = NULL;}}
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = NULL;} }
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] (p); (p) = NULL;} }
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = NULL;} }

//----------------------------------------------------------------
//�@�\�Q
//----------------------------------------------------------------
class Box2D;


//----------------------------------------------------------------------------
//�摜
//----------------------------------------------------------------------------
namespace Texture2
{
	class Image
	{
	public:

		Image();
		~Image();

		//�񋟂��郁�\�b�h

		//�ǂݍ��ݏ���
		//����1:�摜�̃t�@�C���p�X
		void	LoadTexture(LPCWSTR);
		void	LoadTexture(LPCSTR);
		//�摜�̔j��
		void	Destroy();
		

		//����1:�摜�̈ʒu�E�傫��
		//����2:�\�[�X�̉摜�̈ʒu�E�傫��
		//����3:�摜�̐F
		void	Render(Box2D, Box2D, D3DXCOLOR = D3DXCOLOR(1,1,1,1));


	private:

		void	SetCenter(D3DXVECTOR3);		
		void	SetPosition(D3DXVECTOR3);
		void	SetRect(Box2D);
		void	SetColor(D3DXCOLOR);		


		//�X�v���C�g����
		void	CreateSprite();					//�X�v���C�g�̍쐬

		//�T�[�t�F�C�X����
		void	CreateSurface(UINT, UINT);		//�T�[�t�F�C�X�̍쐬
		void	RenderSurface(IDirect3DSurface9*, const RECT*, IDirect3DSurface9*, const POINT*);		//�T�[�t�F�C�X�̕`��
		bool	GetSurfaceLevel(UINT);			//�e�N�X�`������T�[�t�F�C�����擾

		//�o�b�N�o�b�t�@�E�X�e���V���o�b�t�@����
		void	GetRenderTarget(UINT);				//�o�b�N�o�b�t�@�̃T�[�t�F�C�X�̎擾
		void	GetDepthStencilSurface();			//�X�e���V���o�b�t�@�̎擾
		void	CreateStencilSurface(UINT, UINT);	//�X�e���V���o�b�t�@�̐���


		bool	GetImageInfo(LPCWSTR fileName);		//�摜�t�@�C���̃T�C�Y���t�H�[�}�b�g���擾
		bool	GetImageInfo(LPCTSTR fileName);
		bool	CreatePlainSurface();				//�摜�̃T�[�t�F�C�X���쐬
		
		//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
		bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
		bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCTSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
		bool	LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect);
		bool	LoadSurface(LPCTSTR fileName, const RECT* drawRect, const RECT* srcRect);

		void	Rotation(float angle);
		void	Scale(D3DXVECTOR2 scale);
	
	private:

		LPD3DXSPRITE		m_pSprite;			//�X�v���C�g�̊i�[
		LPDIRECT3DTEXTURE9	m_pTexture;			//�e�N�X�`���̊i�[


		LPDIRECT3DSURFACE9	backBufSurface;		//�����_�����O�ɃZ�b�g����Ă����T�[�t�F�C�X
		LPDIRECT3DSURFACE9	backDepthSurface;	//�[�x�o�b�t�@�T�[�t�F�C�X


		LPDIRECT3DSURFACE9	surface;			//�摜�T�[�t�F�C�X
		D3DXIMAGE_INFO		imageInfo;			//�摜�̏��


	private:

		//�ꎞ�i�[
		D3DXVECTOR3			center;
		D3DXVECTOR3			position;
		D3DXCOLOR			color;
		RECT				rect;

		D3DXMATRIX			world;
	};
}


//-------------------------------------------------------------------------------
//�t�H���g
//-------------------------------------------------------------------------------
namespace Text
{
	class Font
	{
	public:

		Font();
		~Font();

	public:
		//�t�H���g�̐���
		//����1:�t�H���g��
		//����2:��
		//����3:����
		bool	Create(LPCWSTR,float,float);
		bool	Create(LPCSTR, float, float);
		//�t�H���g�̉��
		void	Destory();

		//�t�H���g�̕`��
		//����1:������
		//����2:�\���͈�
		//����3:�F
		void	Render(LPCWSTR,Box2D,D3DXCOLOR = D3DXCOLOR(1,1,1,1));
		void	Render(LPCSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1,1,1,1));
	private:
		LPD3DXFONT		pFont;	//�t�H���g�I�u�W�F�N�g
	};
}


//--------------------------------------------------------------------------------
//X�t�@�C��(���f��)
//--------------------------------------------------------------------------------
namespace XFile
{
	class ModelX
	{
	public:
		ModelX();
		~ModelX();

		//�֐�����

		//����1:���f���̃t�@�C���p�X
		bool		Load(LPCWSTR);		//���f���̓ǂݍ���
		bool		Load(LPCSTR);		
		void		Erase();			//���f���̉��
		void		Render();			//���f���̕`��

		bool		BoundingBox();		//���f���̂����蔻��



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
		D3DXVECTOR3			minB;
		D3DXVECTOR3			maxB;

		static int modelNum;

	};
}

//////////////////////////////////////////////////////////////////////////

//�t�H���g�̏���
namespace LibFont
{
	bool	Create(LPCWSTR, float, float,LPD3DXFONT*);
	bool	Create(LPCSTR, float, float,LPD3DXFONT*);
}

//�e�N�X�`���̏���
namespace LibTexture
{
	//�摜�̐�������
	void	Create(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex);
	void	Create(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex);

	//�X�v���C�g�̍쐬
	void	CreateSprite(LPD3DXSPRITE* sprite);

	//�摜�̃T�[�t�F�C�X�̎擾
	bool	CreatePlainSurface(D3DXIMAGE_INFO* imageInfo,LPDIRECT3DSURFACE9* surface);

	//�T�[�t�F�C�X�̕`��
	void	RenderSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint);

	//�T�[�t�F�C�X�̍쐬
	void	CreateSurface(UINT width, UINT height, LPDIRECT3DSURFACE9* backBufSurface);

	//�e�N�X�`������T�[�t�F�C�X���擾
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex, LPDIRECT3DSURFACE9* surface);
}

//XModel��p�̊֐��Q
namespace LibModel
{
	//���f���̃��[�h����
	void	Load(LPCWSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh);
	void	Load(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh);

	void	SetMaterial(D3DMATERIAL9* material);

}

//Shader�̏���
namespace LibShader
{
	bool	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	bool	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
}

//Matrix�̏���
namespace LibMatrix
{
	void	SetMatrix(D3DTRANSFORMSTATETYPE type, D3DXMATRIX* mat);
}


//----------------------------------------------------------------------------------
//���_�o�b�t�@
//XXX:�@�\���P�̕K�v������
//----------------------------------------------------------------------------------
namespace VertexBuf
{
	//�r���{�[�h
	class Billboard
	{
	public:

		Billboard();
		~Billboard();

		//�r���{�[�h�̐���
		bool	Create();

		//���_�o�b�t�@�̒��g�𖄂߂�
		void	SetVertex();

		//���_1�̐ݒ�
		//void	SetVertex(int number, D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXCOLOR color);

		//�r���{�[�h�̔j��
		void	Destroy();

		//�r���{�[�h�̕`��
		void	Render();
		

		//�e�N�X�`���摜�̓ǂݍ���
		bool	LoadVertexTex(LPCWSTR);

		bool	LoadVertexTexA(LPCSTR);

		void	SetMatrix();			//�}�g���b�N�X�̃Z�b�g
		//void	ReceiveViewMatrix(D3DXVECTOR3&,D3DXVECTOR3&,D3DXVECTOR3&);	//�r���[�}�g���b�N�X���󂯎��

	#define VertexFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	private:

		struct Vertex
		{
			D3DXVECTOR3		pos;
			DWORD			diffuse;
			D3DXVECTOR2		tex;
		};

		LPDIRECT3DVERTEXBUFFER9	m_pVB;		//���_�o�b�t�@

	public:
		LPDIRECT3DTEXTURE9		m_pTexture;	//�e�N�X�`���̏��


		D3DXVECTOR3		pos;
		D3DXVECTOR3		angle;
		D3DXVECTOR3		size;
	};
}


//--------------------------------------------------------------------------
//�}�g���b�N�X�@�\
//--------------------------------------------------------------------------
namespace Mat4X4
{
	class Matrix
	{
	public:

		Matrix();
		
		//�}�g���b�N�X���Z�b�g����
		//����1:�ϊ�����s��
		void	SetMatrix(D3DTRANSFORMSTATETYPE type);

	public:
		D3DXMATRIX	mat;
	};
}


//---------------------------------------------------------
//�V�F�[�_�N���X
//---------------------------------------------------------
namespace Effect
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void	Load(LPCWSTR fileName);	//�V�F�[�_�t�@�C���̓ǂݍ���
		void	Load(LPCSTR fileName);	//�V�F�[�_�t�@�C���̓ǂݍ���
		void	DeviceLost();			//�V�F�[�_�f�o�C�X��������
		void	DeviceReset();			//�V�F�[�_�f�o�C�X�̕���
		void	Set();					//�V�F�[�_�̐ݒ�
		void	Render();				//�V�F�[�_�̕`��


		//�e�N�j�b�N�̐ݒ�
		void	SetTechnique(const char* techniqueName);		//�e�N�j�b�N���̐ݒ�
		void	SetProjectViewMatrixName(const char* mWVPName);	//�ˉe�ϊ��s�񖼂̐ݒ�
		void	SetWorldMatrixName(const char* mWITName);		//���[���h�ϊ��s�񖼂̐ݒ�
		void	SetLightDirName(const char* vLightDirName);		//���C�g�̕������̐ݒ�
		void	SetColorName(const char* colorName);			//�F���̐ݒ�

		//���W�E�}�g���b�N�X�̐ݒ�
		void	SetMatrix(D3DXMATRIX* mat);
		void	SetVector(D3DXVECTOR4* vec);
		//���W�E�}�g���b�N�X�̐ݒ�(�n���h���t��)
		void	SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat);
		void	SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec);

		//�V�F�[�_�̃p�����[�^�ݒ�
		D3DXHANDLE	GetParamTechnique(const char* technique);	//�e�N�j�b�N�̐ݒ�
		D3DXHANDLE	GetParameterName(const char* shaderName);	//�V�F�[�_�̕ϐ��̐ݒ�
		bool		SetParamTexture(const char* texName,LPDIRECT3DTEXTURE9 tex);		//�e�N�X�`���̐ݒ�

		//�`��p�X�̊J�n
		void	BeginPass(UINT pass);
		void	EndPass();
		void	Begin(UINT* pass,DWORD flags);
		void	End();
	private:


	public:
		LPD3DXEFFECT	m_pEffect;		//�V�F�[�_�̃f�o�C�X
		LPD3DXBUFFER	m_pErr;			//�o�b�t�@

		//�n���h���͂�͂�A�ʂɎ�������
		D3DXHANDLE		m_hTechnique;	//�e�N�j�b�N
		D3DXHANDLE		m_hmWVP;		//���[�J�� - �ˉe�ϊ��s��
		D3DXHANDLE		m_hmWIT;		//���[�J�� - ���[���h�ϊ��s��
		D3DXHANDLE		m_hvLightDir;	//���C�g�̕���
		D3DXHANDLE		m_hvCol;		//���_�F
	};
}



//-------------------------------------------------------------------
//�I�u�W�F�N�g�ȂǁA���ʂ��Ďg�p����@�\
//-------------------------------------------------------------------
namespace LibDGD
{
	//�����_�����O�p�C�v���C���ɃZ�b�g
	void	SetRenderState(D3DRENDERSTATETYPE, DWORD);

	//�e�N�X�`���X�e�[�W�Z�b�g
	void	SetTexStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value);

	//�e�N�X�`���̃��b�s���O���[�h
	void	SetTexSamplerState(DWORD stage, D3DSAMPLERSTATETYPE type, DWORD value);

	//�X�g���[���\�[�X�̃Z�b�g
	void	SetStreamSource(UINT, LPDIRECT3DVERTEXBUFFER9, UINT, UINT);

	//FVF�̐ݒ�
	void	SetFVF(DWORD fvf);

	//�O�p�`�̕`��
	void	DrawPrimitive(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum);

	//���_�o�b�t�@�̐ݒ�
	bool	CreateVertexBuffer(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf);
	//���_�̃f�R���[�V�����̍쐬
	void	CreateVertexDeclaration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl);

	//�e�N�X�`���摜�̓ǂݍ���(VertexBuf�p)
	bool	CreateTexVertexBuf(LPCTSTR fileName,LPDIRECT3DTEXTURE9* pTex);
	//�e�N�X�`���摜�̓ǂݍ���
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);
	bool	CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture);

	//�e�N�X�`�����p�C�v���C���ɃZ�b�g
	void	SetTexture(DWORD number, LPDIRECT3DTEXTURE9);

	//�r���[�ƃX�e���V���̃N���A
	bool	ViewAndStencilClear();

	//�o�b�N�V�[���̃N���A
	void	SceneClear();

	//Z�o�b�t�@�̃N���A
	void	ZBufClear();

	//�r���[�|�[�g�̐ݒ�
	bool	SetViewPort(D3DVIEWPORT9*);

	//���C�g�֌W�̏���
	void	SetLight(int num, D3DLIGHT9* pLight);	//���C�g�̃Z�b�g
	void	SetUseLight(int num, bool useFlag);		//���C�g���g�p���邩

	bool	BeginRender();	//�`��̊J�n
	void	EndRender();	//�`��̏I��
	void	PresentRender();//�`��̔��f

	//�V���h�E�}�b�v�֌W
	void	CreateTexture(UINT width,UINT height,LPDIRECT3DTEXTURE9* tex);
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex,LPDIRECT3DSURFACE9* surface);
	void	CreateDepthStencilSurface(UINT widht,UINT height,LPDIRECT3DSURFACE9* surface);
	void	CreateDepthStencilSurface(UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality, LPDIRECT3DSURFACE9* surf);

	void	GetRenderTarget(DWORD, LPDIRECT3DSURFACE9* surface);
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface);

	void	SetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface);
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface);

	void	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader);
	void	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader);

	//�V�F�[�_�֘A�̏���
	void	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	void	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr);
	void	CreateVertexShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHander);
	void	CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler);

	//���̒ǉ�����
	void	SetVertexBuf(UINT num, IDirect3DVertexBuffer9* verBuf, UINT size, UINT zero);
	void	VertexRender(D3DPRIMITIVETYPE type, UINT start, UINT num);
}



//----------------------------------------------------------------------------------
//�f�o�C�X���ʂ̏���
//----------------------------------------------------------------------------------
namespace LibDEV
{
	HRESULT InitDevice(HWND, BOOL, int, int);		//Direct3D�̏�����
	void	FinalDevice();							//Direct3D�̉��

	LPDIRECT3DDEVICE9* GetDevice();					//�f�o�C�X��n��
}