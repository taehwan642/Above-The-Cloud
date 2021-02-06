matrix	g_matWorld;
matrix  g_matView;
matrix  g_matProj;

texture	g_BaseTexture;

float4 lightposition;
float4 cameraposition;

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
	float3			vDiffuse : TEXCOORD1;
	float3			vViewDir : TEXCOORD2;
	float3			vReflect : TEXCOORD3;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	Out.vPosition = mul(vector(In.vPosition, 1.f), g_matWorld);

	// 빛 방향 벡터
	float3 lightDir = Out.vPosition.xyz - lightposition.xyz;
	lightDir = normalize(lightDir);

	// 카메라 방향 벡터
	float3 viewDir = normalize(Out.vPosition.xyz - cameraposition.xyz);
	Out.vViewDir = viewDir;

	Out.vPosition = mul(Out.vPosition, g_matView);
	Out.vPosition = mul(Out.vPosition, g_matProj);

	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_matWorld));
	Out.vTexUV = In.vTexUV;

	Out.vDiffuse = dot(-lightDir, Out.vNormal);
	Out.vReflect = reflect(lightDir, Out.vNormal);
	return Out;
}

// w나누기 연산 (2차원 투영변환)
// 래스터라이즈 (둘러쌓여진 정점세개의 정보를 선형보간하여 픽셀의 정보를 생성한다.) 

struct PS_IN
{
	float4			vNormal : NORMAL;
	float2		 	vTexUV : TEXCOORD0;
	float3			vDiffuse : TEXCOORD1;
	float3			vViewDir : TEXCOORD2;
	float3			vReflect : TEXCOORD3;
};

struct PS_OUT
{
	float4	vDiffuse : COLOR0; // 렌더타겟 0번
	//float4	vNormal : COLOR1;  // 렌더타겟 1번
};

// 최종적인 픽셀의 색을 결정하여 화면에 렌더링한다.
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	float4 albedo = tex2D(BaseSampler, In.vTexUV);
	float3 diffuse = saturate(In.vDiffuse);
	float3 reflection = normalize(In.vReflect);
	float3 viewDir = normalize(In.vViewDir);
	float3 specular = 0;
	if (diffuse.x > 0)
	{
		specular = saturate(dot(reflection, -viewDir));
		specular = pow(specular, 20.0f);
	}
	float3 ambient = float3(0.2f, 0.2f, 0.2f);
	Out.vDiffuse = float4(albedo * diffuse + ambient + specular, 1);
	return Out;
}

technique Default_Technique
{
	//pass Default_Rendering
	//{
	//	AlphaTestEnable = true;
	//	Alpharef = 0;
	//	AlphaFunc = Greater;

	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}
	//pass Default_Rendering
	//{
	//	AlphaTestEnable = true;
	//	Alpharef = 0;
	//	AlphaFunc = Greater;

	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}
	//pass Default_Rendering
	//{
	//	AlphaTestEnable = true;
	//	Alpharef = 0;
	//	AlphaFunc = Greater;

	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}
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