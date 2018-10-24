#include "Map.h"


//�R���X�g���N�^
Map::Map() 
{
	D3DXMatrixIdentity(&matW.mat);
}


//--------------------------------------------------------------
//�}�b�v�̏�����
//--------------------------------------------------------------
void	Map::Initialize()
{
	pos = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(100,10, 100);


	//���f���̓ǂݍ���-----------------------------
	ground.Load(TEXT("./data/Model/Map/map.x"));		//�n�ʂ̓ǂݍ���
	block.Load(TEXT("./data/Model/Map/block.x"));		//�ǂ̓ǂݍ���
	tree.Load(TEXT("./data/Model/Map/tree+.x"));		//�؂̓ǂݍ���
	house.Load(TEXT("./data/Model/Map/house.x"));		//�Ƃ̓ǂݍ���
	stone.Load(TEXT("./data/Model/Map/stone.x"));		//�΂̓ǂݍ���
	

	//���f���̈ʒu---------------------------------
	ground.pos = D3DXVECTOR3(0, 0, 0);
	ground.size = D3DXVECTOR3(1000, 10, 1000);
	block.pos = D3DXVECTOR3(500, 100, 300);
	block.size = D3DXVECTOR3(100, 100, 100);
	tree.pos = D3DXVECTOR3(300, 120, 200);
	tree.size = D3DXVECTOR3(30, 50, 30);
	house.pos = D3DXVECTOR3(-600, 100, -100);
	house.size = D3DXVECTOR3(100, 100, 100);
	stone.pos = D3DXVECTOR3(-400, 50, -400);
	stone.size = D3DXVECTOR3(50, 50, 50);
	stLight.Initialize();
	stLight.GetPos(D3DXVECTOR3(400, 10, -300));


	//���f���̓����蔻��p�{�b�N�X�̐ݒ�----------
	blockHitBox = Box3D(-100, -100, -100, 200, 200, 200);
	treeHitBox = Box3D(-30, -200, -30, 60, 400, 60);
	groundHitBox = Box3D(-500, -20, -500, 1000, 40, 1000);
	houseHitBox = Box3D(-70, -150, -100, 140, 200, 200);
	stoneHitBox = Box3D(-50, -50, -50, 100, 100, 100);
	stLightHitBox = Box3D(-30, -50, -30, 60, 100, 60);

	//���f���̓����蔻��͈͂̃{�b�N�X�̐ݒ�
	polyBox.WorldMat(treeHitBox);
	polyBox.VertexInit();
	
}



//--------------------------------------------------------------
//�}�b�v�̉��
//--------------------------------------------------------------
void	Map::Finalize()
{

	//���f���̉��
	ground.Erase();
	block.Erase();
	tree.Erase();
	house.Erase();
	stone.Erase();
}


//--------------------------------------------------------------
//�}�b�v�̍X�V
//--------------------------------------------------------------
void	Map::UpDate()
{
	stLight.UpDate();
}


//--------------------------------------------------------------
//�}�b�v�̕`��
//--------------------------------------------------------------
void	Map::Render()
{

	//�{�b�N�X�̈ړ��I�t�Z�b�g
	blockHitBox.Offset(block.pos);
	treeHitBox.Offset(tree.pos);
	groundHitBox.Offset(ground.pos);
	houseHitBox.Offset(house.pos);
	stoneHitBox.Offset(stone.pos);

	//�n�ʂ̕`��
	this->WorldMatrix(ground.pos, ground.angle, ground.size);
	ground.Render();

	//�u���b�N�̕`��
	this->WorldMatrix(block.pos, block.angle, block.size);
	block.Render();

	//�؂̕`��
	this->WorldMatrix(tree.pos, tree.angle, tree.size);
	tree.Render();

	//�Ƃ̕`��
	this->WorldMatrix(house.pos, house.angle, house.size);
	house.Render();

	//�΂̕`��
	this->WorldMatrix(stone.pos, stone.angle, stone.size);
	stone.Render();

	//�X���̕`��
	stLight.Render();

	//�|���S���{�b�N�X�̕\��
	polyBox.WorldMat(treeHitBox);
	polyBox.VertexRender();
}



