#include "Obj.h"

//�R���X�g���N�^
Obj::Obj()
{
	//gameObj.CreateModel("�G1.x", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));
}

//�f�X�g���N�^
Obj::~Obj()
{
	
}

//������
void	Obj::Initialize()
{
	gameObj.CreateModel("./data/Model/Enemy/enemy2.x", D3DXVECTOR3(50, 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(10, 10, 10));
}

//�X�V����
void	Obj::UpDate()
{
	//gameObj.GetModel().GetPos().x++;
}

//�`��
void	Obj::Render(ZTexture* zTex)
{
	gameObj.ZTexRender(zTex);
}

void	Obj::Render(DepthTexture* depTex)
{
	gameObj.DepthRender(depTex);
}