#include "Particle.h"


//�R���X�g���N�^
Particle::Particle() : m_pVBEffect(NULL),m_pTexture(NULL)
{
	D3DXMatrixIdentity(&world.mat);
}

//�f�X�g���N�^
Particle::~Particle()
{
	
	if (m_pTexture != nullptr) { m_pTexture->Release(); }
	if (m_pVBEffect != nullptr) { m_pVBEffect->Release(); }

}


//------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------
void	Particle::Initialize()
{
	MY_VERTEX*	v;

	//���_�o�b�t�@�̍쐬
	if (FAILED(LibDGD::CreateVertexBuffer(
		MY_NUM_PSPRITE * sizeof(MY_VERTEX),
		MY_VERTEX_FVF,
		&m_pVBEffect
	)))
	{
		MessageBox(NULL, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s���܂���"), TEXT("�����܂���"), MB_OK);
		return;
	}

	//�e�N�X�`���̓ǂݍ���
	//�摜�̓ǂݍ���
	if (FAILED(LibDGD::CreateTextureEx(
		TEXT("./data/image/spark.bmp"), 0, 0, 0xFF000000, NULL, NULL, &m_pTexture
	)))
	{
		MessageBox(NULL, TEXT("�e�N�X�`���̉摜"), TEXT("CreateTextureEx"), MB_OK);
		return;
	}

	//////��ʂ̕`�惂�[�h
	//LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	////���C�g�̌v�Z�����Ȃ�
	//LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	////Z��r���s��Ȃ�
	//LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	//////�f�B�U�����O���s��
	//LibDGD::SetRenderState(D3DRS_DITHERENABLE, TRUE);


	////�e�N�X�`���X�e�[�W�̐ݒ�
	//LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//LibDGD::SetTexStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//LibDGD::SetTexStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	////�A���t�@�u�����f�B���O�̐ݒ�
	//LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	////�e�N�X�`���t�B���^�[�̐ݒ�
	//LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////�|�C���g�X�v���C�g�̐ݒ�
	//LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);	//�|�C���g�X�v���C�g��������
	//
	//LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);	//���_�ɉ����ăT�C�Y��ύX
	//LibDGD::SetRenderState(D3DRS_POINTSIZE, 1.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSIZE_MIN, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	//LibDGD::SetRenderState(D3DRS_POINTSCALE_C, 1.0f);	//������2��


	////////////////////////////////////
	//�|�C���g�X�v���C�g�̏�����
	////////////////////////////////////
	DWORD	time = ::timeGetTime();
	int i;
	for (i = 0; i < MY_NUM_PSPRITE; i++)
	{
		//�|�C���g�X�v���C�g�̏����ʒu
		m_psprite[i].pos = D3DXVECTOR3(0, 0, 0);

		//�|�C���g�X�v���C�g�̏����x�Ƃ��̕���
		m_psprite[i].vec.x = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;
		m_psprite[i].vec.y = ((float)rand() / (float)RAND_MAX) * 30.0f + 30.0f;
		m_psprite[i].vec.z = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;

		//�|�C���g�X�v���C�g�̃T�C�Y
		m_psprite[i].psize = ((float)rand() / (float)RAND_MAX) * 4.0f + 8.0f;

		//�|�C���g�X�v���C�g�̌p������
		m_psprite[i].duration = ((float)rand() / (float)RAND_MAX) * 2.0f + 2.0f;

		//�|�C���g�X�v���C�g�̊J�n����
		m_psprite[i].startTime = time - (DWORD)(((float)rand() / (float)RAND_MAX) * 2.0f * 1000.0f);

	}

	
	//���_�o�b�t�@�̒��g�𖄂߂�
	m_pVBEffect->Lock(0, 0, (LPVOID*)&v, 0);
	for (i = 0; i < MY_NUM_PSPRITE; ++i)
	{
		v[i].color = (DWORD)D3DXCOLOR(1, 1, 1, 1);
	}
	m_pVBEffect->Unlock();

}



//------------------------------------------------------------------------
//�������
//------------------------------------------------------------------------
void	Particle::Finalize()
{

}



//------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------
void	Particle::UpDate()
{
	
}



//------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------
void	Particle::Render()
{
	//�V�[���̃N���A
	LibDGD::ZBufClear();

	LibDGD::SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//�e�N�X�`���X�e�[�W�̐ݒ�
	LibDGD::SetTexStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	LibDGD::SetTexStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	//�A���t�@�u�����f�B���O�̐ݒ�
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	LibDGD::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N�X�`���t�B���^�[�̐ݒ�
	LibDGD::SetTexSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	LibDGD::SetTexSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//�|�C���g�X�v���C�g�̐ݒ�
	LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);	//�|�C���g�X�v���C�g��������
	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);	//���_�ɉ����ăT�C�Y��ύX
	LibDGD::SetRenderState(D3DRS_POINTSIZE, (DWORD)1.0f);
	LibDGD::SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_A, (DWORD)0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_B, (DWORD) 0.0f);
	LibDGD::SetRenderState(D3DRS_POINTSCALE_C, (DWORD)1.0f);	//������2��

	DWORD	time = timeGetTime();
	MY_VERTEX*	v;

	int i;

	//�|�C���g�X�v���C�g�̍X�V
	float t;
	m_pVBEffect->Lock(0, 0, (LPVOID*)&v, 0);
	for (i = 0; i < MY_NUM_PSPRITE; ++i)
	{
		//�o�ߎ��Ԃ��v�Z
		t = (float(time - m_psprite[i].startTime)) / 1000.0f;

		//�p�����Ԃ𒴂��Ă����珉��������
		if (t > m_psprite[i].duration)
		{
			m_psprite[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_psprite[i].startTime = time;
			m_psprite[i].duration = ((float)rand() / (float)RAND_MAX) * 2.0f + 2.0f;
			t = 0.0f;
		}

		//�|�C���g�X�v���C�g�̈ʒu�̌v�Z
		v[i].pos.x = m_psprite[i].pos.x + m_psprite[i].vec.x * t + 0.5f * (0.0f) * t * t;
		v[i].pos.y = m_psprite[i].pos.y + m_psprite[i].vec.y * t + 0.5f * (-9.8f) * t * t;
		v[i].pos.z = m_psprite[i].pos.z + m_psprite[i].vec.z * t + 0.5f * (0.0f) * t * t;

		//�|�C���g�X�v���C�g�̃T�C�Y��ݒ�
		v[i].p_sizse = m_psprite[i].psize;
	}
	m_pVBEffect->Unlock();


	//////////////////////////////////////////////
	//�G�t�F�N�g�̕`��
	//////////////////////////////////////////////
	LibDGD::SetTexture(0, m_pTexture);

	//���[���h�ϊ�
	D3DXMatrixIdentity(&world.mat);
	world.SetMatrix(D3DTS_WORLD);


	//�I�u�W�F�N�g�̕`��
	LibDGD::SetStreamSource(0, m_pVBEffect, 0, sizeof(MY_VERTEX));
	LibDGD::SetFVF(MY_VERTEX_FVF);
	LibDGD::DrawPrimitive(D3DPT_POINTLIST, 0, MY_NUM_PSPRITE);

	LibDGD::SetTexture(0, NULL);
	//�����_�����O�X�e�[�g��߂�
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	LibDGD::SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);	//���_�ɉ����ăT�C�Y��ύX
	LibDGD::SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);	//�|�C���g�X�v���C�g��������

}