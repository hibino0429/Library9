#pragma once
#include "../Function.h"


//----------------------------------------------------------------------
//�t�H���g�N���X
//----------------------------------------------------------------------
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
	bool	Create(LPCWSTR, float, float);
	bool	Create(LPCSTR, float, float);
	//�t�H���g�̉��
	void	Destory();

	//�t�H���g�̕`��
	//����1:������
	//����2:�\���͈�
	//����3:�F
	void	Render(LPCWSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));
	void	Render(LPCSTR, Box2D, D3DXCOLOR = D3DXCOLOR(1, 1, 1, 1));
private:
	LPD3DXFONT		pFont;	//�t�H���g�I�u�W�F�N�g
};