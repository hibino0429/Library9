#pragma once
//---------------------------------------------------------------
//�ėp�N���X	(���O�ύX)
//---------------------------------------------------------------
#include "../../../Library9/Function.h"

//�ǉ�include-------------------------
#include "../Effects/Explode.h"

namespace Shot
{
	class Object
	{
	public:
		//�ύX�s��---------------------------------------
		static Object*	Create(bool flag);
		void			Destroy();
		Object();

		//��{����
		void	Initialize();
		void	Finalize();
		void	UpDate();
		void	Render();


		//�ύX��-----------------------------------------
		//�ǉ����\�b�h
		bool	HitCheck(Box3D box);

		bool	HitSphere(Sphere& sp);
		Sphere	sphere;		//���̂̓����蔻��

	public:

		//�萔
		const float		PI = 3.14159f;

		//�ǉ������o
		D3DXVECTOR3		pos;
		D3DXVECTOR3		angle;
		D3DXVECTOR3		size;

		D3DXVECTOR3		moveVec;

		int				activeCnt;
		int				effectCnt;

		enum State
		{
			ACTIVE,		//�����Ă�����
			EXPLODE,	//�������Ă�����
			NONE,		//�����Ȃ����
		};
		State			state;

	public:
		XFile::ModelX	model;
		XFile::ModelX	explode;

		Mat4X4::Matrix	world;

	};


}