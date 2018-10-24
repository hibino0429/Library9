
//---------------------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------------------
float3		lightDir;		//���C�g�̕���
float4		lightColor;		//���C�g�̐F(���ːF)
float4x4	matWorld;		//���[���h�ϊ��s��
float4x4	matView;		//�r���[�ϊ��s��
float4x4	matProj;		//�ˉe�ϊ��s��

texture		diffuseMap;		//�f�B�q���[�Y�}�b�v

//-------------------------------------------------------------------------
//�T���v��
//-------------------------------------------------------------------------
sampler textureSamp = sampler_state
{
	texture = <diffuseMap>;
};

//-------------------------------------------------------------------------
//�V�F�[�_�[�v���O����
//���_�V�F�[�_�̍\����
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;			//�ϊ���ʒu
	float4	uv		: TEXCOORD0;		//UV���W	
	float3	normal	: TEXCOORD1;		//���[���h�ϊ������@��
};


//-------------------------------------------------------------------------
//���_�V�F�[�_
//-------------------------------------------------------------------------
VS_OUTPUT	DiffuseVS(float4 localPos : POSITION, float3 localNormal : NORMAL,float4 uvPos : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;		//�o�̓f�[�^

	//���[�J�����_���X�N���[����
	Out.Pos = mul(localPos, matWorld);	//���[���h�ϊ�
	Out.Pos = mul(Out.Pos, matView);	//�r���[�ϊ�
	Out.Pos = mul(Out.Pos, matProj);	//�ˉe�ϊ�

	//�@�������[���h��Ԃ�
	Out.normal = mul(localNormal, matWorld);

	//UV���W��o�^
	Out.uv = uvPos;
	
	return Out;
}


//-------------------------------------------------------------------------
//�s�N�Z���V�F�[�_
//-------------------------------------------------------------------------
float4	DiffusePS(float3 inWorldNormal : TEXCOORD1,float4 inUV : TEXCOORD0) : COLOR
{
	//���˂�����̋������Z�o
	float power = dot( normalize(inWorldNormal),-normalize(lightDir) );
	power = clamp(power, 0.0f, 1.0f);

	//�g�U���˂�����̐F���Z�o
	float4	refColor = tex2D(textureSamp, inUV);		//���ːF
	float4	surfaceColor = refColor * lightColor;		//�\�ʂ̐F

	return power * surfaceColor;		//�f�B�t���[�Y�F�̎Z�o
}



//-------------------------------------------------------------------------
//�e�N�j�b�N�̐ݒ�
//-------------------------------------------------------------------------
technique DiffuseShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 DiffuseVS();
		PixelShader  = compile ps_2_0 DiffusePS();
	}
};