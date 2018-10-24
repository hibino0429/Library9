
//---------------------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------------------
float4x4	mWVP;		//���[���h�ˉe�ϊ��s��
float4x4	mWIT;		//���[���h�ϊ��s��
float4		diffuse;	//�f�B�q���[�Y�F
float3		vLightDir;	//���C�g�̕���

float2		fog;		//�t�H�O
texture		texture0;	//�e�N�X�`��

//���̋���
float4	I_a = { 0.3f,0.3f,0.3f,0.0f };	//Ambient
float4	I_d = { 0.3f,0.3f,0.7f,0.0f };	//diffuse

//���˗�
float4	K_a = { 0.4f,0.4f,0.4f,1.0f };	//ambient
float4  K_d = { 0.4f,0.2f,0.2f,1.0f };	//diffuse

//��L�̕ϐ��̓A�v���P�[�V�������Őݒ�
//�A�v���P�[�V�������Ŏg�p���Ȃ��ہA�����̒l���g����

//-------------------------------------------------------------------------
//�T���v��
//-------------------------------------------------------------------------
sampler textureSamp = sampler_state
{
	Texture = <texture0>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//-------------------------------------------------------------------------
//�V�F�[�_�[�v���O����
//���_�V�F�[�_�̍\����
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
	float2	tex0	: TEXCOORD0;
	float	Fog		: FOG;
};


//-------------------------------------------------------------------------
//���_�V�F�[�_
//-------------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION, float3 Normal : NORMAL,float2 tex : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//�o�̓f�[�^

	//���W�ϊ�(���[���h�ˉe�ϊ�)
	Out.Pos = mul(Pos, mWVP);

	//���_�F
	float3 L = -vLightDir;
	float3 N = normalize(mul(Normal, (float3x3)mWIT));	//���[���h���W�n�ł̖@��

	//�e�N�X�`��(���̂܂�)
	Out.tex0 = tex;

	//���_�F
	Out.Color = I_a * K_a + I_d * K_d * max(0, dot(N, L));	//���� + �g�U���ˌ�

	Out.Fog = fog.x + Pos.w + fog.y;	//�t�H�O

	return Out;
}


//-------------------------------------------------------------------------
//�s�N�Z���V�F�[�_
//-------------------------------------------------------------------------
float4	PS(VS_OUTPUT In,float2 tex : TEXCOORD0) : COLOR
{
	//�e�N�X�`���F��Color�Ŏw�肵���F�̍���
	//return tex2D(textureSamp,tex) * In.Color;
	return In.Color;
}



//-------------------------------------------------------------------------
//�e�N�j�b�N�̐ݒ�
//-------------------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};