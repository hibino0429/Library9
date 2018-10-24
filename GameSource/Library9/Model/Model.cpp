#include "Model.h"



//コンストラクタ
Model::Model() : m_pMesh(0), m_pMtrlBuf(0), m_texture(nullptr)
{
	pos = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(1, 1, 1);
}
//デストラクタ
Model::~Model()
{
	Erase();
}

//モデルの読み込み
void	Model::Load(LPCWSTR fileName)
{
	LibModel::Load(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh);
}

void	Model::Load(LPCSTR fileName)
{
	LibModel::Load(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh);
}

//モデルの解放
void	Model::Erase()
{
	if (m_pMesh != nullptr) { m_pMesh->Release(); m_pMesh = nullptr; }
	if (m_pMtrlBuf != nullptr) { m_pMtrlBuf->Release(); m_pMtrlBuf = nullptr; }

}

//モデルの描画
void	Model::Render()
{
	D3DMATERIAL9	mMaterial;

	//マテリアル情報を取り出す
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//テクスチャをマテリアルの数だけ用意

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//マテリアルのコピー
		LibModel::SetMaterial(&mMaterial);		//マテリアルのセット
		m_texture[i] = NULL;					//テクスチャなし

		//使用しているテクスチャがあれば読み込む
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//テクスチャをセットする
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		m_pMesh->DrawSubset(i);					//描画

		LibDGD::SetTexture(0, NULL);			//テクスチャの設定をもとに戻す
	}
}

void	Model::ZTexRender(ZTexture* zTex)
{
	D3DMATERIAL9	mMaterial;

	//マテリアル情報を取り出す
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//テクスチャをマテリアルの数だけ用意

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//マテリアルのコピー
		LibModel::SetMaterial(&mMaterial);		//マテリアルのセット
		m_texture[i] = NULL;					//テクスチャなし

		//使用しているテクスチャがあれば読み込む
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//テクスチャをセットする
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		zTex->SetEffectParam();
		zTex->BeginPass();
		m_pMesh->DrawSubset(i);					//描画
		zTex->EndPass();

		LibDGD::SetTexture(0, NULL);			//テクスチャの設定をもとに戻す
	}
}

void	Model::DepthRender(DepthTexture* depTex)
{
	D3DMATERIAL9	mMaterial;

	//マテリアル情報を取り出す
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//テクスチャをマテリアルの数だけ用意

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//マテリアルのコピー
		LibModel::SetMaterial(&mMaterial);		//マテリアルのセット
		m_texture[i] = NULL;					//テクスチャなし

												//使用しているテクスチャがあれば読み込む
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//テクスチャをセットする
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		depTex->SetMaterialDiffuse(D3DXVECTOR4(mMaterial.Diffuse.r, mMaterial.Diffuse.g, mMaterial.Diffuse.b, mMaterial.Diffuse.a));
		depTex->SetEffectParam();
		depTex->BeginPass();
		m_pMesh->DrawSubset(i);					//描画
		depTex->EndPass();

		LibDGD::SetTexture(0, NULL);			//テクスチャの設定をもとに戻す
	}
}




//仮--------------------
bool	Model::BoundingBox()
{
	DWORD numv, stride;
	LPDIRECT3DVERTEXBUFFER9	vb;
	BYTE*		pvertices;
	HRESULT		hr = S_OK;
	D3DXVECTOR3	lmin, lmax;

	numv = m_pMesh->GetNumVertices();		//頂点数
	stride = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファの取得
	if (FAILED(m_pMesh->GetVertexBuffer(&vb)))
	{
		MessageBox(NULL, TEXT("メッシュの頂点バッファ取得に失敗しました"), TEXT("GetVertexBuf"), MB_OK);
		return false;
	}

	vb->Lock(0, 0, (VOID**)&pvertices, 0);	//頂点バッファのロック
	if (FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices,
		numv, stride, &lmin, &lmax)))
	{
		MessageBox(NULL, TEXT("バウンディングボックスの作成に失敗しました"), TEXT("ComputBound"), MB_OK);
		return false;
	}

	LPD3DXMESH		tempMesh;
	//マテリアルのクローン
	m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), *LibDEV::GetDevice(), &tempMesh);

	minB = pos + lmin;
	maxB = pos + lmax;
	vb->Unlock();

	return true;
}


//クローンメッシュの生成
bool	Model::CloneModel()
{
	//頂点宣言
	const D3DVERTEXELEMENT9 vertexDecl[] =
	{
		{0, 0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0, 12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		{0, 20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		{ 0,32,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
		{ 0,44,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
		D3DDECL_END()
	};

	//クローンメッシュの生成
	if (FAILED(m_pMesh->CloneMesh(m_pMesh->GetOptions(), vertexDecl, *LibDEV::GetDevice(), &cloneMesh)))
	{
		MessageBoxA(NULL, "クローンメッシュの生成に失敗", "CloneMesh", MB_OK);
		return false;
	}
	return true;
}


//設定処理
void		Model::SetPos(const D3DXVECTOR3& pos)
{
	this->pos = pos;
}
void		Model::SetAngle(const D3DXVECTOR3& angle)
{
	this->angle = angle;
}
void		Model::SetSize(const D3DXVECTOR3& size)
{
	this->size = size;
}

//取得処理
D3DXVECTOR3	Model::GetPos()
{
	return D3DXVECTOR3(pos.x,pos.y,pos.z);
}
D3DXVECTOR3	Model::GetAngle()
{
	return D3DXVECTOR3(angle.x, angle.y, angle.z);
}
D3DXVECTOR3	Model::GetSize()
{
	return D3DXVECTOR3(size.x, size.y, size.z);
}
