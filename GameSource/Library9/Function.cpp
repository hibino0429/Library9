#include "Function.h"

#include <string>
#include <locale.h>
#include <atlstr.h>

DGD*	dgd = DGD::Instance();

//----------------------------------------------------------------
//画像の機能
//----------------------------------------------------------------
//Textureは、うまく動作しない
namespace Texture2
{
	Image::Image() : m_pSprite(NULL), m_pTexture(NULL) ,  surface(NULL),backBufSurface(NULL),backDepthSurface(NULL)
	{
		ZeroMemory(&center, sizeof(D3DXVECTOR3));
		ZeroMemory(&position, sizeof(D3DXVECTOR3));
		ZeroMemory(&color, sizeof(D3DXCOLOR));
		ZeroMemory(&rect, sizeof(RECT));
	}

	Image::~Image()
	{
		Destroy();
	}

	//スプライトの作成
	void	Image::CreateSprite()
	{
		if (FAILED(dgd->CreateSprite(&m_pSprite)))
		{
			MessageBox(NULL, TEXT("スプライトの生成に失敗しました"), TEXT("CreateSprite"), MB_OK);
			return;
		}
	}


	//テクスチャのロード
	void	Image::LoadTexture(LPCWSTR fileName)
	{
		if (FAILED(dgd->CretateTexture(fileName, &m_pTexture)))
		{
			MessageBox(NULL, TEXT("テクスチャロード失敗"), TEXT("LoadTexture"), MB_OK);
			return;
		}
		//スプライトの生成
		CreateSprite();
		//サーフェイスに画像ファイルを読み込む
		LoadSurface(fileName, NULL, NULL);
	}

	//テクスチャのロード
	void	Image::LoadTexture(LPCSTR fileName)
	{
		if (FAILED(dgd->CretateTexture(fileName, &m_pTexture)))
		{
			MessageBox(NULL, TEXT("テクスチャロード失敗"), TEXT("LoadTexture"), MB_OK);
			return;
		}
		//スプライトの生成
		CreateSprite();
		//サーフェイスに画像ファイルを読み込む
		LoadSurface(fileName, NULL, NULL);
	}

	//画像の破棄
	void	Image::Destroy()
	{
		if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }
		if (m_pSprite != NULL) { m_pSprite->Release(); m_pSprite = NULL; }

		if (surface != NULL){ surface->Release(); surface = NULL; }

