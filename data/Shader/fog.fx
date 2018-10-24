
//---------------------------------------------------------------
//グローバル変数
//---------------------------------------------------------------
float4x4	mWVP;		//ワールド射影変換行列
float4x4	mWIT;		//ワールド変換行列
float4		diffuse;	//ディヒューズ色
float3		vLightDir;	//ライトの方向

float2		fog;		//フォグ
texture		texture0;	//テクスチャ

//光の強さ
float4	I_a = { 0.3f,0.3f,0.3f,0.0f };	//Ambient
float4	I_d = { 0.3f,0.3f,0.7f,0.0f };	//diffuse

//反射率
float4	K_a = { 0.4f,0.4f,0.4f,1.0f };	//ambient
float4  K_d = { 0.4f,0.2f,0.2f,1.0f };	//diffuse

//上記の変数はアプリケーション側で設定
//アプリケーション側で使用しない際、これらの値が使われる

//-------------------------------------------------------------------------
//サンプラ
//-------------------------------------------------------------------------
sampler textureSamp = sampler_state
{
	Texture = <texture0>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//-------------------------------------------------------------------------
//シェーダープログラム
//頂点シェーダの構造体
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
	float2	tex0	: TEXCOORD0;
	float	Fog		: FOG;
};


//-------------------------------------------------------------------------
//頂点シェーダ
//-------------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION, float3 Normal : NORMAL,float2 tex : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//出力データ

	//座標変換(ワールド射影変換)
	Out.Pos = mul(Pos, mWVP);

	//頂点色
	float3 L = -vLightDir;
	float3 N = normalize(mul(Normal, (float3x3)mWIT));	//ワールド座標系での法線

	//テクスチャ(そのまま)
	Out.tex0 = tex;

	//頂点色
	Out.Color = I_a * K_a + I_d * K_d * max(0, dot(N, L));	//環境光 + 拡散反射光

	Out.Fog = fog.x + Pos.w + fog.y;	//フォグ

	return Out;
}


//-------------------------------------------------------------------------
//ピクセルシェーダ
//-------------------------------------------------------------------------
float4	PS(VS_OUTPUT In,float2 tex : TEXCOORD0) : COLOR
{
	//テクスチャ色とColorで指定した色の合成
	//return tex2D(textureSamp,tex) * In.Color;
	return In.Color;
}



//-------------------------------------------------------------------------
//テクニックの設定
//-------------------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};