
//---------------------------------------------------------------
//グローバル変数
//---------------------------------------------------------------
float3		lightDir;		//ライトの方向
float4		lightColor;		//ライトの色(入射色)
float4x4	matWorld;		//ワールド変換行列
float4x4	matView;		//ビュー変換行列
float4x4	matProj;		//射影変換行列

texture		diffuseMap;		//ディヒューズマップ

//-------------------------------------------------------------------------
//サンプラ
//-------------------------------------------------------------------------
sampler textureSamp = sampler_state
{
	texture = <diffuseMap>;
};

//-------------------------------------------------------------------------
//シェーダープログラム
//頂点シェーダの構造体
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		: POSITION;			//変換後位置
	float4	uv		: TEXCOORD0;		//UV座標	
	float3	normal	: TEXCOORD1;		//ワールド変換した法線
};


//-------------------------------------------------------------------------
//頂点シェーダ
//-------------------------------------------------------------------------
VS_OUTPUT	DiffuseVS(float4 localPos : POSITION, float3 localNormal : NORMAL,float4 uvPos : TEXCOORD0)
{
	VS_OUTPUT	Out = (VS_OUTPUT)0;		//出力データ

	//ローカル頂点をスクリーンへ
	Out.Pos = mul(localPos, matWorld);	//ワールド変換
	Out.Pos = mul(Out.Pos, matView);	//ビュー変換
	Out.Pos = mul(Out.Pos, matProj);	//射影変換

	//法線をワールド空間へ
	Out.normal = mul(localNormal, matWorld);

	//UV座標を登録
	Out.uv = uvPos;
	
	return Out;
}


//-------------------------------------------------------------------------
//ピクセルシェーダ
//-------------------------------------------------------------------------
float4	DiffusePS(float3 inWorldNormal : TEXCOORD1,float4 inUV : TEXCOORD0) : COLOR
{
	//反射する光の強さを算出
	float power = dot( normalize(inWorldNormal),-normalize(lightDir) );
	power = clamp(power, 0.0f, 1.0f);

	//拡散反射する光の色を算出
	float4	refColor = tex2D(textureSamp, inUV);		//反射色
	float4	surfaceColor = refColor * lightColor;		//表面の色

	return power * surfaceColor;		//ディフューズ色の算出
}



//-------------------------------------------------------------------------
//テクニックの設定
//-------------------------------------------------------------------------
technique DiffuseShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 DiffuseVS();
		PixelShader  = compile ps_2_0 DiffusePS();
	}
};