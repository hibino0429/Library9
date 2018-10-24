#include "Font.h"

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
	if (!LibFont::Create(fontName, width, height, &pFont))
	{
		return false;
	}
	return true;
}
bool	Font::Create(LPCSTR fontName, float width, float height)
{
	if (!LibFont::Create(fontName, width, height, &pFont))
	{
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
