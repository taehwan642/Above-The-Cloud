matrix	g_matWorld;
matrix  g_matView;
matrix  g_matProj;

texture	g_BaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};


struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4			vPosition: POSITION;
	float4			vNormal : NORMAL;
	float2		 	vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition, 1.f), matWVP);
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_matWorld));
	Out.vTexUV = In.vTexUV;

	return Out;
}

// w나누기 연산 (2차원 투영변환)
// 뷰포트 변환 (API시연회때 사용한 좌표계)
// 래스터라이즈 (둘러쌓여진 정점세개의 정보를 선형보간하여 픽셀의 정보를 생성한다.) 

struct PS_IN
{
	float4			vPosition: POSITION;
	float4			vNormal : NORMAL;
	float2		 	vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	float4	vDiffuse : COLOR0;
	float4	vNormal : COLOR1;
};

// 최종적인 픽셀의 색을 결정하여 화면에 렌더링한다.
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vDiffuse = tex2D(BaseSampler, In.vTexUV);
	Out.vDiffuse.a = 1.f;
	// -1 => 0
	//  1 => 1
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	return Out;
}

technique Default_Technique
{
	pass Default_Rendering
	{
		AlphaTestEnable = true;
		Alpharef = 0;
		AlphaFunc = Greater;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
	pass Default_Rendering
	{
		AlphaTestEnable = true;
		Alpharef = 0;
		AlphaFunc = Greater;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
	pass Default_Rendering
	{
		AlphaTestEnable = true;
		Alpharef = 0;
		AlphaFunc = Greater;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
	pass Alpha
	{
		//AlphaTestEnable = true;
		//Alpharef = 0;
		//AlphaFunc = Greater;
		AlphaBlendenable = true;
		srcBlend = SrcAlpha;
		destBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}