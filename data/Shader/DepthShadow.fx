//---------------------------------------------------------------
//グローバル変数
//---------------------------------------------------------------
float4x4	matWorld   : world;			//ワールド座標行列
float4x4	cameraView : view;			//ビュー行列
float4x4	cameraProj : projection;	//射影行列
float4x4	lightView;					//ライトビュー行列
float4x4	lightProj;					//ライト射影行列
float4		diffuse;					//マテリアルカラー

texture		shadowTex;	//テクスチャ



//上記の変数はアプリケーション側で設定
//アプリケーション側で使用しない際、これらの値が使われる

//-------------------------------------------------------------------------
//サンプラ
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
//シェーダープログラム
//頂点シェーダの構造体
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;				//射影変換座標
	float4	ShadowMapTex	: TEXCOORD0;	//Zバッファテクスチャ
	float4	Color	: COLOR;				//ディフューズ色
};


//-------------------------------------------------------------------------
//頂点シェーダ
//-------------------------------------------------------------------------
VS_OUTPUT	VS(float4 Pos : POSITION,float3 Normal : NORMAL)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;	//出力データ

	//1:普通にカメラの目線によるワールドビュー射影変換をする
	float4x4	mat;
	mat = mul(matWorld, cameraView);
	mat = mul(mat, cameraProj);
	Out.Pos = mul(Pos, mat);

	//2:ライト目線によるワールドビュー射影変換する
	mat = mul(matWorld, lightView);
	mat = mul(mat, lightProj);
	Out.ShadowMapTex = mul(Pos, mat);

	//法線とライトの方向から頂点の色を決定
	//濃くなりすぎないように調節する
	float3 N = normalize(mul(Normal, matWorld));
	float3 LightDir = normalize(float3(lightView._13, lightView._23, lightView._33));
	//Out.Color = float4(0.0f, 0.6f, 1.0f, 1.0f) * (0.3f + dot(N, -LightDir) * (1.0f - 0.3f));

	//マテリアルカラーの反映
	Out.Color = diffuse * (0.3f + dot(N, -LightDir) * (1.0f - 0.3f));

	return Out;
}


//-------------------------------------------------------------------------
//ピクセルシェーダ
//-------------------------------------------------------------------------
float4	PS(float4 Color : COLOR,float4 ShadowMapTex : TEXCOORD0) : COLOR
{
	//ライト目線によるZ値の再算出
	float zValue = ShadowMapTex.z / ShadowMapTex.w;

	//射影空間のXY座標をテクスチャ座標に変換
	float2 TransTexCoord;
	TransTexCoord.x = (1.0f + ShadowMapTex.x / ShadowMapTex.w) * 0.5f;
	TransTexCoord.y = (1.0f - ShadowMapTex.y / ShadowMapTex.w) * 0.5f;

	//リアルZ値の抽出
	float zRial = tex2D(textureSamp, TransTexCoord).x;

	//算出点がシャドウマップのZ値よりも大きいなら、「影」になる
	if (zValue > zRial + 0.008f)
	{
		Color.rgb = Color.rgb * 0.5f;
	}
	return Color;
}



//-------------------------------------------------------------------------
//テクニックの設定
//-------------------------------------------------------------------------
technique DepthShadowShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();
	}
};