
//---------------------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------------------
float3		lightLocalDir;	//���C�g�̕���
float3		cameraVec;		//�J�����̕���
float4x4	matWorld;		//���[���h�ϊ��s��
float4x4	matView;		//�r���[�ϊ��s��
float4x4	matProj;		//�ˉe�ϊ��s��

texture		diffuseMap;		//�f�B�t���[�Y�}�b�v
texture		normalMap;		//�m�[�}���}�b�v


//-------------------------------------------------------------------------
//�T���v��
//-------------------------------------------------------------------------
sampler diffuseSamp = sampler_state
{
	texture = <diffuseMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
sampler normalSamp = sampler_state
{
	texture = <normalMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//-------------------------------------------------------------------------
//���_���ˉe��Ԃֈړ�
//-------------------------------------------------------------------------
float4	TransVertex(float4 vertex, float4x4 worldMat, float4x4 viewMat, float4x4 projMat)
{
	vertex = mul(vertex, worldMat);
	vertex = mul(vertex, viewMat);
	vertex = mul(vertex, projMat);
	return vertex;
}

//-------------------------------------------------------------------------
//�ڋ�ԍs��̋t�s����o��
//-------------------------------------------------------------------------
float4x4 InvTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	float4x4 mat = { float4(tangent,0.0f),float4(binormal,0.0f),float4(normal,0.0f),{0.0f,0.0f,0.0f,1.0f} };
	return transpose(mat);
}


//-------------------------------------------------------------------------
//�V�F�[�_�[�v���O����
//���_�V�F�[�_�̍\����
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;					//�ϊ���ʒu
	float4	uv		: TEXCOORD0;				//UV���W	
	float4	lightTangentDir	: TEXCOORD3;		//���C�g�̕���
};


//-------------------------------------------------------------------------
//���_�V�F�[�_
//-------------------------------------------------------------------------
VS_OUTPUT	NormalMapVS(float4 inLocalPos : POSITION,
	float3 inTangent : TANGENT,
	float3 inBinormal: BINORMAL,
	float3 inLocalNormal : NORMAL,
	float4 inUVPos : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;		//�o�̓f�[�^

	//���[�J�����_���X�N���[����
	//Out.Pos = TransVertex(inLocalPos, matWorld, matView, matProj);
	inLocalPos = mul(inLocalPos, matWorld);
	inLocalPos = mul(inLocalPos, matView);
	inLocalPos = mul(inLocalPos, matProj);
	Out.Pos = inLocalPos;
	//�ڋ�ԍs��̋t�s��̎Z�o
	float4x4 invTangentMat = InvTangentMatrix(normalize(inTangent), normalize(inBinormal), normalize(inLocalNormal));
	
	//���C�g�x�N�g����ڋ�ԂɈړ�
	Out.lightTangentDir = mul(float4(-lightLocalDir, 1.0f), invTangentMat);

	Out.uv = inUVPos;
	return Out;
}


//-------------------------------------------------------------------------
//�s�N�Z���V�F�[�_
//-------------------------------------------------------------------------
float4	NormalMapPS(float3 inLightTangentDir : TEXCOORD3,float4 inUV : TEXCOORD0) : COLOR
{
	float3 normalColor = tex2D(normalSamp, inUV);
	float3 normalVec = 2.0f * normalColor - 1.0f;
	normalVec = normalize(normalVec);

	float3	bright = dot(normalize(inLightTangentDir), normalVec);
	bright = max(0.0f, bright);
	float4 diffuseColor = tex2D(diffuseSamp, inUV);

	return float4(bright * diffuseColor.xyz, 1.0f);
}



//-------------------------------------------------------------------------
//�e�N�j�b�N�̐ݒ�
//-------------------------------------------------------------------------
technique NormalMapShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 NormalMapVS();
		PixelShader  = compile ps_2_0 NormalMapPS();
	}
};