//Z�l�e�N�X�`���̕`��
void	Map::ZTexRender(ZTexture* zTex)
{
	//�{�b�N�X�̈ړ��I�t�Z�b�g
	blockHitBox.Offset(block.pos);
	treeHitBox.Offset(tree.pos);
	groundHitBox.Offset(ground.pos);
	houseHitBox.Offset(house.pos);
	stoneHitBox.Offset(stone.pos);

	WorldMatrix(ground.pos, ground.angle, ground.size);
	zTex->SetWorldMatrix(&matW.mat);
	ground.ZTexRender(zTex);

	WorldMatrix(block.pos, block.angle, block.size);
	zTex->SetWorldMatrix(&matW.mat);
	block.ZTexRender(zTex);

	WorldMatrix(tree.pos, tree.angle, tree.size);
	zTex->SetWorldMatrix(&matW.mat);
	tree.ZTexRender(zTex);

	WorldMatrix(house.pos, house.angle, house.size);
	zTex->SetWorldMatrix(&matW.mat);
	house.ZTexRender(zTex);

	WorldMatrix(stone.pos, stone.angle, stone.size);
	zTex->SetWorldMatrix(&matW.mat);
	stone.ZTexRender(zTex);

}

//Depth�e�N�X�`���̕`��
void	Map::DepthRender(DepthTexture* depTex)
{
	WorldMatrix(ground.pos, ground.angle, ground.size);
	depTex->GetWorldMatrix(&matW.mat);
	ground.DepthRender(depTex);

	WorldMatrix(block.pos, block.angle, block.size);
	depTex->GetWorldMatrix(&matW.mat);
	block.DepthRender(depTex);

	WorldMatrix(tree.pos, tree.angle, tree.size);
	depTex->GetWorldMatrix(&matW.mat);
	tree.DepthRender(depTex);

	WorldMatrix(house.pos, house.angle, house.size);
	depTex->GetWorldMatrix(&matW.mat);
	house.DepthRender(depTex);

	WorldMatrix(stone.pos, stone.angle, stone.size);
	depTex->GetWorldMatrix(&matW.mat);
	stone.DepthRender(depTex);
}



//�}�b�v�̈ʒu
void	Map::SetPos(D3DXVECTOR3& pos)
{
	this->pos = pos;
}

//�}�b�v�̃A���O��
void	Map::SetAngle(D3DXVECTOR3& angle)
{
	this->angle = angle;
}

//�}�b�v�̃T�C�Y
void	Map::SetSize(D3DXVECTOR3& size)
{
	this->size = size;
}


//���߂�̈ʒu���擾����
void	Map::GetCameraPos(Camera* camera)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mScale;
	
	D3DXVECTOR3 dir = pos - camera->GetTarget();	//����

	//���s�ړ�
	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(-atanf(dir.y / dir.z)), D3DXToRadian(angle.z));
	//�g��k��
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	//�s��̍���
	matW.mat = mScale * mRot * mMove;


	//�����x�N�g���𐳋K�����������擾
	D3DXVec3Normalize(&dir, &dir);	//�������擾

	//�O�ς̌v�Z
	//�O�ς𗘗p���ĕ��ʂ���(�r���{�[�h)�ɑ΂��Đ����̃x�N�g�����擾

}



//���[���h�}�g���b�N�X
void	Map::WorldMatrix(D3DXVECTOR3& pos,D3DXVECTOR3& angle,D3DXVECTOR3& size)
{
	D3DXMATRIX		mMove;
	D3DXMATRIX		mRot;
	D3DXMATRIX		mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(angle.y), D3DXToRadian(angle.x), D3DXToRadian(angle.z));
	D3DXMatrixScaling(&mScale, size.x, size.y, size.z);

	matW.mat = mScale * mRot * mMove;
	matW.SetMatrix(D3DTS_WORLD);
}









//-------------------------------------------------------
//�}�b�v�Ƃ̓����蔻��
//-------------------------------------------------------
bool	Map::CheckHit(Box3D& object)
{
	//�}�b�v�̃{�b�N�X�Ǝ擾�����{�b�N�X�Ƃ̓����蔻��
	//�u���b�N�Ƃ̓����蔻��
	if (blockHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("�u���b�N�ƏՓ˂��܂���"), TEXT("�u���b�N"), MB_OK);
		return true;
	}
	//�؂Ƃ̓����蔻��
	if (treeHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("�؂ƏՓ˂��܂���"), TEXT("��"), MB_OK);
		return true;
	}
	//�n�ʂƂ̓����蔻��
	//if (groundHitBox.Hit(object))
	{
		//MessageBox(NULL, TEXT("�n�ʂƏՓ˂��܂���"), TEXT("�n��"), MB_OK);
	//	return true;
	}
	//�ƂƂ̓����蔻��
	if (houseHitBox.Hit(object))
	{
		return true;
	}
	//�΂Ƃ̓����蔻��
	if (stoneHitBox.Hit(object))
	{
		return true;
	}
	//�X���Ƃ̓����蔻��
	if (stLight.hitBox.Hit(object))
	{
		return true;
	}
	return false;
}