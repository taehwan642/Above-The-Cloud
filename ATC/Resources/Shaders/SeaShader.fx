matrix g_matWorld, g_matView, g_matProj;

texture g_BaseTexture;

float fTime;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;

};

struct VertexShaderInput
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float2 vTexUV : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 vPosition : POSITION;
	float4 vDiffuse : COLOR0;
	float2 vTexUV : TEXCOORD0;
};

struct PixelShaderInput
{
	float4 vPosition : POSITION;
	float4 vDiffuse : COLOR0;
	float2 vTexUV : TEXCOORD0;
};


VertexShaderOutput VS_MAIN(VertexShaderInput Input)
{
	VertexShaderOutput OutPut = (VertexShaderOutput)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	float A = 5;	// amplitude
	float L = 50;	// wavelength
	float w = 2 * 3.1416 / L;
	float Q = 0.5;

	float3 P0 = Input.vPosition.xyz;
	float2 D = float2(0, 1);
	float dotD = dot(P0.xz, D);
	float C = cos(w * dotD + fTime * 30);
	float S = sin(w * dotD + fTime * 30);

	float3 P = float3(P0.x + Q * A * C * D.x, A * S, P0.z + Q * A * C * D.y);

	OutPut.vPosition = mul(float4(P, 1), matWVP);

	OutPut.vTexUV = Input.vTexUV;

	return OutPut;
}

float4 PS_MAIN(PixelShaderInput Input) : COLOR0
{
	float4 vColor = tex2D(BaseSampler, Input.vTexUV);

	return vColor;
}

technique Default
{
	pass DefaultShader
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		dEsTblend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
};