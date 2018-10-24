#pragma once
#include "../Function.h"


//----------------------------------------------------------------
//�e�N�X�`���N���X
//----------------------------------------------------------------
class Texture
{
public:

	Texture();
	~Texture();
	//�񋟂��郁�\�b�h

	//�ǂݍ��ݏ���
	//����1:�摜�̃t�@�C���p�X
	void	Load(LPCWSTR);
	void	Load(LPCSTR);

	//�摜�̔j��
	void	Destroy();

	//����1:�摜�̈ʒu�E�傫��
	//����2:�\�[�X�̉摜�̈ʒu�E�傫��
	//����3:�摜�̐F
	void	Render(Box2D, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));

private:
	//�摜�t�@�C���̃T�C�Y���t�H�[�}�b�g���擾
	bool	GetImageInfo(LPCWSTR fileName);
	bool	GetImageInfo(LPCSTR fileName);

	//�T�[�t�F�C�X�ɉ摜�t�@�C����ǂݍ���
	bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);
	bool	LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo);

	//�T�[�t�F�C�X�ɉ摜����ǂݍ���
	bool	LoadSurface(LPCWSTR fileName, const RECT* drawRect, const RECT* srcRect);
	bool	LoadSurface(LPCSTR fileName, const RECT* drawRect, const RECT* srcRect);

	//�T�[�t�F�C�X����
	bool	CreatePlainSurface();				//�摜�̃T�[�t�F�C�X���쐬

	//�摜�̉�]�E�g��k��
	void	Rotation(float angle);
	void	Scale(D3DXVECTOR2 scale);

private:

	LPD3DXSPRITE		sprite;				//�X�v���C�g�̊i�[
	LPDIRECT3DTEXTURE9	texture;			//�e�N�X�`���̊i�[


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