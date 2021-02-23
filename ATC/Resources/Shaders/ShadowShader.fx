matrix g_matWorld, g_matView, g_matProj;

texture g_BaseTexture;

float alpha;

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

struct PixelShaderOutput
{
	float4 diffuse : COLOR0;
	float4 normal : COLOR1;
};


PixelShaderOutput PS_MAIN(PixelShaderInput Input)
{
	PixelShaderOutput PixelOut = (PixelShaderOutput)0;
	float4 tex = tex2D(BaseSampler, Input.vTexUV);
	PixelOut.diffuse = float4(tex.xyz, alpha);

	return PixelOut;
}

technique Shadow
{
	pass ShadowAlpha
	{
		AlphaBlendenable = true;
		srcBlend = SrcAlpha;
		destBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
};