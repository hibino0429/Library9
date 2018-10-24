#include "Obj.h"

//コンストラクタ
Obj::Obj()
{
	//gameObj.CreateModel("敵1.x", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));
}

//デストラクタ
Obj::~Obj()
{
	
}

//初期化
void	Obj::Initialize()
{
	gameObj.CreateModel("./data/Model/Enemy/enemy2.x", D3DXVECTOR3(50, 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(10, 10, 10));
}

//更新処理
void	Obj::UpDate()
{
	//gameObj.GetModel().GetPos().x++;
}

//描画
void	Obj::Render(ZTexture* zTex)
{
	gameObj.ZTexRender(zTex);
}

void	Obj::Render(DepthTexture* depTex)
{
	gameObj.DepthRender(depTex);
}