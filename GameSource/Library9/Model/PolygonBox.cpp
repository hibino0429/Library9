#include "PolygonBox.h"



//-----------------------------------------------------------------------------
//�|���S���N���X
//-----------------------------------------------------------------------------

//�R���X�g���N�^
PolyBox::PolyBox() : pVB(NULL) , lpvb(NULL)
{
	D3DXMatrixIdentity(&matWorld.mat);
}

//�f�X�g���N�^
PolyBox::~PolyBox()
{
	if (pVB != NULL) { pVB->Release(); pVB = NULL; }
	if (lpvb != NULL) { lpvb->Release(); lpvb = NULL; }
}



//�|���S���̏�����
bool	PolyBox::CreateHitBox(Box3D& hitBox)
{
	//�o�[�e�b�N�X�o�b�t�@�̍쐬
	if (FAILED(LibDGD::CreateVertexBuffer(
		36 * sizeof(VertexBox),
		BoxFVF,
		&pVB
	)))
	{
		MessageBox(NULL, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s"), TEXT("CreateBox"), MB_OK);
		return false;
	}

	VertexBox*	box;
	pVB->Lock(0, 0, (VOID**)&box, 0);

	//��O�̖� Z-
	box[0].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z);
	box[1].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[2].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z);

	box[3].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z);
	box[4].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[5].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z);

	//���̖� Z+
	box[6].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[7].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z + hitBox.sizeZ);
	box[8].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);

	box[9].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[10].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z + hitBox.sizeZ);
	box[11].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z + hitBox.sizeZ);


	//�E�̖� X-
	box[12].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z);
	box[13].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z);
	box[14].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);

	box[15].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[16].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z);
	box[17].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z + hitBox.sizeZ);

	//���̖� X+
	box[18].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z);
	box[19].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[20].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);

	box[21].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[22].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[23].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z + hitBox.sizeZ);


	//��̖� Y+
	box[24].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[25].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z);
	box[26].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);

	box[27].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z + hitBox.sizeZ);
	box[28].pos = D3DXVECTOR3(hitBox.x, hitBox.y + hitBox.sizeY, hitBox.z);
	box[29].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y + hitBox.sizeY, hitBox.z);


	//���̖� Y-
	box[30].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z + hitBox.sizeZ);
	box[31].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[32].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z + hitBox.sizeZ);

	box[33].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z + hitBox.sizeZ);
	box[34].pos = D3DXVECTOR3(hitBox.x, hitBox.y, hitBox.z);
	box[35].pos = D3DXVECTOR3(hitBox.x + hitBox.sizeX, hitBox.y, hitBox.z);


	for (int i = 0; i < 36; ++i)
	{
		box[i].diffuse = (DWORD)D3DXCOLOR(0, 1, 1, 0.3f);
	}

	pVB->Unlock();


	return true;

}


//�|���S���{�b�N�X�̕`��
void	PolyBox::DrawHitBox()
{
	LibDGD::ZBufClear();


	//�����_�����O�X�e�[�g�̐ݒ�
	LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			//�\�ʂ̂ݕ`��
	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);				//���C�g�v�Z���Ȃ�
	LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		//�A���t�@�u�����h���I��
	LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//�\�[�X�A���t�@
	LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);

	//���_�o�b�t�@�̕`��
	LibDGD::SetStreamSource(0, pVB, 0, sizeof(VertexBox));

	//FVF�t�H�[�}�b�g�̐ݒ�
	LibDGD::SetFVF(BoxFVF);

	//�`��
	LibDGD::DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);



	//���ɖ߂�
	//�����_�����O�X�e�[�g�̐ݒ�
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}



//���[���h�}�g���b�N�X
void	PolyBox::WorldMat(Box3D hitbox)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, hitbox.x, hitbox.y, hitbox.z);
	D3DXMatrixScaling(&mScale, hitbox.sizeX, hitbox.sizeY, hitbox.sizeZ);

	matWorld.mat = mScale * mMove;
	matWorld.SetMatrix(D3DTS_WORLD);
}









