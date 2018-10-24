//---------------------------------------------------------------
//�ėp�N���X
//---------------------------------------------------------------
#include "Shot.h"

//�ǉ�include---------------------------------------------

namespace Shot
{
	//�ύX��----------------------------------------------
	//�R���X�g���N�^
	Object::Object() : state(NONE)
	{

	}

	//----------------------------------------------------
	//����������
	//----------------------------------------------------
	void		Object::Initialize()
	{
		this->activeCnt = 0;
		this->effectCnt = 0;


		this->angle = D3DXVECTOR3(90, 0, 0);
		this->size = D3DXVECTOR3(5, 5, 5);

		model.Load(TEXT("./data/Model/shot01.x"));
		explode.Load(TEXT("./data/Model/explodeX.x"));


		//�e�������Ă����ԂɂȂ�
		this->state = ACTIVE;


		this->sphere = Sphere(this->pos, 10.0f);
	}

	//----------------------------------------------------
	//�I������
	//----------------------------------------------------
	void		Object::Finalize()
	{
		model.Erase();
		explode.Erase();
	}

	//----------------------------------------------------
	//�X�V����
	//----------------------------------------------------
	void		Object::UpDate()
	{
		//��Ԃɉ����ď�����ω�
		switch (state)
		{
			//�e�̈ړ�����
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
			//��������
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
			//�Ȃɂ����Ȃ�
			break;
		}

		//���̈ʒu�̍X�V
		this->sphere = Sphere(this->pos, 10.0f);
	}

	//----------------------------------------------------
	//�`�揈��
	//----------------------------------------------------
	void		Object::Render()
	{
		//�}�g���b�N�X�̌v�Z
		D3DXMATRIX	mMove;
		D3DXMATRIX	mRot;
		D3DXMATRIX	mScale;

		D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
		D3DXMatrixRotationX(&mRot, D3DXToRadian(angle.x));
		D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
		D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

		world.mat = mScale * mRot * mMove;

		world.SetMatrix(D3DTS_WORLD);

		//�e�̕`��
		switch (state)
		{
		case ACTIVE:
			model.Render();		//�e�̕`��
			break;
		case EXPLODE:
			explode.Render();	//�����̕`��
		}
	}


	//�ǉ����\�b�h----------------------------------------
	//�����蔻��
	bool	Object::HitCheck(Box3D box)
	{
		//���g�̃{�b�N�X�̗p��
		Box3D	me = Box3D(pos.x, pos.y, pos.z, size.x, size.y, size.z);
		
		//����̃{�b�N�X�̗p��
		Box3D	you = Box3D(box.x, box.y, box.z, box.sizeX, box.sizeY, box.sizeZ);

		if (you.HitCheck(me))
		{
			return true;
		}

		return false;
	}


	//���̂Ƃ̂����蔻��
	bool	Object::HitSphere(Sphere& sp)
	{
		if (this->sphere.Hit(sp))
		{
			return true;
		}
		return false;
	}




	//�ύX�s��--------------------------------------------
	//�I�u�W�F�N�g�̐���
	Object*		Object::Create(bool flag)
	{
		if (!flag) { return nullptr; }
		MessageBox(NULL, TEXT("�I�u�W�F�N�g����������܂���"), TEXT("Shot"), MB_OK);
		Object*	obj = new Object;
		
		return new Object;
	}

	//�I�u�W�F�N�g�j��
	void		Object::Destroy()
	{
		MessageBox(NULL, TEXT("�I�u�W�F�N�g��j�����܂���"), TEXT("Shot"), MB_OK);
		
		delete this;
	}
}
