//---------------------------------------------------------------
//汎用クラス
//---------------------------------------------------------------
#include "Shot.h"

//追加include---------------------------------------------

namespace Shot
{
	//変更可----------------------------------------------
	//コンストラクタ
	Object::Object() : state(NONE)
	{

	}

	//----------------------------------------------------
	//初期化処理
	//----------------------------------------------------
	void		Object::Initialize()
	{
		this->activeCnt = 0;
		this->effectCnt = 0;


		this->angle = D3DXVECTOR3(90, 0, 0);
		this->size = D3DXVECTOR3(5, 5, 5);

		model.Load(TEXT("./data/Model/shot01.x"));
		explode.Load(TEXT("./data/Model/explodeX.x"));


		//弾が生きている状態になる
		this->state = ACTIVE;


		this->sphere = Sphere(this->pos, 10.0f);
	}

	//----------------------------------------------------
	//終了処理
	//----------------------------------------------------
	void		Object::Finalize()
	{
		model.Erase();
		explode.Erase();
	}

	//----------------------------------------------------
	//更新処理
	//----------------------------------------------------
	void		Object::UpDate()
	{
		//状態に応じて処理を変化
		switch (state)
		{
			//弾の移動処理
		case ACTIVE:
			this->pos += this->moveVec;
			this->angle.x  += 10;

			this->activeCnt++;
			if (this->activeCnt >= 240)
			{
				this->activeCnt = 0;
				this->angle.y = 0;

				this->state = EXPLODE;
			}
			break;
			//爆発処理
		case EXPLODE:

			this->size.x = sinf(2.0f * PI / 180.0f ) * effectCnt * 2.0f;
			this->size.y = cosf(2.0f * PI / 180.0f ) * effectCnt * 0.7f;
			this->size.z = sinf(2.0f * PI / 180.0f / 5.0f) * effectCnt * 3.0f;
			
			this->effectCnt++;
			if (effectCnt >= 60)
			{
				this->state = NONE;
			}
			break;
		case NONE:
			//なにもしない
			break;
		}

		//球の位置の更新
		this->sphere = Sphere(this->pos, 10.0f);
	}

	//----------------------------------------------------
	//描画処理
	//----------------------------------------------------
	void		Object::Render()
	{
		//マトリックスの計算
		D3DXMATRIX	mMove;
		D3DXMATRIX	mRot;
		D3DXMATRIX	mScale;

		D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
		D3DXMatrixRotationX(&mRot, D3DXToRadian(angle.x));
		D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
		D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

		world.mat = mScale * mRot * mMove;

		world.SetMatrix(D3DTS_WORLD);

		//弾の描画
		switch (state)
		{
		case ACTIVE:
			model.Render();		//弾の描画
			break;
		case EXPLODE:
			explode.Render();	//爆発の描画
		}
	}


	//追加メソッド----------------------------------------
	//あたり判定
	bool	Object::HitCheck(Box3D box)
	{
		//自身のボックスの用意
		Box3D	me = Box3D(pos.x, pos.y, pos.z, size.x, size.y, size.z);
		
		//相手のボックスの用意
		Box3D	you = Box3D(box.x, box.y, box.z, box.sizeX, box.sizeY, box.sizeZ);

		if (you.HitCheck(me))
		{
			return true;
		}

		return false;
	}


	//球体とのあたり判定
	bool	Object::HitSphere(Sphere& sp)
	{
		if (this->sphere.Hit(sp))
		{
			return true;
		}
		return false;
	}




	//変更不可--------------------------------------------
	//オブジェクトの生成
	Object*		Object::Create(bool flag)
	{
		if (!flag) { return nullptr; }
		MessageBox(NULL, TEXT("オブジェクトが生成されました"), TEXT("Shot"), MB_OK);
		Object*	obj = new Object;
		
		return new Object;
	}

	//オブジェクト破棄
	void		Object::Destroy()
	{
		MessageBox(NULL, TEXT("オブジェクトを破棄しました"), TEXT("Shot"), MB_OK);
		
		delete this;
	}
}
