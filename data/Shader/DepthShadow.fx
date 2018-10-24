//---------------------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------------------
float4x4	matWorld   : world;			//���[���h���W�s��
float4x4	cameraView : view;			//�r���[�s��
float4x4	cameraProj : projection;	//�ˉe�s��
float4x4	lightView;					//���C�g�r���[�s��
float4x4	lightProj;					//���C�g�ˉe�s��
float4		diffuse;					//�}�e���A���J���[

texture		shadowTex;	//�e�N�X�`��



//��L�̕ϐ��̓A�v���P�[�V�������Őݒ�
//�A�v���P�[�V�������Ŏg�p���Ȃ��ہA�����̒l���g����

//-------------------------------------------------------------------------
//�T���v��
//-------------------------------------------------------------------------
sampler textureSamp = sampler_state
{
	Texture = <shadowTex>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	AddressW = CLAMP;
	MIPFILTER = LINEAR;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

//-------------------------------------------------------------------------
//�V�F�[�_�[�v���O����
//���_�V�F�[�_�̍\����
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;				//�ˉe�ϊ����W
	float4	ShadowMapTex	: TEXCOORD0;	//Z�o�b�t�@�e�N�X�`��
	float4	Color	: COLOR;				//�f�B�t���[�Y�F
};


//-------------------------------------------------------------------------
//���_�V�F�[�_
//-------------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION,float3 Normal : NORMAL)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//�o�̓f�[�^

	//1:���ʂɃJ�����̖ڐ��ɂ�郏�[���h�r���[�ˉe�ϊ�������
	float4x4	mat;
	mat = mul(matWorld, cameraView);
	mat = mul(mat, cameraProj);
	Out.Pos = mul(Pos, mat);

	//2:���C�g�ڐ��ɂ�郏�[���h�r���[�ˉe�ϊ�����
	mat = mul(matWorld, lightView);
	mat = mul(mat, lightProj);
	Out.ShadowMapTex = mul(Pos, mat);

	//�@���ƃ��C�g�̕������璸�_�̐F������
	//�Z���Ȃ肷���Ȃ��悤�ɒ��߂���
	float3 N = normalize(mul(Normal, matWorld));
	float3 LightDir = normalize(float3(lightView._13, lightView._23, lightView._33));
	//Out.Color = float4(0.0f, 0.6f, 1.0f, 1.0f) * (0.3f + dot(N, -LightDir) * (1.0f - 0.3f));

	//�}�e���A���J���[�̔��f
	Out.Color = diffuse * (0.3f + dot(N, -LightDir) * (1.0f - 0.3f));

	return Out;
}


//-------------------------------------------------------------------------
//�s�N�Z���V�F�[�_
//-------------------------------------------------------------------------
float4	PS(float4 Color : COLOR,float4 ShadowMapTex : TEXCOORD0) : COLOR
{
	//���C�g�ڐ��ɂ��Z�l�̍ĎZ�o
	float zValue = ShadowMapTex.z / ShadowMapTex.w;

	//�ˉe��Ԃ�XY���W���e�N�X�`�����W�ɕϊ�
	float2 TransTexCoord;
	TransTexCoord.x = (1.0f + ShadowMapTex.x / ShadowMapTex.w) * 0.5f;
	TransTexCoord.y = (1.0f - ShadowMapTex.y / ShadowMapTex.w) * 0.5f;

	//���A��Z�l�̒��o
	float zRial = tex2D(textureSamp, TransTexCoord).x;

	//�Z�o�_���V���h�E�}�b�v��Z�l�����傫���Ȃ�A�u�e�v�ɂȂ�
	if (zValue > zRial + 0.008f)
	{
		Color.rgb = Color.rgb * 0.5f;
	}
	return Color;
}



//-------------------------------------------------------------------------
//�e�N�j�b�N�̐ݒ�
//-------------------------------------------------------------------------
technique DepthShadowShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};