
//---------------------------------------------------------------
//グローバル変数
//---------------------------------------------------------------
float3		lightLocalDir;	//ライトの方向
float3		cameraVec;		//カメラの方向
float4x4	matWorld;		//ワールド変換行列
float4x4	matView;		//ビュー変換行列
float4x4	matProj;		//射影変換行列

texture		diffuseMap;		//ディフューズマップ
texture		normalMap;		//ノーマルマップ


//-------------------------------------------------------------------------
//サンプラ
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
//頂点を射影空間へ移動
//-------------------------------------------------------------------------
float4	TransVertex(float4 vertex, float4x4 worldMat, float4x4 viewMat, float4x4 projMat)
{
	vertex = mul(vertex, worldMat);
	vertex = mul(vertex, viewMat);
	vertex = mul(vertex, projMat);
	return vertex;
}

//-------------------------------------------------------------------------
//接空間行列の逆行列を出力
//-------------------------------------------------------------------------
float4x4 InvTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	float4x4 mat = { float4(tangent,0.0f),float4(binormal,0.0f),float4(normal,0.0f),{0.0f,0.0f,0.0f,1.0f} };
	return transpose(mat);
}


//-------------------------------------------------------------------------
//シェーダープログラム
//頂点シェーダの構造体
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;					//変換後位置
	float4	uv		: TEXCOORD0;				//UV座標	
	float4	lightTangentDir	: TEXCOORD3;		//ライトの方向
};


//-------------------------------------------------------------------------
//頂点シェーダ
//-------------------------------------------------------------------------
VS_OUTPUT	NormalMapVS(float4 inLocalPos : POSITION,
	float3 inTangent : TANGENT,
	float3 inBinormal: BINORMAL,
	float3 inLocalNormal : NORMAL,
	float4 inUVPos : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;		//出力データ

	//ローカル頂点をスクリーンへ
	//Out.Pos = TransVertex(inLocalPos, matWorld, matView, matProj);
	inLocalPos = mul(inLocalPos, matWorld);
	inLocalPos = mul(inLocalPos, matView);
	inLocalPos = mul(inLocalPos, matProj);
	Out.Pos = inLocalPos;
	//接空間行列の逆行列の算出
	float4x4 invTangentMat = InvTangentMatrix(normalize(inTangent), normalize(inBinormal), normalize(inLocalNormal));
	
	//ライトベクトルを接空間に移動
	Out.lightTangentDir = mul(float4(-lightLocalDir, 1.0f), invTangentMat);

	Out.uv = inUVPos;
	return Out;
}


//-------------------------------------------------------------------------
//ピクセルシェーダ
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
//テクニックの設定
//-------------------------------------------------------------------------
technique NormalMapShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 NormalMapVS();
		PixelShader  = compile ps_2_0 NormalMapPS();
	}
};