#pragma once

#include "../Function.h"
#include "../../System/ShaderSystem/ZTexture.h"
#include "../../System/ShaderSystem/DepthTex.h"


//----------------------------------------------------
//モデルのクラス
//----------------------------------------------------
class Model
{
public:
	Model();
	~Model();

	//引数1:モデルのファイルパス
	void		Load(LPCWSTR);		//モデルの読み込み
	void		Load(LPCSTR);
	void		Erase();			//モデルの解放
	void		Render();			//モデルの描画

	void		ZTexRender(ZTexture* zTex);
	void		DepthRender(DepthTexture* depTex);

	//設定処理
	void		SetPos(const D3DXVECTOR3& pos);
	void		SetAngle(const D3DXVECTOR3& angle);
	void		SetSize(const D3DXVECTOR3& size);

	//取得処理
	D3DXVECTOR3	GetPos();
	D3DXVECTOR3	GetAngle();
	D3DXVECTOR3	GetSize();

private:
	bool		BoundingBox();		//モデルのあたり判定

	bool		CloneModel();		//モデルの再作成

private:
	//Xファイル情報
	LPD3DXMESH			m_pMesh;		//メッシュのインターフェイス
	LPD3DXBUFFER		m_pMtrlBuf;		//メッシュのマテリアル
	DWORD				m_MtrlNum;		//マテリアルの数

public:
	LPDIRECT3DTEXTURE9*	m_texture;		//テクスチャ情報

public:
	D3DXVECTOR3			pos;
	D3DXVECTOR3			angle;
	D3DXVECTOR3			size;
private:
	D3DXVECTOR3			minB;
	D3DXVECTOR3			maxB;

	LPD3DXMESH			cloneMesh;		//クローンメッシュ
public:

};