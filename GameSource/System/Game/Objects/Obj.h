#pragma once
#include "../../../Library9/Function.h"
#include "GameObject.h"

//モデルクラス
class Obj
{
public:
	Obj();
	~Obj();

	void	Initialize();
	void	UpDate();
	void	Render(ZTexture* zTex);
	void	Render(DepthTexture* depTex);

private:
	GameObject	gameObj;

};