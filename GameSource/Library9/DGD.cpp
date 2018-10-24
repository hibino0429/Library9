#include "DGD.h"

//------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------
DGD::DGD() : m_pD3D(0),m_pD3DDevice(0)
{
	
}

//------------------------------------------------------
//DGD���̂̐���
//------------------------------------------------------
DGD*	DGD::Instance()
{
	if (instance == 0)
	{
		instance = new DGD;
	}

	return instance;
}


//------------------------------------------------------
//�f�o�C�X�̏�����
//------------------------------------------------------
HRESULT DGD::DeviceInit(HWND hWnd, BOOL isFullScreen, int clientWidth, int clientHeight)
{
	D3DDISPLAYMODE d3ddm;


	// Direct3D9�I�u�W�F�N�g�̍쐬
	if ((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0) {
		return E_FAIL;	// �擾���s
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��������
	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.BackBufferCount = 1;
	if (isFullScreen) { // �t���X�N���[���̏ꍇ
		m_D3DPP.Windowed = FALSE;			// �t���X�N���[���\���̎w��
		m_D3DPP.BackBufferWidth = clientWidth;		// �t���X�N���[�����̉���
		m_D3DPP.BackBufferHeight = clientHeight;		// �t���X�N���[�����̏c��
	}
	else {
		m_D3DPP.Windowed = TRUE;				// �E�C���h�E���\���̎w��
	}
	m_D3DPP.BackBufferFormat = d3ddm.Format;			// �J���[���[�h�̎w��
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 
	m_D3DPP.EnableAutoDepthStencil = TRUE;						// �G���[�΍�
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D16;				// �G���[�΍�
	m_D3DPP.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;			//�o�b�N�o�b�t�@�̑���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_D3DPP, &m_pD3DDevice))) {
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_D3DPP, &m_pD3DDevice))) {
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_D3DPP, &m_pD3DDevice))) {
				// ���������s
				return E_FAIL;
			}
		}
	}


	return S_OK;
}



//------------------------------------------------------
//�f�o�C�X�̉��
//------------------------------------------------------
void	DGD::DeviceFinal()
{
	if (m_pD3DDevice != NULL) {	m_pD3DDevice->Release(); m_pD3DDevice = NULL; }
	if (m_pD3D != NULL) { m_pD3D->Release(); m_pD3D = NULL; }

}


//------------------------------------------------------
//�[�x�o�b�t�@�ƃX�e���V���o�b�t�@�̃N���A
//------------------------------------------------------
bool	DGD::ViewAndStencilClear()
{
	if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 64),
		1.0f,
		0)))
	{
		MessageBox(NULL, TEXT("�[�x�ƃX�e���V���̃N���A���s"), TEXT("ViewAndStencilClear"), MB_OK);
		return false;
	}

	/*if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0)))
	{
		MessageBox(NULL, TEXT("�e�T�[�t�F�C�X�̏������Ɏ��s"), TEXT("Clear"), MB_OK);
		return false;
	}*/
	return true;
}

//Z�o�b�t�@�̃N���A
bool	DGD::ZBufClear()
{
	if (FAILED(m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 64),
		1.0f,
		0)))
	{
		MessageBox(NULL, TEXT("Z�o�b�t�@�̃N���A���s"), TEXT("ZBufClear"), MB_OK);
		return false;
	}
	return true;
}

//------------------------------------------------------
//�`��J�n�錾
//------------------------------------------------------
bool	DGD::BeginRender()
{
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		return true;
	}
	MessageBox(NULL, TEXT("�`�掸�s"), TEXT("BeginScene"), MB_OK);
	return false;
}


//------------------------------------------------------
//�`��I���錾
//------------------------------------------------------
void	DGD::EndRender()
{
	m_pD3DDevice->EndScene();
}


