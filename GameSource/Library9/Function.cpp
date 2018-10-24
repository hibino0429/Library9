#include "Function.h"

#include <string>
#include <locale.h>
#include <atlstr.h>

DGD*	dgd = DGD::Instance();

//----------------------------------------------------------------
//�摜�̋@�\
//----------------------------------------------------------------
//Texture�́A���܂����삵�Ȃ�
namespace Texture2
{
	Image::Image() : m_pSprite(NULL), m_pTexture(NULL) ,  surface(NULL),backBufSurface(NULL),backDepthSurface(NULL)
	{
		ZeroMemory(&center, sizeof(D3DXVECTOR3));
		ZeroMemory(&position, sizeof(D3DXVECTOR3));
		ZeroMemory(&color, sizeof(D3DXCOLOR));
		ZeroMemory(&rect, sizeof(RECT));
	}

	Image::~Image()
	{
		Destroy();
	}

	//�X�v���C�g�̍쐬
	void	Image::CreateSprite()
	{
		if (FAILED(dgd->CreateSprite(&m_pSprite)))
		{
			MessageBox(NULL, TEXT("�X�v���C�g�̐����Ɏ��s���܂���"), TEXT("CreateSprite"), MB_OK);
			return;
		}
	}


	//�e�N�X�`���̃��[�h
	void	Image::LoadTexture(LPCWSTR fileName)
	{
		if (FAILED(dgd->CretateTexture(fileName, &m_pTexture)))
		{
			MessageBox(NULL, TEXT("�e�N�X�`�����[�h���s"), TEXT("LoadTexture"), MB_OK);
			return;
		}
		//�X�v���C�g�̐���
		CreateSprite();
		//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
		LoadSurface(fileName, NULL, NULL);
	}

	//�e�N�X�`���̃��[�h
	void	Image::LoadTexture(LPCSTR fileName)
	{
		if (FAILED(dgd->CretateTexture(fileName, &m_pTexture)))
		{
			MessageBox(NULL, TEXT("�e�N�X�`�����[�h���s"), TEXT("LoadTexture"), MB_OK);
			return;
		}
		//�X�v���C�g�̐���
		CreateSprite();
		//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
		LoadSurface(fileName, NULL, NULL);
	}

	//�摜�̔j��
	void	Image::Destroy()
	{
		if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }
		if (m_pSprite != NULL) { m_pSprite->Release(); m_pSprite = NULL; }

		if (surface != NULL){ surface->Release(); surface = NULL; }

