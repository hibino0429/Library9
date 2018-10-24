#pragma once
#include "../../../Library9/Function.h"


//------------------------------------------
//ポリゴンメッシュのデータ定義
//------------------------------------------
class SkinAnim
{
public:


private:

	//頂点情報
	struct Vertex
	{
		D3DXVECTOR3		coord;
		D3DXVECTOR3		weight;
		unsigned char matrixIndex[4];
	};

	void	VertexDeclaration();		//頂点宣言


	//ボーン
	struct Bone
	{
		int id;
		Bone*	firstChild;
		Bone*	sibling;

		D3DXMATRIX offsetMat;
		D3DXMATRIX initMat;
		D3DXMATRIX	boneMat;
		D3DXMATRIX* combMatArray;
	};

	void	CreateBone();	//ボーンの生成
};