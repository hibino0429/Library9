#include "Texture.h"

//�R���X�g���N�^
Texture::Texture() : sprite(nullptr),texture(nullptr),backBufSurface(nullptr),backDepthSurface(nullptr),
surface(nullptr)
{
}

//�f�X�g���N�^
Texture::~Texture()
{
	Destroy();
}


//------------------------------------------------------------------/
//public:���J���A�񋟂��郁�\�b�h
//------------------------------------------------------------------/
//�摜�̃��[�h
void	Texture::Load(LPCWSTR fileName)
{
	LibTexture::Create(fileName, &texture);		//�摜�̐���
	LibTexture::CreateSprite(&sprite);			//�X�v���C�g�̐���
	LoadSurface(fileName, nullptr, nullptr);	//�T�[�t�F�C�X�ɉ摜��ǂݍ��܂���
}
void	Texture::Load(LPCSTR fileName)
{
	LibTexture::Create(fileName, &texture);
	LibTexture::CreateSprite(&sprite);
	LoadSurface(fileName, nullptr, nullptr);	
}

//�摜�̔j��
void	Texture::Destroy()
{
	if (sprite != nullptr) { sprite->Release(); sprite = nullptr; }
	if (texture != nullptr) { texture->Release(); texture = nullptr; }
	if (backBufSurface != nullptr) { backBufSurface->Release(); backBufSurface = nullptr; }
	if (backDepthSurface != nullptr) { backDepthSurface->Release(); backDepthSurface = nullptr; }
}

//�摜�̕`��
void	Texture::Render(Box2D draw, Box2D src, D3DXCOLOR color)
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
	D3DXVECTOR2		scale;
	scale.x = (float)src.sizeX / draw.sizeX * 2.0f;
	scale.y = (float)src.sizeY / draw.sizeY * 2.0f;
	D3DXMATRIX	matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1);
	

	//�摜�\�[�X�͈̔͂�������Ŏw�肷��
	//
	if (SUCCEEDED(sprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		if (FAILED(sprite->Draw(
			texture,
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
	sprite->End();
}



//------------------------------------------------------------------------------------------/
//private:���J�����A�񋟂��Ȃ����\�b�h
//------------------------------------------------------------------------------------------/

//------------------------------------------------------------------
//�摜�̏����擾���A�T�[�t�F�C�X�ɏ���ǂݍ���
//------------------------------------------------------------------
bool	Texture::LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect)
{
	//1:�摜���̎擾
	GetImageInfo(fileName);
	//2:�T�[�t�F�C�X�̍쐬
	CreatePlainSurface();
	//3:�T�[�t�F�C�X�ɉ摜��ǂݍ���
	if (!LoadSurfaceFromFile(
		surface,
		NULL,
		drawRect,
		fileName,
		srcRect,
		D3DX_FILTER_NONE,
		0, NULL
	))
	{
		MessageBox(NULL, TEXT("�T�[�t�F�C���̓ǂݍ��ݎ��s"), TEXT("LoadSurface"), MB_OK);
		return false;
	}
	return true;

}
bool	Texture::LoadSurface(LPCSTR fileName, const RECT* drawRect, const RECT* srcRect)
{
	//1:�摜���̎擾
	GetImageInfo(fileName);
	//2:�T�[�t�F�C�X�̍쐬
	CreatePlainSurface();
	//3:�T�[�t�F�C�X�ɉ摜��ǂݍ���
	if (!LoadSurfaceFromFile(
		surface,
		NULL,
		drawRect,
		fileName,
		srcRect,
		D3DX_FILTER_NONE,
		0, NULL
	))
	{
		MessageBox(NULL, TEXT("�T�[�t�F�C���̓ǂݍ��ݎ��s"), TEXT("LoadSurface"), MB_OK);
		return false;
	}
	return true;

}

//------------------------------------------------------------------
//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
//------------------------------------------------------------------
bool	Texture::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, 
									const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, 
									DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
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
bool	Texture::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette,
	const RECT* rect, LPCSTR srcFile, const RECT* srcRect,
	DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
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

//------------------------------------------------------------------
//�摜�t�@�C���̃T�C�Y���t�H�[�}�b�g���擾
//------------------------------------------------------------------
bool	Texture::GetImageInfo(LPCWSTR fileName)
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
bool	Texture::GetImageInfo(LPCSTR fileName)
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

//------------------------------------------------------------------
//�摜�̃T�[�t�F�C�X�̎擾
//------------------------------------------------------------------
//�摜�̃T�[�t�F�C�X�̎擾
bool	Texture::CreatePlainSurface()
{
	if (!LibTexture::CreatePlainSurface(&imageInfo, &surface)) { return false; }
	return true;
}

//------------------------------------------------------------------
//�摜�̉�]�E�g��k��
//------------------------------------------------------------------
//�摜�̉�]
void	Texture::Rotation(float angle)
{
	D3DXMATRIX	mRot;

	D3DXMatrixRotationY(&mRot, D3DXToRadian(angle));

	sprite->SetTransform(&mRot);
}

//�摜�̊g��
void	Texture::Scale(D3DXVECTOR2 scale)
{
	D3DXMATRIX	mScale;

	D3DXMatrixScaling(&mScale, scale.x, scale.y, 0);

	sprite->SetTransform(&mScale);
}