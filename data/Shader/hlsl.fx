
//---------------------------------------------------------------
//グローバル変数
//---------------------------------------------------------------
float4x4	mWVP;
float4x4	mWIT;

float3		vLightDir;	//ライトの方向


//光の強さ
float4	I_a = { 0.3f,0.3f,0.3f,0.0f };	//Ambient
float4	I_d = { 0.3f,0.3f,0.7f,0.0f };	//diffuse

//反射率
float4	K_a = { 0.4f,0.4f,0.4f,1.0f };	//ambient
float4  K_d = { 0.4f,0.2f,0.2f,1.0f };	//diffuse

//上記の変数はアプリケーション側で設定
//アプリケーション側で使用しない際、これらの値が使われる


//-------------------------------------------------------------------
//シェーダープログラム
//頂点シェーダの構造体
//-------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
};


//-------------------------------------------------------------------
//ローカル座標・法線ベクトル
//頂点シェーダ
//-------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION, float3 Normal : NORMAL)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//出力データ

	//座標変換
	Out.Pos = mul(Pos, mWVP);

	//頂点色
	float3 L = -vLightDir;
	float3 N = normalize(mul(Normal, (float3x3)mWIT));	//ワールド座標系での法線

	Out.Color = I_a * K_a + I_d * K_d * max(0, dot(N, L));	//環境光 + 拡散反射光

	return Out;
}


//-------------------------------------------------------------------------
//頂点シェーダで計算した色を出力
//ピクセルシェーダ
//-------------------------------------------------------------------------
float4	PS(VS_OUTPUT In) : COLOR
{
	return In.Color;
}



//テクニックの設定
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};