//------------------------------------------------------
//�`�挋�ʂ���ʂɓ]������
//------------------------------------------------------
void	DGD::PresentRender()
{
	if (FAILED(m_pD3DDevice->Present(0, 0, 0, 0)))
	{
		m_pD3DDevice->Reset(&m_D3DPP);
	}
}



//--------------
//���_�o�b�t�@�̍쐬
HRESULT	DGD::CreateVertexBuf(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf)
{
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(
		len,
		D3DUSAGE_WRITEONLY,
		fvf,
		D3DPOOL_MANAGED,
		vertexBuf,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("���_�o�b�t�@�̎��s"), TEXT("���_�������s"), MB_OK);
		return E_FAIL;
	}
	return S_OK;
}




//�`�悷�钸�_�o�b�t�@�̎w��
void	DGD::SetVertexBufRender(UINT streamNum, IDirect3DVertexBuffer9* vertexBuf, UINT offsetBuf, UINT stride)
{
	m_pD3DDevice->SetStreamSource(streamNum, vertexBuf, offsetBuf, stride);
}

//���_�f�[�^��FVF�t�H�[�}�b�g�̐ݒ�
void	DGD::SetVertexFVF(DWORD fvf)
{
	m_pD3DDevice->SetFVF(fvf);
}

//���_�f�[�^��`��
void	DGD::VertexRender(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum)
{
	m_pD3DDevice->DrawPrimitive(renderType, startVertex, primitiveNum);
}


//���_�ɒ���t����e�N�X�`���̃Z�b�g
void	DGD::SetVertexTexture(DWORD stageNum, LPDIRECT3DTEXTURE9 tex)
{
	m_pD3DDevice->SetTexture(stageNum, tex);
}

//���_�f�R���[�V�������쐬
bool	DGD::CreateVertexDecration(const D3DVERTEXELEMENT9* decl,LPDIRECT3DVERTEXDECLARATION9 pDecl)
{
	if (FAILED(m_pD3DDevice->CreateVertexDeclaration(decl,&pDecl)))
	{
		MessageBoxA(NULL, "���_�f�R���[�V�����̍쐬�Ɏ��s���܂���", "CreateVertexDecration", MB_OK);
		return false;
	}
	return true;
}


//--------------
//�����_�����O�X�e�[�g�̐ݒ�

//------------------------------------------------------
//����(�\��)��`�悷�邩
//------------------------------------------------------
void	DGD::CullMode(bool flag)
{
	if (flag)
	{
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}
}

//Z��r���s��
void	DGD::ZEnable(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, flag);
}

//�f�B�U�����O�����邩
void	DGD::DitherEnable(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, flag);
}

//���C�g���e�������邩
void	DGD::LightMode(bool flag)
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, flag);
}


//�e�N�X�`���X�e�[�W�̐ݒ�
void	DGD::SetTextureStageState(DWORD stage,D3DTEXTURESTAGESTATETYPE type,DWORD value)
{
	m_pD3DDevice->SetTextureStageState(stage, type, value);
}

//�e�N�X�`�����b�s���O���[�h�̐ݒ�
void	DGD::SetSamplerState(DWORD stage,D3DSAMPLERSTATETYPE type,DWORD value)
{
	m_pD3DDevice->SetSamplerState(stage, type, value);
}



//------------------------
//�}�g���b�N�X�̐ݒ�

//�}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
void	DGD::SetMatrixToRender(D3DTRANSFORMSTATETYPE matType, D3DXMATRIX* mat)
{
	m_pD3DDevice->SetTransform(matType, mat);
}


//--------------------------
//�r���[�|�[�g�̐ݒ�
bool	DGD::SetViewPort(D3DVIEWPORT9* viewport)
{
	if (FAILED(m_pD3DDevice->GetViewport(viewport)))
	{
		MessageBox(NULL, TEXT("�r���[�|�b�g�̐ݒ�Ɏ��s"), TEXT("SetViewPort"), MB_OK);
		return false;
	}
	return true;
}


