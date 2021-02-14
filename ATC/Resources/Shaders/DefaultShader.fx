matrix g_matWorld, g_matView, g_matProj;

texture g_BaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;

};

struct VertexShaderInput
{
	float3 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct PixelShaderInput
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};


VertexShaderOutput VS_MAIN(VertexShaderInput Input)
{
	VertexShaderOutput OutPut = (VertexShaderOutput)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	OutPut.vPosition = mul(vector(Input.vPosition, 1.f), matWVP);
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
	pass SkySphere
	{
		ZEnable = false;
		ZWriteEnable = false;
		CullMode = cw;
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
};