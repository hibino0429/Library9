//
// Scene.cpp
// �V�[���̎���
//

#include <windows.h>

#include "Scene.h"

//=============================================================
// ����
//=============================================================
//-------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------------------------------------
Scene::Scene()
 :m_pMyVB(0)
{
}

//-------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------
Scene::~Scene()
{

	Destroy();
}

//-------------------------------------------------------------
// �V�[���𐶐�
// ����
//		pD3DDevice : IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
// �߂�l
//		����������S_OK
//-------------------------------------------------------------
HRESULT Scene::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	Destroy();

	if(pD3DDevice == 0) {
		return E_FAIL;
	}

	//--------------------------------------
	// ���f���̒��_�o�b�t�@�[�𐶐�
	//--------------------------------------

	// 4�̒��_����Ȃ钸�_�o�b�t�@�����
	if( FAILED( pD3DDevice->CreateVertexBuffer( 
		4*sizeof(MY_VERTEX),	// ���_�o�b�t�@�S�̂̃T�C�Y
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g����
        MY_VERTEX_FVF,			// ���_�f�[�^��FVF�t�H�[�}�b�g
        D3DPOOL_MANAGED, 		// �V�X�e���̒��_�o�b�t�@������
		&m_pMyVB, 				// ���_�o�b�t�@���i�[����ϐ�
		NULL ) ) )				// ���NULL�Ɏw��
	{
        return E_FAIL;
	}


    //���_�o�b�t�@�[�̒��g�𖄂߂�
    MY_VERTEX* v;
    m_pMyVB->Lock( 0, 0, (void**)&v, 0 );

	//���_�f�[�^�F���_�̍��W�l�̐ݒ�
    v[0].p = D3DXVECTOR3(-1.5f,  1.5f, 0.0f );	// ���_�@
    v[1].p = D3DXVECTOR3( 1.5f,  1.5f, 0.0f );	// ���_�A
    v[2].p = D3DXVECTOR3(-1.5f, -1.5f, 0.0f );	// ���_�B
    v[3].p = D3DXVECTOR3( 1.5f, -1.5f, 0.0f );	// ���_�C
    
	//���_�f�[�^�F���_�̊�{�I�ȐF�̐ݒ�i���F�ɐݒ�j
    v[0].color = v[1].color = v[2].color = v[3].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_pMyVB->Unlock();

	//--------------------------------------
	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	//--------------------------------------

	// ���ʕ`�惂�[�h�̎w��
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// �y��r���s�Ȃ�
    pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// �f�B�U�����O���s�Ȃ��i���i���`��j
	pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE);
	// �m�[���C�e�B���O���[�h 	
    pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	

	return S_OK;
}

//-------------------------------------------------------------
// ���W�ϊ����s��
// ����
//		pD3DDevice : IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//-------------------------------------------------------------
void Scene::Transform(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if(pD3DDevice == 0) {
		return;
	}

	//---------------------------
	// �r���[�}�g���b�N�X�̐ݒ�
	//---------------------------

	// ������
	D3DXMatrixIdentity(&m_view);

	// �J�����̈ʒu�ƕ�����ݒ�
	D3DXMatrixLookAtLH(&m_view, 
			&D3DXVECTOR3( 0.0f, 0.0f, -10.0f),	// �J�����̈ʒu
			&D3DXVECTOR3( 0.0f, 0.0f, 0.0f),	// �J�����̕�����������_
			&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));	// �J�����̏�̕���

	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_view);
		

	//---------------------------
	// �ˉe�}�g���b�N�X�̐ݒ�
	//---------------------------

	// �r���[�|�[�g�̎擾
	D3DVIEWPORT9    vp;
	if(FAILED(pD3DDevice->GetViewport(&vp))) {
		return;
	}

	// �A�X�y�N�g��̌v�Z
	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	// ������
	D3DXMatrixIdentity(&m_proj);

	// �ˉe�}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_proj, 
			D3DXToRadian(45.0f),	// �J�����̉�p
			aspect,					// �A�X�y�N�g��
			1.0f,					// near�v���[��
			1000.0f);				// far�v���[��

	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_proj);

}

//-------------------------------------------------------------
// �I�u�W�F�N�g���̕`��
// ����
//		pD3DDevice : IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//-------------------------------------------------------------
void Scene::Draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if(pD3DDevice == 0) {
		return;
	}

	if(m_pMyVB == 0) {
		return;
	}

	// ���W�ϊ��i�J�����̐ݒ�Ȃǁj
	Transform(pD3DDevice);

	// ���W�ϊ��i���f���̔z�u�j
	D3DXMatrixIdentity(&m_world);
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_world);

	//--------------------------------------
	// ���_�o�b�t�@�[�̕`��
	//--------------------------------------

	// ���_�o�b�t�@�[�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetStreamSource( 0, m_pMyVB, 0, sizeof(MY_VERTEX) );
    
	// ���_�f�[�^�̂e�u�e�t�H�[�}�b�g��ݒ�
    pD3DDevice->SetFVF( MY_VERTEX_FVF );

	// �`��
    pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

}

//-------------------------------------------------------------
// �V�[���̔j��
//-------------------------------------------------------------
void Scene::Destroy()
{
	// ���_�o�b�t�@�[�̉��
	SAFE_RELEASE(m_pMyVB);
}