//-------------------------
//���C�g�������_�����O�p�C�v���C���փZ�b�g
void	DGD::SetLight(int num, D3DLIGHT9* light)
{
	m_pD3DDevice->SetLight(num, light);
}

//���C�g���g�p���邩
void	DGD::LightEnable(int num, bool use)
{
	m_pD3DDevice->LightEnable(num, use);
}


//�����_�����O�p�C�v���C���ɃZ�b�g
void	DGD::SetRenderState(D3DRENDERSTATETYPE type, DWORD value)
{
	m_pD3DDevice->SetRenderState(type, value);
}


bool	DGD::CretateTexture(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex)
{
	if (FAILED(D3DXCreateTextureFromFileA(
		m_pD3DDevice,
		fileName,
		pTex
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`���̐����Ɏ��s���܂���"), TEXT("CreateTextureA"), MB_OK);
		return false;
	}
	return true;
}

//---------------------------------
//�e�N�X�`���̐���
bool	DGD::CretateTexture(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex)
{
	if (FAILED(D3DXCreateTextureFromFileW(
		m_pD3DDevice,
		fileName,
		pTex
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`���̐����Ɏ��s"), TEXT("CreateTexture"), MB_OK);
		return false;
	}
	return true;
}

//�e�N�X�`���̐���Ex
bool	DGD::CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture)
{
	if (FAILED(D3DXCreateTextureFromFileExW(
		m_pD3DDevice,
		fileName,
		width,
		height,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
		colorKey, pSrcInfo, pPalette,
		texture
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`��Ex�̐����Ɏ��s���܂���"), TEXT("CreateTextureEx"), MB_OK);
		return false;
	}
	return true;
}

bool DGD::CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO * pSrcInfo, PALETTEENTRY * pPalette, LPDIRECT3DTEXTURE9 * texture)
{
	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		fileName,
		width,
		height,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
		colorKey, pSrcInfo, pPalette,
		texture
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`��Ex�̐����Ɏ��s���܂���"), TEXT("CreateTextureEx"), MB_OK);
		return false;
	}
	return true;
}


//---------------------------------
//�X�v���C�g�̐���
bool	DGD::CreateSprite(LPD3DXSPRITE* pSprite)
{
	if (FAILED(D3DXCreateSprite(m_pD3DDevice, pSprite)))
	{
		MessageBox(NULL, TEXT("�X�v���C�g�̐����Ɏ��s"), TEXT("CreateSprite"), MB_OK);
		return false;
	}
	return true;
}

//�T�[�t�F�C�X�̍쐬
bool	DGD::CreateOffScreenPlainSurface(UINT width, UINT height,D3DPOOL pool, IDirect3DSurface9** pSurface, HANDLE* sharedHandle)
{
	if (FAILED(m_pD3DDevice->CreateOffscreenPlainSurface(width, height, m_D3DPP.BackBufferFormat, pool, pSurface, sharedHandle)))
	{
		MessageBox(NULL, TEXT("�T�[�t�F�C�X�̍쐬�Ɏ��s���܂���"), TEXT("CraeteOffScreenPlainSurface"), MB_OK);
		return false;
	}
	return true;
}


//�T�[�t�F�C�X�̕`��
void	DGD::SurfaceRender(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
{
	m_pD3DDevice->UpdateSurface(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
}

//�T�[�t�F�C�X�̃o�b�N�o�b�t�@
void	DGD::GetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->GetRenderTarget(targetIndex, surface)))
	{
		MessageBox(NULL, TEXT("�����_�[�^�[�Q�b�g�̎擾�Ɏ��s���܂���"), TEXT("GetRenderTarget"), MB_OK);
		return;
	}
}

//�T�[�t�F�C�X�̃X�e���V���o�b�t�@
void	DGD::GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->GetDepthStencilSurface(surface)))
	{
		MessageBox(NULL, TEXT("�[�x�o�b�t�@�̂̎擾�Ɏ��s���܂���"), TEXT("GetDepthStencilSurface"), MB_OK);
		return;
	}
}

//�e�N�X�`���̍쐬
bool	DGD::TextureCreate(LPDIRECT3DTEXTURE9* tex,UINT width,UINT height)
{
	if (FAILED(D3DXCreateTexture(
		m_pD3DDevice,
		width,
		height,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A16B16G16R16,			//D3DFMT_A8R8G8B8 , D3DFMT_A16B16G16R16
		D3DPOOL_DEFAULT,
		tex
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`���̍쐬�Ɏ��s���܂���"), TEXT("TextureCreate"), MB_OK);
		return false;
	}
	return true;
}

//�X�e���V���o�b�t�@�̍쐬
bool	DGD::StencilBufCreate(LPDIRECT3DSURFACE9* surface,UINT width,UINT height)
{
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(
		width,
		height,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		surface,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("�X�e���V���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("StencilBufCreate"), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::StencilBufCreate(LPDIRECT3DSURFACE9* surf, UINT width, UINT height, D3DFORMAT format,
	D3DMULTISAMPLE_TYPE type, DWORD quality)
{
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(
		width, height,
		format, type, quality,
		FALSE,
		surf,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("�X�e���V���o�b�t�@�̍쐬�Ɏ��s"), TEXT("StencilBufCreate"), MB_OK);
		return false;
	}
	return true;
}

//�X�e���V���o�b�t�@�̐ݒ�
void	DGD::SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->SetDepthStencilSurface(*surface)))
	{
		MessageBox(NULL, TEXT("�X�e���V���o�b�t�@�̐ݒ�Ɏ��s���܂���"), TEXT("SetDepthStencilSurface"), MB_OK);
		return;
	}
}

//�T�[�t�F�C�X�̃Z�b�g
void	DGD::SetRenderTarget(DWORD num, LPDIRECT3DSURFACE9* surface)
{
	if (FAILED(m_pD3DDevice->SetRenderTarget(num, *surface)))
	{
		MessageBox(NULL, TEXT("�T�[�t�F�C�X�̐ݒ�Ɏ��s���܂���"), TEXT("SetRenderTarget"), MB_OK);
		return;
	}
}



//---------------------------------
//�t�H���g�̐���
bool	DGD::CreateFont2D(
	float height, 
	float width, 
	UINT weight, 
	UINT wipLevels, 
	bool italic, 
	UINT charSet, 
	DWORD outputPrecision, 
	DWORD quority, 
	DWORD pitchAndfamiry, 
	LPCWSTR fontName, 
	LPD3DXFONT* pFont)
{
	if (FAILED(D3DXCreateFontW(
		m_pD3DDevice,
		(UINT)height,
		(UINT)width,
		weight,
		wipLevels,
		italic,
		charSet,
		outputPrecision,
		quority,
		pitchAndfamiry,
		fontName,
		pFont
	)))
	{
		MessageBox(NULL, TEXT("�t�H���g�̐����Ɏ��s"), TEXT("CreateFont"), MB_OK);
		return false;
	}
	return true;
}
//�t�H���g�̐���
bool	DGD::CreateFont2DA(
	float height,
	float width,
	UINT weight,
	UINT wipLevels,
	bool italic,
	UINT charSet,
	DWORD outputPrecision,
	DWORD quority,
	DWORD pitchAndfamiry,
	LPCSTR fontName,
	LPD3DXFONT* pFont)
{
	if (FAILED(D3DXCreateFontA(
		m_pD3DDevice,
		(UINT)height,
		(UINT)width,
		weight,
		wipLevels,
		italic,
		charSet,
		outputPrecision,
		quority,
		pitchAndfamiry,
		fontName,
		pFont
	)))
	{
		MessageBox(NULL, TEXT("�t�H���g�̐����Ɏ��s"), TEXT("CreateFont"), MB_OK);
		return false;
	}
	return true;
}

//---------------------------------
//���f���̃��[�h
bool	DGD::LoadModel(LPCWSTR modelName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
{
	if (FAILED(D3DXLoadMeshFromXW(
		modelName,
		D3DXMESH_SYSTEMMEM,
		m_pD3DDevice,
		NULL,
		mtrlBuf,
		NULL,
		numMtrl,
		mesh)))
	{
		MessageBox(NULL, TEXT("���f���̓ǂݍ��ݎ��s"), TEXT("LoadModel"), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::LoadModel(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
{
	if (FAILED(D3DXLoadMeshFromXA(
		fileName,
		D3DXMESH_SYSTEMMEM,
		m_pD3DDevice,
		NULL,
		mtrlBuf,
		NULL,
		numMtrl,
		mesh)))
	{
		MessageBoxA(NULL, "���f���̓ǂݍ��ݎ��s","LoadModel", MB_OK);
		return false;
	}
	return true;
}


//�}�e���A���̃Z�b�g
void	DGD::SetMaterial(D3DMATERIAL9* mtrl)
{
	m_pD3DDevice->SetMaterial(mtrl);
}




//------------------------------------------
//�V�F�[�_�֘A����
//------------------------------------------
//�G�t�F�N�g�t�@�C���̓ǂݍ���
bool	DGD::LoadEffectFile(LPCWSTR fileName,LPD3DXEFFECT* pEffect,LPD3DXBUFFER pErr)
{
	if (FAILED(D3DXCreateEffectFromFileW(m_pD3DDevice, fileName,
		NULL, NULL, 0, NULL, pEffect, &pErr)))
	{
		MessageBox(NULL, TEXT("�V�F�[�_�t�@�C�����ǂݍ��߂܂���"), TEXT("�V�F�[�_�G���["), MB_OK);
		return false;
	}
	return true;
}
bool	DGD::LoadEffectFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
{
	if (FAILED(D3DXCreateEffectFromFileA(m_pD3DDevice, fileName,
		NULL, NULL, 0, NULL, pEffect, &pErr)))
	{
		MessageBoxA(NULL, "�V�F�[�_�t�@�C�����ǂݍ��߂܂���ł���", "LoadEffectFile", MB_OK);
		return false;
	}
	return true;
}

//���_�V�F�[�_�n���h���̐���
bool	DGD::CreateVertexShader(LPD3DXBUFFER pShader,DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHandler)
{
	if (FAILED(m_pD3DDevice->CreateVertexShader(
		(DWORD*)pShader->GetBufferPointer(),
		shaderHandler
	)))
	{
		MessageBox(NULL, TEXT("���_�V�F�[�_�n���h���̐����Ɏ��s"), TEXT("CreateVertexShader"), MB_OK);
		return false;
	}
	return true;
}
//�s�N�Z���V�F�[�_�n���h���̐���
bool	DGD::CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler)
{
	if (FAILED(m_pD3DDevice->CreatePixelShader(
		(DWORD*)pShader->GetBufferPointer(),
		shaderHandler
	)))
	{
		MessageBox(NULL, TEXT("�s�N�Z���V�F�[�_�̐����Ɏ��s"), TEXT("CreatePixelShader"), MB_OK);
		return false;
	}
	return true;
}

//���_�V�F�[�_�̐ݒ�
bool	DGD::SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader)
{
	if (FAILED(m_pD3DDevice->SetVertexShader(*pShader)))
	{
		MessageBox(NULL, TEXT("���_�V�F�[�_�̐ݒ�Ɏ��s���܂���"), TEXT("SetVertexShader"), MB_OK);
		return false;
	}
	return true;
}
//�s�N�Z���V�F�[�_�̐ݒ�
bool	DGD::SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader)
{
	if (FAILED(m_pD3DDevice->SetPixelShader(*pShader)))
	{
		MessageBox(NULL, TEXT("�s�N�Z���V�F�[�_�̐ݒ�Ɏ��s���܂���"), TEXT("SetPixelShader"), MB_OK);
		return false;
	}
	return true;
}