//���_�o�b�t�@�̃f�[�^�̏���
void	PolyBox::VertexInit()
{
	if (FAILED(LibDGD::CreateVertexBuffer(
		24 * sizeof(Box3DVertex),
		Box3DVertexBuf,
		&lpvb
	)))
	{
		MessageBox(NULL, TEXT("���s"), TEXT("���s"), MB_OK);
		return;
	}

	Box3DVertex*		vbBox;
	lpvb->Lock(0, 0, (VOID**)&vbBox, 0);

	vbBox[0].pos = D3DXVECTOR3(-0.5, -0.5, -0.5);
	vbBox[1].pos = D3DXVECTOR3(0.5, -0.5, -0.5);

	vbBox[2].pos = D3DXVECTOR3(0.5, -0.5, -0.5);
	vbBox[3].pos = D3DXVECTOR3(0.5, -0.5, 0.5);

	vbBox[4].pos = D3DXVECTOR3(0.5, -0.5, 0.5);
	vbBox[5].pos = D3DXVECTOR3(-0.5, -0.5, 0.5);

	vbBox[6].pos = D3DXVECTOR3(-0.5, -0.5, 0.5);
	vbBox[7].pos = D3DXVECTOR3(-0.5, -0.5, -0.5);



	vbBox[8].pos = D3DXVECTOR3(-0.5, 0.5, -0.5);
	vbBox[9].pos = D3DXVECTOR3(0.5, 0.5, -0.5);

	vbBox[10].pos = D3DXVECTOR3(0.5, 0.5, -0.5);
	vbBox[11].pos = D3DXVECTOR3(0.5, 0.5, 0.5);

	vbBox[12].pos = D3DXVECTOR3(0.5, 0.5, 0.5);
	vbBox[13].pos = D3DXVECTOR3(-0.5, 0.5, 0.5);

	vbBox[14].pos = D3DXVECTOR3(-0.5, 0.5, 0.5);
	vbBox[15].pos = D3DXVECTOR3(-0.5, 0.5, -0.5);


	vbBox[16].pos = D3DXVECTOR3(-0.5, -0.5, -0.5);
	vbBox[17].pos = D3DXVECTOR3(-0.5, 0.5, -0.5);

	vbBox[18].pos = D3DXVECTOR3(0.5, -0.5, -0.5);
	vbBox[19].pos = D3DXVECTOR3(0.5, 0.5, -0.5);

	vbBox[20].pos = D3DXVECTOR3(0.5, -0.5, 0.5);
	vbBox[21].pos = D3DXVECTOR3(0.5, 0.5, 0.5);

	vbBox[22].pos = D3DXVECTOR3(-0.5, -0.5, 0.5);
	vbBox[23].pos = D3DXVECTOR3(-0.5, 0.5, 0.5);

	for (int i = 0; i < 24; ++i)
	{
		vbBox[i].color = (DWORD)D3DXCOLOR(0, 1, 0, 1);
	}

	

	lpvb->Unlock();

	
}


void	PolyBox::VertexRender()
{

	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);
	LibDGD::SetStreamSource(0, lpvb, 0, sizeof(Box3DVertex));

	LibDGD::SetFVF(Box3DVertexBuf);

	LibDGD::DrawPrimitive(D3DPT_LINELIST, 0, 12);
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
}



//���S�_�̒��_�̏�����
void	PolyBox::PointInit()
{
	if (FAILED(LibDGD::CreateVertexBuffer(
		1 * sizeof(Box3DPoint),
		Box3DVertexBuf,
		&pointVB)))
	{
		MessageBox(NULL, TEXT("���S�_�̒��_�̏������Ɏ��s���܂���"), TEXT("���s"), MB_OK);
		return;
	}

	Box3DPoint*	point;
	pointVB->Lock(0, 0, (VOID**)&point, 0);

	point[0].pos = D3DXVECTOR3(20, 0, 10);
	point[0].color = (DWORD)D3DXCOLOR(0, 1, 0, 1);

	pointVB->Unlock();

}

//���S�_�̒��_�̕`��
void	PolyBox::PointRender()
{
	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);
	LibDGD::SetStreamSource(0, pointVB, 0, sizeof(Box3DPoint));

	LibDGD::SetFVF(Box3DVertexBuf);

	LibDGD::DrawPrimitive(D3DPT_POINTLIST, 0, 1);
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
}


//�}�g���b�N�X�̃Z�b�g
void	PolyBox::SetMatrix(const D3DXVECTOR3& pos)
{
	D3DXMATRIX	mMove;
	D3DXMATRIX	mScale;

	D3DXMatrixTranslation(&mMove, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&mScale, 1, 1, 1);

	matWorld.mat =  mScale * mMove;
	matWorld.SetMatrix(D3DTS_WORLD);
}