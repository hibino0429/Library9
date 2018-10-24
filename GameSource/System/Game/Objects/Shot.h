#pragma once
//---------------------------------------------------------------
//汎用クラス	(名前変更)
//---------------------------------------------------------------
#include "../../../Library9/Function.h"

//追加include-------------------------
#include "../Effects/Explode.h"

namespace Shot
{
	class Object
	{
	public:
		//変更不可---------------------------------------
		static Object*	Create(bool flag);
		void			Destroy();
		Object();

		//基本処理
		void	Initialize();
		void	Finalize();
		void	UpDate();
		void	Render();


		//変更可-----------------------------------------
		//追加メソッド
		bool	HitCheck(Box3D box);

		bool	HitSphere(Sphere& sp);
		Sphere	sphere;		//球体の当たり判定

	public:

		//定数
		const float		PI = 3.14159f;

		//追加メンバ
		D3DXVECTOR3		pos;
		D3DXVECTOR3		angle;
		D3DXVECTOR3		size;

		D3DXVECTOR3		moveVec;

		int				activeCnt;
		int				effectCnt;

		enum State
		{
			ACTIVE,		//生きている状態
			EXPLODE,	//爆発している状態
			NONE,		//何もない状態
		};
		State			state;

	public:
		XFile::ModelX	model;
		XFile::ModelX	explode;

		Mat4X4::Matrix	world;

	};


}