		if (backBufSurface != NULL) { backBufSurface->Release(); backBufSurface = NULL; }
		if (backDepthSurface != NULL) { backDepthSurface->Release(); backDepthSurface = NULL; }
		//dgd->SetRenderTarget(0, backBufSurface);
		//dgd->SetDepthStencilSurface(backDepthSurface);

		
	}

	//色の設定
	void	Image::SetColor(D3DXCOLOR color)
	{
		this->color = color;
	}

	//中心位置の設定
	void	Image::SetCenter(D3DXVECTOR3 center)
	{
		this->center = center;
	}

	//配置位置の設定
	void	Image::SetPosition(D3DXVECTOR3 pos)
	{
		this->position = pos;
	}

	//範囲の設定
	void	Image::SetRect(Box2D box2D)
	{
		this->rect =
		{
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};
	}




	//画像の描画
	void	Image::Render(Box2D draw, Box2D src, D3DXCOLOR color)
	{
		RECT sr = {
			(LONG)src.x,
			(LONG)src.y,
			(LONG)src.x + (LONG)src.sizeX,
			(LONG)src.y + (LONG)src.sizeY
		};

		D3DXVECTOR3	pos = D3DXVECTOR3(draw.x, draw.y, 0);
		D3DXVECTOR3 center = D3DXVECTOR3(draw.sizeX, draw.sizeY, 0);

		//srcの大きさをdrawの大きさにする src/draw で倍率を取得
		//D3DXVECTOR2	scale;
		//scale.x = (float)src.sizeX / draw.sizeX * 2.0f;
		//scale.y = (float)src.sizeY / draw.sizeY * 2.0f;
		//D3DXVECTOR2	rotCenter(0, 0);
		//D3DXVECTOR2	drawPos(0, 0);

		////画像の表示する範囲をスケールで調整する
		//D3DXMATRIX	mWorld;
		//D3DXMatrixTransformation2D(&mWorld, nullptr, 0.0f, &scale, &rotCenter, 0.0f, &drawPos);

		
		//画像ソースの範囲を第二引数で指定する
		//
		if (SUCCEEDED(m_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
		{
			if (FAILED(m_pSprite->Draw(
				m_pTexture,
				&sr,
				&center,
				&pos,
				color		//色の乗算
			)))
			{
				MessageBox(NULL, TEXT("画像の描画に失敗しました"), TEXT("Render"), MB_OK);
				return;
			}
		}
		m_pSprite->End();
	}


	//テクスチャからサーフェイスを取得
	bool	Image::GetSurfaceLevel(UINT level)
	{
		LPDIRECT3DSURFACE9 surf;
		if (FAILED(m_pTexture->GetSurfaceLevel(0, &surf)))
		{
			MessageBox(NULL, TEXT("サーフェイスの取得に失敗"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}

		dgd->SetRenderTarget(0, &surf);

		return true;
	}


	
	//以下の処理はうまく動作しない
	//////////////////////////////////////////////////////////
	//サーフェイスの作成
	void	Image::CreateSurface(UINT width, UINT height)
	{
		if (!dgd->CreateOffScreenPlainSurface(width, height, D3DPOOL_SYSTEMMEM, &backBufSurface, NULL))
		{
			MessageBox(NULL, TEXT("サーフェイスの作成に失敗"), TEXT("CreateSurface"), MB_OK);
			return;
		}
	}

	//バックサーフェイスの取得
	void	Image::GetRenderTarget(UINT level)
	{
		dgd->GetRenderTarget(level, &backBufSurface);
	}
	//ステンシルバッファの取得
	void	Image::GetDepthStencilSurface()
	{
		dgd->GetDepthStencilSurface(&backDepthSurface);
	}

	//ステンシルバッファの作成
	void	Image::CreateStencilSurface(UINT width, UINT height)
	{
		if (!dgd->StencilBufCreate(&backDepthSurface, width, height))
		{
			MessageBox(NULL, TEXT("ステンシルバッファの作成に失敗しました"), TEXT("StencilBufCreate"), MB_OK);
			return;
		}
		//ステンシルバッファのセット
		dgd->SetDepthStencilSurface(&backDepthSurface);
	}

	//サーフェイスの描画
	void	Image::RenderSurface(IDirect3DSurface9* pSourceSurface,const RECT* pSourceRect,IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
	{
		dgd->SurfaceRender(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
	}




	//追加処理------------------------------------
	//画像の情報を受け取る
	bool	Image::GetImageInfo(LPCWSTR fileName)
	{
		if (FAILED(D3DXGetImageInfoFromFileW(
			fileName,
			&imageInfo
		)))
		{
			MessageBox(NULL, TEXT("画像の情報を受け取れませんでした"), TEXT("GetImageInfo"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::GetImageInfo(LPCTSTR fileName)
	{
		if (FAILED(D3DXGetImageInfoFromFileA(
			fileName,
			&imageInfo
		)))
		{
			MessageBox(NULL, TEXT("画像の情報を受け取れませんでした"), TEXT("GetImageInfo"), MB_OK);
			return false;
		}
		return true;
	}


	//画像のサーフェイスの取得
	bool	Image::CreatePlainSurface()
	{
		if (FAILED(dgd->CreateOffScreenPlainSurface(
			imageInfo.Width, imageInfo.Height,
			D3DPOOL_DEFAULT, &surface, NULL
		)))
		{
			MessageBox(NULL, TEXT("画像のサーフェイスの取得に失敗しました"), TEXT("CreatePlainSurface"), MB_OK);
			return false;
		}
		return true;
	}

	

	//サーフェイスに画像を読み込ませる
	bool	Image::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY* palette, const RECT* rect, LPCWSTR srcFile, const RECT* srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO* srcInfo)
	{
		if (FAILED(D3DXLoadSurfaceFromFileW(
			surface,
			palette,
			rect,
			srcFile,
			srcRect,
			filter,
			colorKey,
			srcInfo
		)))
		{
			MessageBox(NULL, TEXT("サーフェイスに画像を読み込みできませんでした"), TEXT("LoadSurfaceFromFile"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::LoadSurfaceFromFile(LPDIRECT3DSURFACE9 surface, const PALETTEENTRY * palette, const RECT * rect, LPCTSTR srcFile, const RECT * srcRect, DWORD filter, D3DCOLOR colorKey, D3DXIMAGE_INFO * srcInfo)
	{
		if (FAILED(D3DXLoadSurfaceFromFileA(
			surface,
			palette,
			rect,
			srcFile,
			srcRect,
			filter,
			colorKey,
			srcInfo
		)))
		{
			MessageBox(NULL, TEXT("サーフェイスに画像を読み込みできませんでした"), TEXT("LoadSurfaceFromFile"), MB_OK);
			return false;
		}
		return true;
	}

	//サーフェイスに画像ファイルを読み込む
	bool	Image::LoadSurface(LPCWSTR fileName,const RECT* drawRect,const RECT* srcRect)
	{
		//画像情報の取得
		this->GetImageInfo(fileName);
		//サーフェイスの作成
		this->CreatePlainSurface();
		//サーフェイスに画像を読み込む
		if (FAILED(LoadSurfaceFromFile(
			surface,
			NULL,
			drawRect,
			fileName,
			srcRect,
			D3DX_FILTER_NONE,
			0, NULL
		)))
		{
			MessageBox(NULL, TEXT("サーフェイルの読み込み失敗"), TEXT("LoadSurface"), MB_OK);
			return false;
		}
		return true;
	}

	bool Image::LoadSurface(LPCTSTR fileName, const RECT * drawRect, const RECT * srcRect)
	{
		//画像情報の取得
		this->GetImageInfo(fileName);
		//サーフェイスの作成
		this->CreatePlainSurface();
		//サーフェイスに画像を読み込む
		if (FAILED(LoadSurfaceFromFile(
			surface,
			NULL,
			drawRect,
			fileName,
			srcRect,
			D3DX_FILTER_NONE,
			0, NULL
		)))
		{
			MessageBox(NULL, TEXT("サーフェイルの読み込み失敗"), TEXT("LoadSurface"), MB_OK);
			return false;
		}
		return true;
	}


	//画像の回転
	void	Image::Rotation(float angle)
	{
		D3DXMATRIX	mRot;

		D3DXMatrixRotationY(&mRot, D3DXToRadian(angle));

		m_pSprite->SetTransform(&mRot);
	}

	//画像の拡大
	void	Image::Scale(D3DXVECTOR2 scale)
	{
		D3DXMATRIX	mScale;

		D3DXMatrixScaling(&mScale, scale.x, scale.y, 0);

		m_pSprite->SetTransform(&mScale);
	}

}


//----------------------------------------------------------------
//フォントの機能
//----------------------------------------------------------------
namespace Text
{
	Font::Font() : pFont(NULL)
	{

	}

	Font::~Font()
	{
		Destory();
	}

	//フォントの生成
	bool	Font::Create(LPCWSTR fontName, float width, float height)
	{
		if (FAILED(dgd->CreateFont2D(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			&pFont
		)))
		{
			MessageBox(NULL, TEXT("フォントの生成に失敗"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
	bool	Font::Create(LPCSTR fontName, float width, float height)
	{
		if (FAILED(dgd->CreateFont2DA(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			&pFont
		)))
		{
			MessageBoxA(NULL, "フォントの生成に失敗しました", "Create", MB_OK);
			return false;
		}
		return true;
	}

	//フォントの破棄
	void	Font::Destory()
	{
		if (pFont != NULL) { pFont->Release(); pFont = NULL; }
	}

	//フォントの描画
	void	Font::Render(LPCWSTR string, Box2D box2D, D3DXCOLOR color)
	{
		//表示範囲はRECT型
		RECT rc = {
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};

		pFont->DrawTextW(
			NULL,
			string,		//描画テキスト
			-1,			//全て表示
			&rc,		//表示範囲
			DT_LEFT,	//左寄せ
			color		//色
		);
	}
	void	Font::Render(LPCSTR string, Box2D box2D, D3DXCOLOR color)
	{
		//表示範囲はRECT型
		RECT rc = {
			(LONG)box2D.x,
			(LONG)box2D.y,
			(LONG)box2D.x + (LONG)box2D.sizeX,
			(LONG)box2D.y + (LONG)box2D.sizeY
		};

		pFont->DrawTextA(
			NULL,
			string,		//描画テキスト
			-1,			//全て表示
			&rc,		//表示範囲
			DT_LEFT,	//左寄せ
			color		//色
		);
	}
}



//----------------------------------------------------------------
//モデルの機能
//----------------------------------------------------------------
namespace XFile
{
	int ModelX::modelNum = -1;

	ModelX::ModelX() : m_pMesh(0),m_pMtrlBuf(0),m_texture(nullptr)
	{
		pos = D3DXVECTOR3(0, 0, 0);
		angle = D3DXVECTOR3(0, 0, 0);
		size = D3DXVECTOR3(1, 1, 1);
		modelNum++;
	}
	ModelX::~ModelX()
	{
		Erase();
	}

	//モデルの読み込み
	bool	ModelX::Load(LPCWSTR fileName)
	{
		if (FAILED(dgd->LoadModel(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh)))
		{
			MessageBox(NULL, TEXT("モデルの読み込み失敗"), TEXT("Load"), MB_OK);
			return false;
		}
		return true;
	}
	bool	ModelX::Load(LPCSTR fileName)
	{
		if (FAILED(dgd->LoadModel(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh)))
		{
			MessageBoxA(NULL, "モデルの読み込み失敗", "Load", MB_OK);
			return false;
		}
		return true;
	}

	//モデルの解放
	void	ModelX::Erase()
	{
		if (m_pMesh != nullptr) { m_pMesh->Release(); m_pMesh = nullptr; }
		if (m_pMtrlBuf != nullptr) { m_pMtrlBuf->Release(); m_pMtrlBuf = nullptr; }
		
	}

	//モデルの描画
	void	ModelX::Render()
	{
		D3DMATERIAL9	mMaterial;

		//マテリアル情報を取り出す
		D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
		m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//テクスチャをマテリアルの数だけ用意

		for (DWORD i = 0; i < m_MtrlNum; i++)
		{
			mMaterial = mD3DXMaterials[i].MatD3D;	//マテリアルのコピー
			dgd->SetMaterial(&mMaterial);			//マテリアルのセット
			m_texture[i] = NULL;					//テクスチャなし

			//使用しているテクスチャがあれば読み込む
			if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
			{
				if (FAILED(dgd->CretateTexture(mD3DXMaterials[i].pTextureFilename, &m_texture[i])))
				{
					MessageBox(NULL, TEXT("失敗しました"), TEXT("失敗してます"), MB_OK);
					return;
				}
				LibDGD::SetTexture(0, m_texture[i]);	//テクスチャをセットする
			} 
			if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
			delete m_texture[i];


			m_pMesh->DrawSubset(i);					//描画

			LibDGD::SetTexture(0, NULL);			//テクスチャの設定をもとに戻す
		}
	}

	

	
	//仮--------------------
	bool	ModelX::BoundingBox()
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
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), dgd->m_pD3DDevice, &tempMesh);

		minB = pos + lmin;
		maxB = pos + lmax;
		vb->Unlock();
		
		return true;
	}
}


////////////////////////////////////////////////////////////////////
//フォントの処理
namespace LibFont
{
	bool	Create(LPCWSTR fontName, float width, float height,LPD3DXFONT* pFont)
	{
		if (FAILED(dgd->CreateFont2D(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			pFont
		)))
		{
			MessageBox(NULL, TEXT("フォントの生成に失敗"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
	bool	Create(LPCSTR fontName, float width, float height, LPD3DXFONT* pFont)
	{
		if (FAILED(dgd->CreateFont2DA(
			height,
			width,
			FW_REGULAR,
			NULL,
			FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			fontName,
			pFont
		)))
		{
			MessageBox(NULL, TEXT("フォントの生成に失敗"), TEXT("Create"), MB_OK);
			return false;
		}
		return true;
	}
}

//テクスチャの処理
namespace LibTexture
{
	//画像の生成処理
	void	Create(LPCWSTR fileName, LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex)) { return; }
	}
	void	Create(LPCSTR fileName, LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex)) { return; }
	}


	//スプライトの作成
	void	CreateSprite(LPD3DXSPRITE* sprite)
	{
		if (FAILED(dgd->CreateSprite(sprite)))
		{
			MessageBox(NULL, TEXT("スプライトの生成に失敗しました"), TEXT("CreateSprite"), MB_OK);
			return;
		}
	}

	//画像のサーフェイスの取得
	bool	CreatePlainSurface(D3DXIMAGE_INFO* imageInfo,LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED(dgd->CreateOffScreenPlainSurface(
			imageInfo->Width, imageInfo->Height,
			D3DPOOL_DEFAULT, surface, NULL
		)))
		{
			MessageBox(NULL, TEXT("画像のサーフェイスの取得に失敗しました"), TEXT("CreatePlainSurface"), MB_OK);
			return false;
		}
		return true;
	}

	//サーフェイスの描画
	void	RenderSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDistinationSurface, const POINT* pDestPoint)
	{
		dgd->SurfaceRender(pSourceSurface, pSourceRect, pDistinationSurface, pDestPoint);
	}

	//サーフェイスの作成
	void	CreateSurface(UINT width, UINT height, LPDIRECT3DSURFACE9* backBufSurface)
	{
		if (!dgd->CreateOffScreenPlainSurface(width, height, D3DPOOL_SYSTEMMEM, backBufSurface, NULL))
		{
			MessageBox(NULL, TEXT("サーフェイスの作成に失敗"), TEXT("CreateSurface"), MB_OK);
			return;
		}
	}

	//テクスチャからサーフェイスを取得
	bool	GetSurfaceLevel(UINT level,LPDIRECT3DTEXTURE9* pTex,LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED((*pTex)->GetSurfaceLevel(level, surface)))
		{
			MessageBox(NULL, TEXT("サーフェイスの取得に失敗"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}
		return true;
	}
}

//モデルの処理
namespace LibModel
{
	//ロード処理
	void	Load(LPCWSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
	{
		if (!dgd->LoadModel(fileName, mtrlBuf, numMtrl, mesh))
		{
			MessageBox(NULL, TEXT("モデルのロードに失敗しました"), TEXT("Load"), MB_OK);
			return;
		}
	}
	void	Load(LPCSTR fileName, LPD3DXBUFFER* mtrlBuf, DWORD* numMtrl, LPD3DXMESH* mesh)
	{
		if (!dgd->LoadModel(fileName, mtrlBuf, numMtrl, mesh))
		{
			MessageBoxA(NULL, "モデルのロードに失敗しました", "Load", MB_OK);
			return;
		}
	}

	//マテリアルのセット
	void	SetMaterial(D3DMATERIAL9* material)
	{
		dgd->SetMaterial(material);
	}
}

//Matrixの処理
namespace LibMatrix
{
	void	SetMatrix(D3DTRANSFORMSTATETYPE type, D3DXMATRIX* mat)
	{
		dgd->SetMatrixToRender(type, mat);
	}
}


//シェーダの処理
namespace LibShader
{
	//シェーダファイルの読み込み
	bool	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		if (!dgd->LoadEffectFile(fileName, pEffect, pErr)) { return false; }
		return true;
	}
	bool	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		if (!dgd->LoadEffectFile(fileName, pEffect, pErr)) { return false; }
		return true;
	}
}


//-----------------------------------------------------------
//ビルボードの機能
//Vertexでテクスチャを作成
//-----------------------------------------------------------
namespace VertexBuf
{
	//コンストラクタ
	Billboard::Billboard() : m_pVB(NULL),m_pTexture(NULL)
	{
		
	}

	//デストラクタ
	Billboard::~Billboard()
	{
		Destroy();
	}



	//ビルボードの生成
	bool	Billboard::Create()
	{
		//頂点バッファの生成
		if(FAILED(dgd->CreateVertexBuf(
			4 * sizeof(Vertex),	//頂点バッファの数
			VertexFVF,			//頂点バッファのFVFフォーマット
			&m_pVB
		)))
		{
			MessageBox(NULL, TEXT("頂点の生成に失敗"), TEXT("CreateVertexBuf"), MB_OK);
			return false;
		}

		return true;
	}


	//頂点バッファに張り付ける画像の読み込み
	bool	Billboard::LoadVertexTex(LPCWSTR fileName)
	{
		if (!dgd->CretateTexture(fileName, &m_pTexture))
		{
			MessageBox(NULL, TEXT("画像の読み込みに失敗しました"), TEXT("LoadVertexTex"), MB_OK);
			return false;
		}
		return true;
	}

	bool	Billboard::LoadVertexTexA(LPCSTR fileName)
	{
		if (!dgd->CretateTexture(fileName, &m_pTexture))
		{
			MessageBox(NULL, TEXT("画像の読み込みに失敗しました"), TEXT("LoadVertexTex"), MB_OK);
			return false;
		}
		return true;
	}

	//頂点バッファの中身を埋める
	void	Billboard::SetVertex()
	{
		Vertex* v;

		//頂点のロック
		if (FAILED(m_pVB->Lock(0, 0, (void**)&v, 0)))
		{
			MessageBox(NULL, TEXT("ロックに失敗しました"), TEXT("Lock"), MB_OK);
			return;
		}


		//頂点データ : 頂点の座標値の設定
		v[0].pos = D3DXVECTOR3(-1.5f, 1.5f, 0);		//頂点１
		v[1].pos = D3DXVECTOR3(1.5f, 1.5f, 0);		//頂点２
		v[2].pos = D3DXVECTOR3(-1.5f, -1.5f, 0);	//頂点３
		v[3].pos = D3DXVECTOR3(1.5f, -1.5f, 0);		//頂点４

		//頂点データ : 頂点の色
		v[0].diffuse = D3DXCOLOR(0, 1, 1, 1);
		v[1].diffuse = D3DXCOLOR(1, 0, 1, 1);
		v[2].diffuse = D3DXCOLOR(1, 0.5f, 0, 1);
		v[3].diffuse = D3DXCOLOR(0.5f, 1, 1, 1);

		//頂点のテクスチャの座標
		v[0].tex = D3DXVECTOR2(0, 0);
		v[1].tex = D3DXVECTOR2(1, 0);
		v[2].tex = D3DXVECTOR2(0, 1);
		v[3].tex = D3DXVECTOR2(1, 1);

		m_pVB->Unlock();


		//テクスチャステージの設定
		//仮の設定
		//頂点を設定した後で呼び出す
		//テクスチャステージの設定
		
	}

	//頂点1つの設定
	//void	Billboard::SetVertex(int number, D3DXVECTOR3 pos, D3DXVECTOR2 tex, D3DXCOLOR color)
	//{
	//	
	//	//番号が頂点の数以内
	//	if (number < 0 && 3 < number) 
	//	{
	//		MessageBox(NULL, TEXT("当てはまる頂点がありません"), TEXT("SetVertex"), MB_OK);
	//		return; 
	//	}
	//	
	//	//頂点の設定
	//
	//	if (FAILED(m_pVB->Lock(0, 0, (void**)&vertex, 0)))
	//	{
	//		MessageBox(NULL, TEXT("頂点のロックに失敗しました"), TEXT("Lock"), MB_OK);
	//		return;
	//	}

	//	//頂点の座標値の設定
	//	vertex[number].pos = pos;
	//	vertex[number].diffuse = color;
	//	vertex[number].tex = tex;

	//	m_pVB->Unlock();
	//}


	//ビルボードの破棄
	void	Billboard::Destroy()
	{
		if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }
		if (m_pVB != NULL) { m_pVB->Release(); m_pVB = NULL; }
		
	}

	//ビルボードの描画
	void	Billboard::Render()
	{
		dgd->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		dgd->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		dgd->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		dgd->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		dgd->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		dgd->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		//テクスチャをパイプラインにセット
		dgd->SetVertexTexture(0, m_pTexture);

		//頂点バッファの描画
		dgd->SetVertexBufRender(0, m_pVB, 0, sizeof(Vertex));

		//FVFフォーマットの設定
		dgd->SetVertexFVF(VertexFVF);

		//描画
		dgd->VertexRender(D3DPT_TRIANGLESTRIP, 0, 2);
		
		dgd->SetVertexTexture(0, NULL);
	}


	void	Billboard::SetMatrix()
	{
		D3DXMATRIX	mMove;
		D3DXMATRIX	mRot;
		D3DXMATRIX	mScale;

		D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
		D3DXMatrixRotationY(&mRot, D3DXToRadian(angle.y));
		D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

		
	}
}




//--------------------------------------------------------------------------
//マトリックス機能
//--------------------------------------------------------------------------
namespace Mat4X4
{
	Matrix::Matrix()
	{
		D3DXMatrixIdentity(&mat);
	}


	//マトリックスをセットする
	void	Matrix::SetMatrix(D3DTRANSFORMSTATETYPE type)
	{
		dgd->SetMatrixToRender(type, &mat);
	}
}



//------------------------------------------------------
//シェーダ関連処理
//------------------------------------------------------
namespace Effect
{
	//コンストラクタ
	Shader::Shader() : m_pEffect(NULL),m_pErr(NULL)
	{

	}

	//デストラクタ
	Shader::~Shader()
	{
		if (m_pEffect != NULL) { m_pEffect->Release(); m_pEffect = NULL; }
		if (m_pErr != NULL) { m_pErr->Release(); m_pErr = NULL; }
	}

	//ロード処理
	void	Shader::Load(LPCWSTR fileName)
	{
		if (FAILED(dgd->LoadEffectFile(fileName, &m_pEffect, m_pErr)))
		{
			MessageBox(NULL, TEXT("ロードに失敗"), TEXT("EffectFile"), MB_OK);
			return;
		}
		else
		{
			m_hTechnique	= m_pEffect->GetTechniqueByName("TShader");
			m_hmWVP			= m_pEffect->GetParameterByName(NULL, "mWVP");
			m_hmWIT			= m_pEffect->GetParameterByName(NULL, "mWIT");
			m_hvLightDir	= m_pEffect->GetParameterByName(NULL, "vLightDir");
			m_hvCol			= m_pEffect->GetParameterByName(NULL, "vColor");	
		}
	}
	void	Shader::Load(LPCSTR fileName)
	{
		if (FAILED(dgd->LoadEffectFile(fileName, &m_pEffect, m_pErr)))
		{
			MessageBoxA(NULL, "シェーダファイルのロードに失敗", "Load", MB_OK);
			return;
		}
		else
		{
			m_hTechnique = m_pEffect->GetTechniqueByName("TShader");
			m_hmWVP = m_pEffect->GetParameterByName(NULL, "mWVP");
			m_hmWIT = m_pEffect->GetParameterByName(NULL, "mWIT");
			m_hvLightDir = m_pEffect->GetParameterByName(NULL, "vLightDir");
			m_hvCol = m_pEffect->GetParameterByName(NULL, "vColor");
		}
	}
	
	//テクニック名の設定
	void	Shader::SetTechnique(const char* techniqueName)
	{
		m_hTechnique = m_pEffect->GetTechniqueByName(techniqueName);
	}
	//射影変換行列名の設定
	void	Shader::SetProjectViewMatrixName(const char* WVPName)
	{
		m_hmWVP = m_pEffect->GetParameterByName(NULL, WVPName);
	}
	//ワールド変換行列名の設定
	void	Shader::SetWorldMatrixName(const char* WITName)
	{
		m_hmWIT = m_pEffect->GetParameterByName(NULL, WITName);
	}
	//ライトの方向名の設定
	void	Shader::SetLightDirName(const char* lightDirName)
	{
		m_hvLightDir = m_pEffect->GetParameterByName(NULL, lightDirName);
	}
	//色の名前の設定
	void	Shader::SetColorName(const char* colorName)
	{
		m_hvCol = m_pEffect->GetParameterByName(NULL, colorName);
	}

	//シェーダデバイスのロスト
	void	Shader::DeviceLost()
	{
		if (m_pEffect != NULL) { m_pEffect->OnLostDevice(); }
	}
	//シェーダデバイスの復元
	void	Shader::DeviceReset()
	{
		if (m_pEffect != NULL) { m_pEffect->OnResetDevice(); }
	}

	//シェーダファイルの設定
	void	Shader::Set()
	{
		//ローカル - 射影変換行列
		D3DXMATRIX	playerMat;		//プレイヤーのワールドマトリックス
		D3DXMATRIX	worldMat;		//ワールドマトリックス
		D3DXMatrixInverse(&playerMat, NULL, &worldMat);
		D3DXMatrixTranspose(&playerMat, &worldMat);

		//ローカル - 射影変換行列
		D3DXMATRIX	cameraView, cameraProj;
		playerMat = worldMat * cameraView * cameraProj;

		//ライトの方向
		D3DXVECTOR4	lightPos(0, 0, 0, 1);
		m_pEffect->SetVector(NULL, &lightPos);

	}

	//シェーダの描画
	void	Shader::Render()
	{

		if (m_pEffect == NULL) { return; }
		
		//シェーダの設定
		m_pEffect->SetTechnique(m_hTechnique);
		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);
		dgd->SetVertexFVF(D3DFVF_XYZ | D3DFVF_NORMAL);

		Set();
		
		//描画
		m_pEffect->End();
	}

	//位置・マトリックスの設定
	void	Shader::SetMatrix(D3DXMATRIX* mat)
	{
		m_pEffect->SetMatrix(NULL, mat);
	}
	void	Shader::SetVector(D3DXVECTOR4* vec)
	{
		m_pEffect->SetVector(NULL, vec);
	}
	void	Shader::SetMatrix(D3DXHANDLE handle, D3DXMATRIX* mat)
	{
		m_pEffect->SetMatrix(handle, mat);
	}
	void	Shader::SetVector(D3DXHANDLE handle, D3DXVECTOR4* vec)
	{
		m_pEffect->SetVector(handle, vec);
	}


	//シェーダのパラメータ設定
	//シェーダのテクニックの設定
	D3DXHANDLE	Shader::GetParamTechnique(const char* technique)
	{
		return m_pEffect->GetTechniqueByName(technique);
	}
	//シェーダの変数の設定
	D3DXHANDLE	Shader::GetParameterName(const char* shaderName)
	{
		return m_pEffect->GetParameterByName(NULL, shaderName);
	}

	//テクスチャの設定
	bool	Shader::SetParamTexture(const char* texName,LPDIRECT3DTEXTURE9 tex)
	{
		if (FAILED(m_pEffect->SetTexture(texName, tex)))
		{
			MessageBox(NULL, TEXT("テクスチャをシェーダにセットできません"), TEXT("SetParamTexture"), MB_OK);
			return false;
		}
		return true;
	}


	//描画関係
	void	Shader::BeginPass(UINT pass)
	{
		m_pEffect->BeginPass(pass);
	}
	void	Shader::EndPass()
	{
		m_pEffect->EndPass();
	}
	void	Shader::Begin(UINT* pass,DWORD flags)
	{
		m_pEffect->Begin(pass,flags);
	}
	void	Shader::End()
	{
		m_pEffect->End();
	}
}


//-------------------------------------------------------
//複数のオブジェクト共通の機能
//-------------------------------------------------------
namespace LibDGD
{
	//レンダリングパイプラインにセット
	void	SetRenderState(D3DRENDERSTATETYPE type, DWORD value)
	{
		dgd->SetRenderState(type, value);
	}

	//テクスチャステージステート
	void	SetTexStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
	{
		dgd->SetTextureStageState(stage, type, value);
	}

	//テクスチャのラッピングモードのセット
	void	SetTexSamplerState(DWORD stage, D3DSAMPLERSTATETYPE type, DWORD value)
	{
		dgd->SetSamplerState(stage, type, value);
	}

	//頂点バッファのストリームソースをセット
	void	SetStreamSource(UINT streamNum, IDirect3DVertexBuffer9* vertexBuf, UINT offsetBuf, UINT stride)
	{
		dgd->SetVertexBufRender(streamNum, vertexBuf, offsetBuf, stride);
	}

	//頂点バッファのFVFのセット
	void	SetFVF(DWORD fvf)
	{
		dgd->SetVertexFVF(fvf);
	}

	//頂点バッファの描画
	void	DrawPrimitive(D3DPRIMITIVETYPE renderType, UINT startVertex, UINT primitiveNum)
	{
		dgd->VertexRender(renderType, startVertex, primitiveNum);
	}

	//頂点バッファの設定
	bool	CreateVertexBuffer(UINT len, DWORD fvf, IDirect3DVertexBuffer9** vertexBuf)
	{
		if (FAILED(dgd->CreateVertexBuf(
			len,
			fvf,
			vertexBuf
		)))
		{
			MessageBox(NULL, TEXT("頂点バッファの失敗"), TEXT("CreateVertexBuffer"), MB_OK);
			return false;
		}
		return true;
	}
	//頂点デコレーションの作成
	void	CreateVertexDeclaration(const D3DVERTEXELEMENT9* decl, LPDIRECT3DVERTEXDECLARATION9 pDecl)
	{
		if (!dgd->CreateVertexDecration(decl, pDecl)) { return; }
	}

	//テクスチャの読み込み(VertexBuf用)
	bool	CreateTexVertexBuf(LPCTSTR fileName,LPDIRECT3DTEXTURE9* pTex)
	{
		if (!dgd->CretateTexture(fileName, pTex))
		{
			return false;
		}
		return true;
	}

	//テクスチャ画像の読み込み
	bool	CreateTextureEx(LPCWSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* pPalette, LPDIRECT3DTEXTURE9* texture)
	{
		if (FAILED(dgd->CreateTextureEx(
			fileName, 
			width,
			height,
			colorKey,
			pSrcInfo,
			pPalette,
			texture
		)))
		{
			MessageBox(NULL, TEXT("テクスチャの読み込みに失敗しました"), TEXT("CreateTexture"), MB_OK);
			return false;
		}
		return true;
	}

	bool CreateTextureEx(LPCTSTR fileName, UINT width, UINT height, D3DCOLOR colorKey, D3DXIMAGE_INFO * pSrcInfo, PALETTEENTRY * pPalette, LPDIRECT3DTEXTURE9 * texture)
	{
		if (FAILED(dgd->CreateTextureEx(
			fileName,
			width,
			height,
			colorKey,
			pSrcInfo,
			pPalette,
			texture
		)))
		{
			MessageBox(NULL, TEXT("テクスチャの読み込みに失敗しました"), TEXT("CreateTexture"), MB_OK);
			return false;
		}
		return true;
	}


	//テクスチャをパイプラインにセット
	void	SetTexture(DWORD number, LPDIRECT3DTEXTURE9 m_pTex)
	{
		dgd->SetVertexTexture(number, m_pTex);
	}

	//ビューとステンシルのクリア
	bool	ViewAndStencilClear()
	{
		if (!dgd->ViewAndStencilClear())
		{
			return false;
		}
		return true;
	}

	//バックシーンのクリア
	void	SceneClear()
	{
		dgd->ViewAndStencilClear();
	}

	//Zバッファのクリア
	void	ZBufClear()
	{
		dgd->ZBufClear();
	}

	//ビューポートの設定
	bool	SetViewPort(D3DVIEWPORT9* viewport)
	{
		if (!dgd->SetViewPort(viewport)) { return false; }
		return true;
	}

	//ライトのセット
	void	SetLight(int number, D3DLIGHT9* pLight)
	{
		dgd->SetLight(number, pLight);
	}
	//ライトを使用するかのセット
	void	SetUseLight(int number, bool useFlag)
	{
		dgd->LightEnable(number, useFlag);
	}

	//描画の開始
	bool	BeginRender()
	{
		if (dgd->BeginRender())
		{
			return true;
		}
		return false;
	}
	//描画の終了
	void	EndRender()
	{
		dgd->EndRender();
	}
	//描画の反映
	void	PresentRender()
	{
		dgd->PresentRender();
	}

	//シャドウマップ関係
	//テクスチャの生成
	void	CreateTexture(UINT width, UINT height, LPDIRECT3DTEXTURE9* tex)
	{
		dgd->TextureCreate(tex, width, height);
	}
	//テクスチャからサーフェイスを取得
	bool	GetSurfaceLevel(UINT level, LPDIRECT3DTEXTURE9* pTex, LPDIRECT3DSURFACE9* surface)
	{
		if (FAILED((*pTex)->GetSurfaceLevel(level, surface)))
		{
			MessageBox(NULL, TEXT("サーフェイスの取得に失敗"), TEXT("GetSurfaceLevel"), MB_OK);
			return false;
		}
		return true;
	}
	//深度バッファの作成
	void	CreateDepthStencilSurface(UINT width,UINT height,LPDIRECT3DSURFACE9* surface)
	{
		if (!dgd->StencilBufCreate(surface, width, height))
		{
			return;
		}
	}
	void	CreateDepthStencilSurface(UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE type, DWORD quality, LPDIRECT3DSURFACE9* surf)
	{
		if (!dgd->StencilBufCreate(surf, width, height, format, type, quality))
		{
			return;
		}
	}

	//レンダリングターゲットの取得
	void	GetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
	{
		dgd->GetRenderTarget(targetIndex, surface);
	}
	//深度バッファの取得
	void	GetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
	{
		dgd->GetDepthStencilSurface(surface);
	}

	//レンダリングターゲットの設定
	void	SetRenderTarget(DWORD targetIndex, LPDIRECT3DSURFACE9* surface)
	{
		dgd->SetRenderTarget(targetIndex, surface);
	}
	//深度バッファの設定
	void	SetDepthStencilSurface(LPDIRECT3DSURFACE9* surface)
	{
		dgd->SetDepthStencilSurface(surface);
	}
	//頂点シェーダの設定
	void	SetVertexShader(LPDIRECT3DVERTEXSHADER9* pShader)
	{
		if (!dgd->SetVertexShader(pShader))
		{
			MessageBoxA(NULL, "バーテックスシェーダの設定に失敗しました", "SetVertexShader", MB_OK);
			return;
		}
	}
	//ピクセルシェーダの設定
	void	SetPixelShader(LPDIRECT3DPIXELSHADER9* pShader)
	{
		dgd->SetPixelShader(pShader);
	}

	//--------------------------------------
	//シェーダ関連の処理
	//シェーダファイルの読み込み
	void	LoadShaderFile(LPCWSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		dgd->LoadEffectFile(fileName, pEffect, pErr);
	}
	void	LoadShaderFile(LPCSTR fileName, LPD3DXEFFECT* pEffect, LPD3DXBUFFER pErr)
	{
		dgd->LoadEffectFile(fileName, pEffect, pErr);
	}

	//頂点シェーダのハンドルを生成
	void	CreateVertexShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DVERTEXSHADER9* shaderHander)
	{
		if (!dgd->CreateVertexShader(pShader, func, shaderHander))
		{
			return;
		}
	}
	//ピクセルシェーダのハンドルを生成
	void	CreatePixelShader(LPD3DXBUFFER pShader, DWORD* func, LPDIRECT3DPIXELSHADER9* shaderHandler)
	{
		if (!dgd->CreatePixelShader(pShader, func, shaderHandler))
		{
			return;
		}
	}


	//追加の仮処理
	void	SetVertexBuf(UINT num,IDirect3DVertexBuffer9* verBuf,UINT size,UINT zero)
	{
		dgd->SetVertexBufRender(num, verBuf, size, zero);
	}
	void	VertexRender(D3DPRIMITIVETYPE type,UINT start,UINT num)
	{
		dgd->VertexRender(type, start, num);
	}
}



//--------------------------------------------------
//Direct3DDeviceの処理
//--------------------------------------------------
namespace LibDEV
{
	//デバイスの初期化
	HRESULT	InitDevice(HWND hWnd, BOOL isFullScreen, int clientWidth, int clientHeight)
	{
		if (FAILED(dgd->DeviceInit(hWnd, isFullScreen, clientWidth, clientHeight)))
		{
			return E_FAIL;
		}
		return S_OK;
	}

	//デバイスの解放
	void	FinalDevice()
	{
		dgd->DeviceFinal();
	}

	//デバイスを渡す
	LPDIRECT3DDEVICE9* GetDevice()
	{
		return &dgd->m_pD3DDevice;
	}
}