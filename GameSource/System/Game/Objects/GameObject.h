#pragma once
#include "../../../Library9/Function.h"
#include "../../../Library9/Model/Model.h"
#include <string>

//--------------------------------------------------------------------------------
//ゲームオブジェクト
//--------------------------------------------------------------------------------
class GameObject
{

	//公開メソッド
public:
	GameObject();
	~GameObject();

	//取得処理
	Model&	GetModel();
	Mat4X4::Matrix& GetMatrix();
	Box3D&	GetBox3D();

	//設定処理
	void	SetModel(const Model& model);
	void	SetMatrix(const Mat4X4::Matrix& mat);
	void	SetHitBase(const Box3D& hitBox);

	//モデルに関して
	//モデルの生成
	void	CreateModel(const std::string& filePath,
						const D3DXVECTOR3& pos,
						const D3DXVECTOR3& angle,
						const D3DXVECTOR3& size);

	//モデルの描画
	void	ZTexRender(ZTexture* zTex);
	void	DepthRender(DepthTexture* depTex);

	//マトリックスに関して
	//マトリックス処理の実行
	void	MatrixProcess();

	//当たり判定ボックスに関して

	//非公開メソッド
private:
	
	//モデルの大きさと当たり判定の大きさを合わせる
	void	AdjustBox();

private:
	Model			model;		//モデル
	Mat4X4::Matrix	matrix;		//マトリックス
	Box3D			hitBase;	//当たり判定
};