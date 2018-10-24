
//---------------------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------------------
float4x4	mWVP;
float4x4	mWIT;

float3		vLightDir;	//���C�g�̕���


//���̋���
float4	I_a = { 0.3f,0.3f,0.3f,0.0f };	//Ambient
float4	I_d = { 0.3f,0.3f,0.7f,0.0f };	//diffuse

//���˗�
float4	K_a = { 0.4f,0.4f,0.4f,1.0f };	//ambient
float4  K_d = { 0.4f,0.2f,0.2f,1.0f };	//diffuse

//��L�̕ϐ��̓A�v���P�[�V�������Őݒ�
//�A�v���P�[�V�������Ŏg�p���Ȃ��ہA�����̒l���g����


//-------------------------------------------------------------------
//�V�F�[�_�[�v���O����
//���_�V�F�[�_�̍\����
//-------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
};


//-------------------------------------------------------------------
//���[�J�����W�E�@���x�N�g��
//���_�V�F�[�_
//-------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION, float3 Normal : NORMAL)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//�o�̓f�[�^

	//���W�ϊ�
	Out.Pos = mul(Pos, mWVP);

	//���_�F
	float3 L = -vLightDir;
	float3 N = normalize(mul(Normal, (float3x3)mWIT));	//���[���h���W�n�ł̖@��

	Out.Color = I_a * K_a + I_d * K_d * max(0, dot(N, L));	//���� + �g�U���ˌ�

	return Out;
}


//-------------------------------------------------------------------------
//���_�V�F�[�_�Ōv�Z�����F���o��
//�s�N�Z���V�F�[�_
//-------------------------------------------------------------------------
float4	PS(VS_OUTPUT In) : COLOR
{
	return In.Color;
}



//�e�N�j�b�N�̐ݒ�
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};