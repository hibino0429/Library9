#include "Magic.h"


//�R���X�g���N�^
MagicEffect::MagicEffect() : m_TexEffect(NULL),m_VBEffect(NULL),
m_animAngle(0),m_animRadius(0),m_animHeight(0),m_numAnimArrayElem(0)
{
	D3DXMatrixIdentity(&world.mat);
}

//�f�X�g���N�^
MagicEffect::~MagicEffect()
{
	Finalize();
}

//----------------------------------------------------------
//����������
//----------------------------------------------------------
void	MagicEffect::Initialize()
{
	DWORD	time = ::timeGetTime();

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	Vertex1*		v;

	if (FAILED(LibDGD::CreateVertexBuffer(
		1 * sizeof(Vertex1),
		VERTEX_FVF,
		&m_VBEffect
	)))
	{
		MessageBox(NULL, TEXT("���_�̐����Ɏ��s���܂���"), TEXT("CreateVertexBuf"), MB_OK);
		return;
	}

	//���_�o�b�t�@���쐬
	m_VBEffect->Lock(0, 0, (LPVOID*)&v, 0);
	v[0].pos = D3DXVECTOR3(0, 0, 0);
	v[0].p_size = 18.0f;
	v[0].color = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	m_VBEffect->Unlock();


	//�e�N�X�`���̓ǂݍ���
	LibDGD::CreateTextureEx(
		TEXT("./data/image/spark.bmp"),
		0, 0, 0xFF000000, NULL, NULL, &m_TexEffect);
	
	//�����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//���C�g�v�Z
	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);
	//Z��r�����Ȃ�
	LibDGD::SetRenderState(D3DRS_ZENABLE, FALSE);
	//�f�B�U�����O������
	LibDGD::SetRenderState(D3DRS_DITHERENABLE, TRUE);

	//�e�N�X�`���X�e�[�W�̐ݒ�
	LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	//�A���t�@�u�����f�B���O
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�|�C���g�X�v���C�g�̐ݒ�
	LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	//�|�C���g�X�P�[���̌W��
	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_POINTSIZE, (DWORD)1.0f);
	LibDGD::SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_A, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_B, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_C, (DWORD)1.0f);

	//�e�N�X�`���t�B���^�[�̐ݒ�
	LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	

	//-----------------------------------------------
	//�A�j���[�V�����̐���
	//-----------------------------------------------
	m_numAnimArrayElem = 30;
	m_animAngle = new Animation[m_numAnimArrayElem];
	m_animRadius = new Animation[m_numAnimArrayElem];
	m_animHeight = new Animation[m_numAnimArrayElem];

	
	float	randam;
	for (int i = 0; i < m_numAnimArrayElem; ++i)
	{
		//��]�p
		randam = (float)rand() * 360.0f / (float)RAND_MAX;
		m_animAngle[i].CreateKey(4);
		m_animAngle[i].SetKeyValue(0, 0.0f, 0.0f - randam);
		m_animAngle[i].SetKeyValue(1, 0.5f, 180.0f - randam);
		m_animAngle[i].SetKeyValue(2, 1.0f, 360.0f - randam);
		m_animAngle[i].SetDuration(1000);
		m_animAngle[i].SetStartTime(time);
		m_animAngle[i].SetLoopFlag(TRUE);
		
		//��]���a
		randam = ((float)rand() / (float)RAND_MAX);
		m_animRadius[i].CreateKey(2);
		m_animRadius[i].SetKeyValue(0, 0.0f, 2.0f * randam);
		m_animRadius[i].SetKeyValue(1, 1.0f, 10.0f * randam);
		m_animRadius[i].SetDuration(20000);
		m_animRadius[i].SetStartTime(time);
		m_animRadius[i].SetLoopFlag(TRUE);
		
		//����
		randam = ((float)rand() / (float)RAND_MAX);
		m_animHeight[i].CreateKey(2);
		m_animHeight[i].SetKeyValue(0, 0.0f, -8.0f + randam * 2.0f);
		m_animHeight[i].SetKeyValue(1, 1.0f, 8.0f);
		m_animHeight[i].SetDuration(3000 + (DWORD)(randam * 5000.0f));
		m_animHeight[i].SetStartTime(time);
		m_animHeight[i].SetLoopFlag(TRUE);
	}

	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
}



//--------------------------------------------------------------------
//�������
//--------------------------------------------------------------------
void	MagicEffect::Finalize()
{
	//�A�j���[�V�����̍폜
	if (m_animAngle != 0) { delete[] m_animAngle; }
	if (m_animRadius != 0) { delete[] m_animRadius; }
	if (m_animHeight != 0) { delete[] m_animHeight; }

	m_numAnimArrayElem = 0;

	//�e�N�X�`���̉��
	if (m_TexEffect != NULL) { m_TexEffect->Release(); m_TexEffect = NULL; }
	if (m_VBEffect != NULL) { m_VBEffect->Release(); m_VBEffect = NULL; }
}



//---------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------
void	MagicEffect::UpDate()
{

}


//---------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------
void	MagicEffect::Render()
{
	DWORD	time = ::timeGetTime();
	float	value;
	bool	isEnd;


	//�G�t�F�N�g�̕`��
	LibDGD::SetTexture(0, m_TexEffect);

	float	angle;
	float	radius;
	float	height;

	for (int i = 0; i < m_numAnimArrayElem; ++i)
	{
		//�~�����W�n���g�p
		radius = 0.0f;
		if (m_animRadius[i].GetValue(time, &value, &isEnd))
		{
			radius = value;
		}
		//�p�x
		angle = 0.0f;
		if (m_animAngle[i].GetValue(time, &value, &isEnd))
		{
			angle = D3DXToRadian(value);
		}
		//����
		height = 0.0f;
		if (m_animHeight[i].GetValue(time, &value, &isEnd))
		{
			height = value;
		}

		D3DXMatrixTranslation(&world.mat,
			radius * cosf(angle),
			height,
			radius * sinf(angle));

		//���[���h�ϊ��}�g���b�N�X���p�C�v���C���ɃZ�b�g
		world.SetMatrix(D3DTS_WORLD);

		//�I�u�W�F�N�g�̕`��
		LibDGD::SetStreamSource(0, m_VBEffect, 0, sizeof(Vertex1));
		LibDGD::SetFVF(VERTEX_FVF);
		LibDGD::DrawPrimitive(D3DPT_POINTLIST, 0, 1);
	}

	
}