		if (backBufSurface != NULL) { backBufSurface->Release(); backBufSurface = NULL; }
		if (backDepthSurface != NULL) { backDepthSurface->Release(); backDepthSurface = NULL; }
		//dgd->SetRenderTarget(0, backBufSurface);
		//dgd->SetDepthStencilSurface(backDepthSurface);

		
	}

	//�F�̐ݒ�
	void	Image::SetColor(D3DXCOLOR color)
	{
		this->color = color;
	}

	//���S�ʒu�̐ݒ�
	void	Image::SetCenter(D3DXVECTOR3 center)
	{
		this->center = center;
	}

	//�z�u�ʒu�̐ݒ�
	void	Image::SetPosition(D3DXVECTOR3 pos)
	{
		this->position = pos;
	}

	//�͈͂̐ݒ�
	void	Image::SetRect(Box2D box2D)
	{
		this->rect =
		{
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};
	}




	//�摜�̕`��
	void	Image::Render(Box2D draw, Box2D src, D3DXCOLOR color)
	{
		RECT sr = {
			(LONG)src.x,
			(LONG)src.y,
			(LONG)src.x + (LONG)src.sizeX,
			(LONG)src.y + (LONG)src.sizeY
		};

		D3DXVECTOR3	pos = D3DXVECTOR3(draw.x, draw.y, 0);
		D3DXVECTOR3 center = D3DXVECTOR3(draw.sizeX, draw.sizeY, 0);

		//src�̑傫����draw�̑傫���ɂ��� src/draw �Ŕ{�����擾
		//D3DXVECTOR2	scale;
		//scale.x = (float)src.sizeX / draw.sizeX * 2.0f;
		//scale.y = (float)src.sizeY / draw.sizeY * 2.0f;
		//D3DXVECTOR2	rotCenter(0, 0);
		//D3DXVECTOR2	drawPos(0, 0);

		////�摜�̕\������͈͂��X�P�[���Œ�������
		//D3DXMATRIX	mWorld;
		//D3DXMatrixTransformation2D(&mWorld, nullptr, 0.0f, &scale, &rotCenter, 0.0f, &drawPos);

		
		//�摜�\�[�X�͈̔͂�������Ŏw�肷��
		//
		if (SUCCEEDED(m_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
		{
			if (FAILED(m_pSprite->Draw(
				m_pTexture,
				&sr,
				&center,
				&pos,
				color		//�F�̏�Z
			)))
			{
				MessageBox(NULL, TEXT("�摜�̕`��Ɏ��s���܂���"), TEXT("Render"), MB_OK);
				return;
			}
		}
		m_pSprite->End();
	}


	//�e�N�X�`������T�[�t�F�C�X���擾
	bool	Image::GetSurfaceLevel(UINT level)
	{
		LPDIRECT3DSURFACE9 surf;
		if (FAILED(m_pTexture->GetSurfaceLevel(0, &surf)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�̎擾�Ɏ��s"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}

		dgd->SetRenderTarget(0, &surf);

		return true;
	}


	
	//�ȉ��̏����͂��܂����삵�Ȃ�
	//////////////////////////////////////////////////////////
	//�T�[�t�F�C�X�̍쐬
	void	Image::CreateSurface(UINT width, UINT height)
	{
		if (!dgd->CreateOffScreenPlainSurface(width, height, D3DPOOL_SYSTEMMEM, &backBufSurface, NULL))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�̍쐬�Ɏ��s"), TEXT("CreateSurface"), MB_OK);
			return;
		}
	}

	//�o�b�N�T�[�t�F�C�X�̎擾
	void	Image::GetRenderTarget(UINT level)
	{
		dgd->GetRenderTarget(level, &backBufSurface);
	}
	//�X�e���V���o�b�t�@�̎擾
	void	Image::GetDepthStencilSurface()
	{
		dgd->GetDepthStencilSurface(&backDepthSurface);
	}

	//�X�e���V���o�b�t�@�̍쐬
	void	Image::CreateStencilSurface(UINT width, UINT height)
	{
		if (!dgd->StencilBufCreate(&backDepthSurface, width, height))
		{
			MessageBox(NULL, TEXT("�X�e���V���o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("StencilBufCreate"), MB_OK);
			return;
		}
		//�X�e���V���o�b�t�@�̃Z�b�g
		dgd->SetDepthStencilSurface(&backDepthSurface);
	}

	//�T�[�t�F�C�X�̕`��
	void	Image::RenderSurface(IDirect3DSurface9* pSourceSurface,const RECT* pSourceRect,IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
	{
		dgd->SurfaceRender(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
	}




	//�ǉ�����------------------------------------
	//�摜�̏����󂯎��
	bool	Image::GetImageInfo(LPCWSTR fileName)
	{
		if (FAILED(D3DXGetImageInfoFromFileW(
			fileName,
			&imageInfo
		)))
		{
			MessageBox(NULL, TEXT("�摜�̏����󂯎��܂���ł���"), TEXT("GetImageInfo"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::GetImageInfo(LPCTSTR fileName)
	{
		if (FAILED(D3DXGetImageInfoFromFileA(
			fileName,
			&imageInfo
		)))
		{
			MessageBox(NULL, TEXT("�摜�̏����󂯎��܂���ł���"), TEXT("GetImageInfo"), MB_OK);
			return false;
		}
		return true;
	}


	//�摜�̃T�[�t�F�C�X�̎擾
	bool	Image::CreatePlainSurface()
	{
		if (FAILED(dgd->CreateOffScreenPlainSurface(
			imageInfo.Width, imageInfo.Height,
			D3DPOOL_DEFAULT, &surface, NULL
		)))
		{
			MessageBox(NULL, TEXT("�摜�̃T�[�t�F�C�X�̎擾�Ɏ��s���܂���"), TEXT("CreatePlainSurface"), MB_OK);
			return false;
		}
		return true;
	}

	

	//�T�[�t�F�C�X�ɉ摜��ǂݍ��܂���
	bool	Image::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
	{
		if (FAILED(D3DXLoadSurfaceFromFileW(
			surface,
			palette,
			rect,
			srcFile,
			srcRect,
			filter,
			colorKey,
			srcInfo
		)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�ɉ摜��ǂݍ��݂ł��܂���ł���"), TEXT("LoadSurfaceFromFile"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY * palette, const RECT * rect, LPCTSTR srcFile, const RECT * srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO * srcInfo)
	{
		if (FAILED(D3DXLoadSurfaceFromFileA(
			surface,
			palette,
			rect,
			srcFile,
			srcRect,
			filter,
			colorKey,
			srcInfo
		)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�ɉ摜��ǂݍ��݂ł��܂���ł���"), TEXT("LoadSurfaceFromFile"), MB_OK);
			return false;
		}
		return true;
	}

	//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
	bool	Image::LoadSurface(LPCWSTR fileName,const RECT* drawRect,const RECT* srcRect)
	{
		//�摜���̎擾
		this->GetImageInfo(fileName);
		//�T�[�t�F�C�X�̍쐬
		this->CreatePlainSurface();
		//�T�[�t�F�C�X�ɉ摜��ǂݍ���
		if (FAILED(LoadSurfaceFromFile(
			surface,
			NULL,
			drawRect,
			fileName,
			srcRect,
			D3DX_FILTER_NONE,
			0, NULL
		)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C���̓ǂݍ��ݎ��s"), TEXT("LoadSurface"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::LoadSurface(LPCTSTR fileName, const RECT * drawRect, const RECT * srcRect)
	{
		//�摜���̎擾
		this->GetImageInfo(fileName);
		//�T�[�t�F�C�X�̍쐬
		this->CreatePlainSurface();
		//�T�[�t�F�C�X�ɉ摜��ǂݍ���
		if (FAILED(LoadSurfaceFromFile(
			surface,
			NULL,
			drawRect,
			fileName,
			srcRect,
			D3DX_FILTER_NONE,
			0, NULL
		)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C���̓ǂݍ��ݎ��s"), TEXT("LoadSurface"), MB_OK);
			return false;
		}
		return true;
	}


	//�摜�̉�]
	void	Image::Rotation(float angle)
	{
		D3DXMATRIX	mRot;

		D3DXMatrixRotationY(&mRot, D3DXToRadian(angle));

		m_pSprite->SetTransform(&mRot);
	}

	//�摜�̊g��
	void	Image::Scale(D3DXVECTOR2 scale)
	{
		D3DXMATRIX	mScale;

		D3DXMatrixScaling(&mScale, scale.x, scale.y, 0);

		m_pSprite->SetTransform(&mScale);
	}

}


//----------------------------------------------------------------
//�t�H���g�̋@�\
//----------------------------------------------------------------
namespace Text
{
	Font::Font() : pFont(NULL)
	{

	}

	Font::~Font()
	{
		Destory();
	}

	//�t�H���g�̐���
	bool	Font::Create(LPCWSTR fontName, float width, float height)
	{
		if (FAILED(dgd->CreateFont2D(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			&pFont
		)))
		{
			MessageBox(NULL, TEXT("�t�H���g�̐����Ɏ��s"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
	bool	Font::Create(LPCSTR fontName, float width, float height)
	{
		if (FAILED(dgd->CreateFont2DA(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			&pFont
		)))
		{
			MessageBoxA(NULL, "�t�H���g�̐����Ɏ��s���܂���", "Create", MB_OK);
			return false;
		}
		return true;
	}

	//�t�H���g�̔j��
	void	Font::Destory()
	{
		if (pFont != NULL) { pFont->Release(); pFont = NULL; }
	}

	//�t�H���g�̕`��
	void	Font::Render(LPCWSTR string, Box2D box2D, D3DXCOLOR color)
	{
		//�\���͈͂�RECT�^
		RECT rc = {
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};

		pFont->DrawTextW(
			NULL,
			string,		//�`��e�L�X�g
			-1,			//�S�ĕ\��
			&rc,		//�\���͈�
			DT_LEFT,	//����
			color		//�F
		);
	}
	void	Font::Render(LPCSTR string, Box2D box2D, D3DXCOLOR color)
	{
		//�\���͈͂�RECT�^
		RECT rc = {
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};

		pFont->DrawTextA(
			NULL,
			string,		//�`��e�L�X�g
			-1,			//�S�ĕ\��
			&rc,		//�\���͈�
			DT_LEFT,	//����
			color		//�F
		);
	}
}



//----------------------------------------------------------------
//���f���̋@�\
//----------------------------------------------------------------
namespace XFile
{
	int ModelX::modelNum = -1;

	ModelX::ModelX() : m_pMesh(0),m_pMtrlBuf(0),m_texture(nullptr)
	{
		pos = D3DXVECTOR3(0, 0, 0);
		angle = D3DXVECTOR3(0, 0, 0);
		size = D3DXVECTOR3(1, 1, 1);
		modelNum++;
	}
	ModelX::~ModelX()
	{
		Erase();
	}

	//���f���̓ǂݍ���
	bool	ModelX::Load(LPCWSTR fileName)
	{
		if (FAILED(dgd->LoadModel(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh)))
		{
			MessageBox(NULL, TEXT("���f���̓ǂݍ��ݎ��s"), TEXT("Load"), MB_OK);
			return false;
		}
		return true;
	}
	bool	ModelX::Load(LPCSTR fileName)
	{
		if (FAILED(dgd->LoadModel(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh)))
		{
			MessageBoxA(NULL, "���f���̓ǂݍ��ݎ��s", "Load", MB_OK);
			return false;
		}
		return true;
	}

	//���f���̉��
	void	ModelX::Erase()
	{
		if (m_pMesh != nullptr) { m_pMesh->Release(); m_pMesh = nullptr; }
		if (m_pMtrlBuf != nullptr) { m_pMtrlBuf->Release(); m_pMtrlBuf = nullptr; }
		
	}

	//���f���̕`��
	void	ModelX::Render()
	{
		D3DMATERIAL9	mMaterial;

		//�}�e���A���������o��
		D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
		m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//�e�N�X�`�����}�e���A���̐������p��

		for (DWORD i = 0; i < m_MtrlNum; i++)
		{
			mMaterial = mD3DXMaterials[i].MatD3D;	//�}�e���A���̃R�s�[
			dgd->SetMaterial(&mMaterial);			//�}�e���A���̃Z�b�g
			m_texture[i] = NULL;					//�e�N�X�`���Ȃ�

			//�g�p���Ă���e�N�X�`��������Γǂݍ���
			if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
			{
				if (FAILED(dgd->CretateTexture(mD3DXMaterials[i].pTextureFilename, &m_texture[i])))
				{
					MessageBox(NULL, TEXT("���s���܂���"), TEXT("���s���Ă܂�"), MB_OK);
					return;
				}
				LibDGD::SetTexture(0, m_texture[i]);	//�e�N�X�`�����Z�b�g����
			} 
			if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
			delete m_texture[i];


			m_pMesh->DrawSubset(i);					//�`��

			LibDGD::SetTexture(0, NULL);			//�e�N�X�`���̐ݒ�����Ƃɖ߂�
		}
	}

	

	
	//��--------------------
	bool	ModelX::BoundingBox()
	{
		DWORD numv, stride;
		LPDIRECT3DVERTEXBUFFER9	vb;
		BYTE*		pvertices;
		HRESULT		hr = S_OK;
		D3DXVECTOR3	lmin, lmax;

		numv = m_pMesh->GetNumVertices();		//���_��
		stride = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
		
		//���_�o�b�t�@�̎擾
		if (FAILED(m_pMesh->GetVertexBuffer(&vb)))
		{
			MessageBox(NULL, TEXT("���b�V���̒��_�o�b�t�@�擾�Ɏ��s���܂���"), TEXT("GetVertexBuf"), MB_OK);
			return false;
		}

		vb->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�̃��b�N
		if (FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices,
			numv, stride, &lmin, &lmax)))
		{
			MessageBox(NULL, TEXT("�o�E���f�B���O�{�b�N�X�̍쐬�Ɏ��s���܂���"), TEXT("ComputBound"), MB_OK);
			return false;
		}
		
		LPD3DXMESH		tempMesh;
		//�}�e���A���̃N���[��
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), dgd->m_pD3DDevice, &tempMesh);

		minB = pos + lmin;
		maxB = pos + lmax;
		vb->Unlock();
		
		return true;
	}
}


////////////////////////////////////////////////////////////////////
//�t�H���g�̏���
namespace LibFont
{
	bool	Create(LPCWSTR fontName, float width, float height,LPD3DXFONT* pFont)
	{
		if (FAILED(dgd->CreateFont2D(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			pFont
		)))
		{
			MessageBox(NULL, TEXT("�t�H���g�̐����Ɏ��s"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
	bool	Create(LPCSTR fontName, float width, float height, LPD3DXFONT* pFont)
	{
		if (FAILED(dgd->CreateFont2DA(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			pFont
		)))
		{
			MessageBox(NULL, TEXT("�t�H���g�̐����Ɏ��s"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
}

//�e�N�X�`���̏���
namespace LibTexture
{
	//�摜�̐�������
	void	Create(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex)) { return; }
	}
	void	Create(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex)) { return; }
	}


	//�X�v���C�g�̍쐬
	void	CreateSprite(LPD3DXSPRITE* sprite)
	{
		if (FAILED(dgd->CreateSprite(sprite)))
		{
			MessageBox(NULL, TEXT("�X�v���C�g�̐����Ɏ��s���܂���"), TEXT("CreateSprite"), MB_OK);
			return;
		}
	}

	//�摜�̃T�[�t�F�C�X�̎擾
	bool	CreatePlainSurface(D3DXIMAGE_INFO* imageInfo,LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED(dgd->CreateOffScreenPlainSurface(
			imageInfo->Width, imageInfo->Height,
			D3DPOOL_DEFAULT, surface, NULL
		)))
		{
			MessageBox(NULL, TEXT("�摜�̃T�[�t�F�C�X�̎擾�Ɏ��s���܂���"), TEXT("CreatePlainSurface"), MB_OK);
			return false;
		}
		return true;
	}

	//�T�[�t�F�C�X�̕`��
	void	RenderSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
	{
		dgd->SurfaceRender(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
	}

	//�T�[�t�F�C�X�̍쐬
	void	CreateSurface(UINT width, UINT height, LPDIRECT3DSURFACE9* backBufSurface)
	{
		if (!dgd->CreateOffScreenPlainSurface(width, height, D3DPOOL_SYSTEMMEM, backBufSurface, NULL))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�̍쐬�Ɏ��s"), TEXT("CreateSurface"), MB_OK);
			return;
		}
	}

	//�e�N�X�`������T�[�t�F�C�X���擾
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex,LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED((*pTex)->GetSurfaceLevel(level, surface)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�̎擾�Ɏ��s"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}
		return true;
	}
}

//���f���̏���
namespace LibModel
{
	//���[�h����
	void	Load(LPCWSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
	{
		if (!dgd->LoadModel(fileName, mtrlBuf, numMtrl, mesh))
		{
			MessageBox(NULL, TEXT("���f���̃��[�h�Ɏ��s���܂���"), TEXT("Load"), MB_OK);
			return;
		}
	}
	void	Load(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
	{
		if (!dgd->LoadModel(fileName, mtrlBuf, numMtrl, mesh))
		{
			MessageBoxA(NULL, "���f���̃��[�h�Ɏ��s���܂���", "Load", MB_OK);
			return;
		}
	}

	//�}�e���A���̃Z�b�g
	void	SetMaterial(D3DMATERIAL9* material)
	{
		dgd->SetMaterial(material);
	}
}

//Matrix�̏���
namespace LibMatrix
{
	void	SetMatrix(D3DTRANSFORMSTATETYPE type, D3DXMATRIX* mat)
	{
		dgd->SetMatrixToRender(type, mat);
	}
}


//�V�F�[�_�̏���
namespace LibShader
{
	//�V�F�[�_�t�@�C���̓ǂݍ���
	bool	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		if (!dgd->LoadEffectFile(fileName, pEffect, pErr)) { return false; }
		return true;
	}
	bool	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		if (!dgd->LoadEffectFile(fileName, pEffect, pErr)) { return false; }
		return true;
	}
}


//-----------------------------------------------------------
//�r���{�[�h�̋@�\
//Vertex�Ńe�N�X�`�����쐬
//-----------------------------------------------------------
namespace VertexBuf
{
	//�R���X�g���N�^
	Billboard::Billboard() : m_pVB(NULL),m_pTexture(NULL)
	{
		
	}

	//�f�X�g���N�^
	Billboard::~Billboard()
	{
		Destroy();
	}



	//�r���{�[�h�̐���
	bool	Billboard::Create()
	{
		//���_�o�b�t�@�̐���
		if(FAILED(dgd->CreateVertexBuf(
			4 * sizeof(Vertex),	//���_�o�b�t�@�̐�
			VertexFVF,			//���_�o�b�t�@��FVF�t�H�[�}�b�g
			&m_pVB
		)))
		{
			MessageBox(NULL, TEXT("���_�̐����Ɏ��s"), TEXT("CreateVertexBuf"), MB_OK);
			return false;
		}

		return true;
	}


	//���_�o�b�t�@�ɒ���t����摜�̓ǂݍ���
	bool	Billboard::LoadVertexTex(LPCWSTR fileName)
	{
		if (!dgd->CretateTexture(fileName, &m_pTexture))
		{
			MessageBox(NULL, TEXT("�摜�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("LoadVertexTex"), MB_OK);
			return false;
		}
		return true;
	}

	bool	Billboard::LoadVertexTexA(LPCSTR fileName)
	{
		if (!dgd->CretateTexture(fileName, &m_pTexture))
		{
			MessageBox(NULL, TEXT("�摜�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("LoadVertexTex"), MB_OK);
			return false;
		}
		return true;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	void	Billboard::SetVertex()
	{
		Vertex* v;

		//���_�̃��b�N
		if (FAILED(m_pVB->Lock(0, 0, (void**)&v, 0)))
		{
			MessageBox(NULL, TEXT("���b�N�Ɏ��s���܂���"), TEXT("Lock"), MB_OK);
			return;
		}


		//���_�f�[�^ : ���_�̍��W�l�̐ݒ�
		v[0].pos = D3DXVECTOR3(-1.5f, 1.5f, 0);		//���_�P
		v[1].pos = D3DXVECTOR3(1.5f, 1.5f, 0);		//���_�Q
		v[2].pos = D3DXVECTOR3(-1.5f, -1.5f, 0);	//���_�R
		v[3].pos = D3DXVECTOR3(1.5f, -1.5f, 0);		//���_�S

		//���_�f�[�^ : ���_�̐F
		v[0].diffuse = D3DXCOLOR(0, 1, 1, 1);
		v[1].diffuse = D3DXCOLOR(1, 0, 1, 1);
		v[2].diffuse = D3DXCOLOR(1, 0.5f, 0, 1);
		v[3].diffuse = D3DXCOLOR(0.5f, 1, 1, 1);

		//���_�̃e�N�X�`���̍��W
		v[0].tex = D3DXVECTOR2(0, 0);
		v[1].tex = D3DXVECTOR2(1, 0);
		v[2].tex = D3DXVECTOR2(0, 1);
		v[3].tex = D3DXVECTOR2(1, 1);

		m_pVB->Unlock();


		//�e�N�X�`���X�e�[�W�̐ݒ�
		//���̐ݒ�
		//���_��ݒ肵����ŌĂяo��
		//�e�N�X�`���X�e�[�W�̐ݒ�
		
	}

	//���_1�̐ݒ�
	//void	Billboard::SetVertex(int number, D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXCOLOR color)
	//{
	//	
	//	//�ԍ������_�̐��ȓ�
	//	if (number < 0 && 3 < number) 
	//	{
	//		MessageBox(NULL, TEXT("���Ă͂܂钸�_������܂���"), TEXT("SetVertex"), MB_OK);
	//		return; 
	//	}
	//	
	//	//���_�̐ݒ�
	//
	//	if (FAILED(m_pVB->Lock(0, 0, (void**)&vertex, 0)))
	//	{
	//		MessageBox(NULL, TEXT("���_�̃��b�N�Ɏ��s���܂���"), TEXT("Lock"), MB_OK);
	//		return;
	//	}

	//	//���_�̍��W�l�̐ݒ�
	//	vertex[number].pos = pos;
	//	vertex[number].diffuse = color;
	//	vertex[number].tex = tex;

	//	m_pVB->Unlock();
	//}


	//�r���{�[�h�̔j��
	void	Billboard::Destroy()
	{
		if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }
		if (m_pVB != NULL) { m_pVB->Release(); m_pVB = NULL; }
		
	}

	//�r���{�[�h�̕`��
	void	Billboard::Render()
	{
		dgd->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		dgd->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		dgd->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		dgd->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		dgd->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		dgd->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		//�e�N�X�`�����p�C�v���C���ɃZ�b�g
		dgd->SetVertexTexture(0, m_pTexture);

		//���_�o�b�t�@�̕`��
		dgd->SetVertexBufRender(0, m_pVB, 0, sizeof(Vertex));

		//FVF�t�H�[�}�b�g�̐ݒ�
		dgd->SetVertexFVF(VertexFVF);

		//�`��
		dgd->VertexRender(D3DPT_TRIANGLESTRIP, 0, 2);
		
		dgd->SetVertexTexture(0, NULL);
	}


	void	Billboard::SetMatrix()
	{
		D3DXMATRIX	mMove;
		D3DXMATRIX	mRot;
		D3DXMATRIX	mScale;

		D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
		D3DXMatrixRotationY(&mRot, D3DXToRadian(angle.y));
		D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

		
	}
}




//--------------------------------------------------------------------------
//�}�g���b�N�X�@�\
//--------------------------------------------------------------------------
namespace Mat4X4
{
	Matrix::Matrix()
	{
		D3DXMatrixIdentity(&mat);
	}


	//�}�g���b�N�X���Z�b�g����
	void	Matrix::SetMatrix(D3DTRANSFORMSTATETYPE type)
	{
		dgd->SetMatrixToRender(type, &mat);
	}
}



//------------------------------------------------------
//�V�F�[�_�֘A����
//------------------------------------------------------
namespace Effect
{
	//�R���X�g���N�^
	Shader::Shader() : m_pEffect(NULL),m_pErr(NULL)
	{

	}

	//�f�X�g���N�^
	Shader::~Shader()
	{
		if (m_pEffect != NULL) { m_pEffect->Release(); m_pEffect = NULL; }
		if (m_pErr != NULL) { m_pErr->Release(); m_pErr = NULL; }
	}

	//���[�h����
	void	Shader::Load(LPCWSTR fileName)
	{
		if (FAILED(dgd->LoadEffectFile(fileName, &m_pEffect, m_pErr)))
		{
			MessageBox(NULL, TEXT("���[�h�Ɏ��s"), TEXT("EffectFile"), MB_OK);
			return;
		}
		else
		{
			m_hTechnique	= m_pEffect->GetTechniqueByName("TShader");
			m_hmWVP			= m_pEffect->GetParameterByName(NULL, "mWVP");
			m_hmWIT			= m_pEffect->GetParameterByName(NULL, "mWIT");
			m_hvLightDir	= m_pEffect->GetParameterByName(NULL, "vLightDir");
			m_hvCol			= m_pEffect->GetParameterByName(NULL, "vColor");	
		}
	}
	void	Shader::Load(LPCSTR fileName)
	{
		if (FAILED(dgd->LoadEffectFile(fileName, &m_pEffect, m_pErr)))
		{
			MessageBoxA(NULL, "�V�F�[�_�t�@�C���̃��[�h�Ɏ��s", "Load", MB_OK);
			return;
		}
		else
		{
			m_hTechnique = m_pEffect->GetTechniqueByName("TShader");
			m_hmWVP = m_pEffect->GetParameterByName(NULL, "mWVP");
			m_hmWIT = m_pEffect->GetParameterByName(NULL, "mWIT");
			m_hvLightDir = m_pEffect->GetParameterByName(NULL, "vLightDir");
			m_hvCol = m_pEffect->GetParameterByName(NULL, "vColor");
		}
	}
	
	//�e�N�j�b�N���̐ݒ�
	void	Shader::SetTechnique(const char* techniqueName)
	{
		m_hTechnique = m_pEffect->GetTechniqueByName(techniqueName);
	}
	//�ˉe�ϊ��s�񖼂̐ݒ�
	void	Shader::SetProjectViewMatrixName(const char* WVPName)
	{
		m_hmWVP = m_pEffect->GetParameterByName(NULL, WVPName);
	}
	//���[���h�ϊ��s�񖼂̐ݒ�
	void	Shader::SetWorldMatrixName(const char* WITName)
	{
		m_hmWIT = m_pEffect->GetParameterByName(NULL, WITName);
	}
	//���C�g�̕������̐ݒ�
	void	Shader::SetLightDirName(const char* lightDirName)
	{
		m_hvLightDir = m_pEffect->GetParameterByName(NULL, lightDirName);
	}
	//�F�̖��O�̐ݒ�
	void	Shader::SetColorName(const char* colorName)
	{
		m_hvCol = m_pEffect->GetParameterByName(NULL, colorName);
	}

	//�V�F�[�_�f�o�C�X�̃��X�g
	void	Shader::DeviceLost()
	{
		if (m_pEffect != NULL) { m_pEffect->OnLostDevice(); }
	}
	//�V�F�[�_�f�o�C�X�̕���
	void	Shader::DeviceReset()
	{
		if (m_pEffect != NULL) { m_pEffect->OnResetDevice(); }
	}

	//�V�F�[�_�t�@�C���̐ݒ�
	void	Shader::Set()
	{
		//���[�J�� - �ˉe�ϊ��s��
		D3DXMATRIX	playerMat;		//�v���C���[�̃��[���h�}�g���b�N�X
		D3DXMATRIX	worldMat;		//���[���h�}�g���b�N�X
		D3DXMatrixInverse(&playerMat, NULL, &worldMat);
		D3DXMatrixTranspose(&playerMat, &worldMat);

		//���[�J�� - �ˉe�ϊ��s��
		D3DXMATRIX	cameraView, cameraProj;
		playerMat = worldMat * cameraView * cameraProj;

		//���C�g�̕���
		D3DXVECTOR4	lightPos(0, 0, 0, 1);
		m_pEffect->SetVector(NULL, &lightPos);

	}

	//�V�F�[�_�̕`��
	void	Shader::Render()
	{

		if (m_pEffect == NULL) { return; }
		
		//�V�F�[�_�̐ݒ�
		m_pEffect->SetTechnique(m_hTechnique);
		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);
		dgd->SetVertexFVF(D3DFVF_XYZ | D3DFVF_NORMAL);

		Set();
		
		//�`��
		m_pEffect->End();
	}

	//�ʒu�E�}�g���b�N�X�̐ݒ�
	void	Shader::SetMatrix(D3DXMATRIX* mat)
	{
		m_pEffect->SetMatrix(NULL, mat);
	}
	void	Shader::SetVector(D3DXVECTOR4* vec)
	{
		m_pEffect->SetVector(NULL, vec);
	}
	void	Shader::SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat)
	{
		m_pEffect->SetMatrix(handle, mat);
	}
	void	Shader::SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec)
	{
		m_pEffect->SetVector(handle, vec);
	}


	//�V�F�[�_�̃p�����[�^�ݒ�
	//�V�F�[�_�̃e�N�j�b�N�̐ݒ�
	D3DXHANDLE	Shader::GetParamTechnique(const char* technique)
	{
		return m_pEffect->GetTechniqueByName(technique);
	}
	//�V�F�[�_�̕ϐ��̐ݒ�
	D3DXHANDLE	Shader::GetParameterName(const char* shaderName)
	{
		return m_pEffect->GetParameterByName(NULL, shaderName);
	}

	//�e�N�X�`���̐ݒ�
	bool	Shader::SetParamTexture(const char* texName,LPDIRECT3DTEXTURE9 tex)
	{
		if (FAILED(m_pEffect->SetTexture(texName, tex)))
		{
			MessageBox(NULL, TEXT("�e�N�X�`�����V�F�[�_�ɃZ�b�g�ł��܂���"), TEXT("SetParamTexture"), MB_OK);
			return false;
		}
		return true;
	}


	//�`��֌W
	void	Shader::BeginPass(UINT pass)
	{
		m_pEffect->BeginPass(pass);
	}
	void	Shader::EndPass()
	{
		m_pEffect->EndPass();
	}
	void	Shader::Begin(UINT* pass,DWORD flags)
	{
		m_pEffect->Begin(pass,flags);
	}
	void	Shader::End()
	{
		m_pEffect->End();
	}
}


//-------------------------------------------------------
//�����̃I�u�W�F�N�g���ʂ̋@�\
//-------------------------------------------------------
namespace LibDGD
{
	//�����_�����O�p�C�v���C���ɃZ�b�g
	void	SetRenderState(D3DRENDERSTATETYPE type, DWORD value)
	{
		dgd->SetRenderState(type, value);
	}

	//�e�N�X�`���X�e�[�W�X�e�[�g
	void	SetTexStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
	{
		dgd->SetTextureStageState(stage, type, value);
	}

	//�e�N�X�`���̃��b�s���O���[�h�̃Z�b�g
	void	SetTexSamplerState(DWORD stage, D3DSAMPLERSTATETYPE type, DWORD value)
	{
		dgd->SetSamplerState(stage, type, value);
	}

	//���_�o�b�t�@�̃X�g���[���\�[�X���Z�b�g
	void	SetStreamSource(UINT streamNum, IDirect3DVertexBuffer9* vertexBuf, UINT offsetBuf, UINT stride)
	{
		dgd->SetVertexBufRender(streamNum, vertexBuf, offsetBuf, stride);
	}

	//���_�o�b�t�@��FVF�̃Z�b�g
	void	SetFVF(DWORD fvf)
	{
		dgd->SetVertexFVF(fvf);
	}

	//���_�o�b�t�@�̕`��
	void	DrawPrimitive(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum)
	{
		dgd->VertexRender(renderType, startVertex, primitiveNum);
	}

	//���_�o�b�t�@�̐ݒ�
	bool	CreateVertexBuffer(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf)
	{
		if (FAILED(dgd->CreateVertexBuf(
			len,
			fvf,
			vertexBuf
		)))
		{
			MessageBox(NULL, TEXT("���_�o�b�t�@�̎��s"), TEXT("CreateVertexBuffer"), MB_OK);
			return false;
		}
		return true;
	}
	//���_�f�R���[�V�����̍쐬
	void	CreateVertexDeclaration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl)
	{
		if (!dgd->CreateVertexDecration(decl, pDecl)) { return; }
	}

	//�e�N�X�`���̓ǂݍ���(VertexBuf�p)
	bool	CreateTexVertexBuf(LPCTSTR fileName,LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex))
		{
			return false;
		}
		return true;
	}

	//�e�N�X�`���摜�̓ǂݍ���
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture)
	{
		if (FAILED(dgd->CreateTextureEx(
			fileName, 
			width,
			height,
			colorKey,
			pSrcInfo,
			pPalette,
			texture
		)))
		{
			MessageBox(NULL, TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("CreateTexture"), MB_OK);
			return false;
		}
		return true;
	}

	bool CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO * pSrcInfo, PALETTEENTRY * pPalette, LPDIRECT3DTEXTURE9 * texture)
	{
		if (FAILED(dgd->CreateTextureEx(
			fileName,
			width,
			height,
			colorKey,
			pSrcInfo,
			pPalette,
			texture
		)))
		{
			MessageBox(NULL, TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"), TEXT("CreateTexture"), MB_OK);
			return false;
		}
		return true;
	}


	//�e�N�X�`�����p�C�v���C���ɃZ�b�g
	void	SetTexture(DWORD number, LPDIRECT3DTEXTURE9 m_pTex)
	{
		dgd->SetVertexTexture(number, m_pTex);
	}

	//�r���[�ƃX�e���V���̃N���A
	bool	ViewAndStencilClear()
	{
		if (!dgd->ViewAndStencilClear())
		{
			return false;
		}
		return true;
	}

	//�o�b�N�V�[���̃N���A
	void	SceneClear()
	{
		dgd->ViewAndStencilClear();
	}

	//Z�o�b�t�@�̃N���A
	void	ZBufClear()
	{
		dgd->ZBufClear();
	}

	//�r���[�|�[�g�̐ݒ�
	bool	SetViewPort(D3DVIEWPORT9* viewport)
	{
		if (!dgd->SetViewPort(viewport)) { return false; }
		return true;
	}

	//���C�g�̃Z�b�g
	void	SetLight(int number, D3DLIGHT9* pLight)
	{
		dgd->SetLight(number, pLight);
	}
	//���C�g���g�p���邩�̃Z�b�g
	void	SetUseLight(int number, bool useFlag)
	{
		dgd->LightEnable(number, useFlag);
	}

	//�`��̊J�n
	bool	BeginRender()
	{
		if (dgd->BeginRender())
		{
			return true;
		}
		return false;
	}
	//�`��̏I��
	void	EndRender()
	{
		dgd->EndRender();
	}
	//�`��̔��f
	void	PresentRender()
	{
		dgd->PresentRender();
	}

	//�V���h�E�}�b�v�֌W
	//�e�N�X�`���̐���
	void	CreateTexture(UINT width, UINT height, LPDIRECT3DTEXTURE9* tex)
	{
		dgd->TextureCreate(tex, width, height);
	}
	//�e�N�X�`������T�[�t�F�C�X���擾
	bool	GetSurfaceLevel(UINT level, LPDIRECT3DTEXTURE9* pTex, LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED((*pTex)->GetSurfaceLevel(level, surface)))
		{
			MessageBox(NULL, TEXT("�T�[�t�F�C�X�̎擾�Ɏ��s"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}
		return true;
	}
	//�[�x�o�b�t�@�̍쐬
	void	CreateDepthStencilSurface(UINT width,UINT height,LPDIRECT3DSURFACE9* surface)
	{
		if (!dgd->StencilBufCreate(surface, width, height))
		{
			return;
		}
	}
	void	CreateDepthStencilSurface(UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality, LPDIRECT3DSURFACE9* surf)
	{
		if (!dgd->StencilBufCreate(surf, width, height, format, type, quality))
		{
			return;
		}
	}

	//�����_�����O�^�[�Q�b�g�̎擾
	void	GetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
	{
		dgd->GetRenderTarget(targetIndex, surface);
	}
	//�[�x�o�b�t�@�̎擾
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
	{
		dgd->GetDepthStencilSurface(surface);
	}

	//�����_�����O�^�[�Q�b�g�̐ݒ�
	void	SetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
	{
		dgd->SetRenderTarget(targetIndex, surface);
	}
	//�[�x�o�b�t�@�̐ݒ�
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
	{
		dgd->SetDepthStencilSurface(surface);
	}
	//���_�V�F�[�_�̐ݒ�
	void	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader)
	{
		if (!dgd->SetVertexShader(pShader))
		{
			MessageBoxA(NULL, "�o�[�e�b�N�X�V�F�[�_�̐ݒ�Ɏ��s���܂���", "SetVertexShader", MB_OK);
			return;
		}
	}
	//�s�N�Z���V�F�[�_�̐ݒ�
	void	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader)
	{
		dgd->SetPixelShader(pShader);
	}

	//--------------------------------------
	//�V�F�[�_�֘A�̏���
	//�V�F�[�_�t�@�C���̓ǂݍ���
	void	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		dgd->LoadEffectFile(fileName, pEffect, pErr);
	}
	void	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		dgd->LoadEffectFile(fileName, pEffect, pErr);
	}

	//���_�V�F�[�_�̃n���h���𐶐�
	void	CreateVertexShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHander)
	{
		if (!dgd->CreateVertexShader(pShader, func, shaderHander))
		{
			return;
		}
	}
	//�s�N�Z���V�F�[�_�̃n���h���𐶐�
	void	CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler)
	{
		if (!dgd->CreatePixelShader(pShader, func, shaderHandler))
		{
			return;
		}
	}


	//�ǉ��̉�����
	void	SetVertexBuf(UINT num,IDirect3DVertexBuffer9* verBuf,UINT size,UINT zero)
	{
		dgd->SetVertexBufRender(num, verBuf, size, zero);
	}
	void	VertexRender(D3DPRIMITIVETYPE type,UINT start,UINT num)
	{
		dgd->VertexRender(type, start, num);
	}
}



//--------------------------------------------------
//Direct3DDevice�̏���
//--------------------------------------------------
namespace LibDEV
{
	//�f�o�C�X�̏�����
	HRESULT	InitDevice(HWND hWnd, BOOL isFullScreen, int clientWidth, int clientHeight)
	{
		if (FAILED(dgd->DeviceInit(hWnd, isFullScreen, clientWidth, clientHeight)))
		{
			return E_FAIL;
		}
		return S_OK;
	}

	//�f�o�C�X�̉��
	void	FinalDevice()
	{
		dgd->DeviceFinal();
	}

	//�f�o�C�X��n��
	LPDIRECT3DDEVICE9* GetDevice()
	{
		return &dgd->m_pD3DDevice;
	}
}