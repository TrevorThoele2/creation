
Texture2D g_Lightmap;
sampler g_LightmapSampler = sampler_state
{
	Texture = <g_Lightmap>;
};

struct VertexIn
{
	float4 position : POSITION0;
	float4 center : POSITION1;
	float4 color : COLOR;
	float2 radius : TEXCOORD0;
};

struct VertexOut
{
	float4 position : POSITION0;
	float4 center : POSITION1;
	float4 color : COLOR;
	float2 radius : TEXCOORD0;
};

float4x4 g_Projection;
float2 g_ScreenSize;

VertexOut vShader(VertexIn Input)
{
	VertexOut Vert = (VertexOut)0;
	
	Vert.position = mul(Input.position, g_Projection);
	Vert.center = Input.center;
	Vert.color = Input.color;
	Vert.radius = Input.radius;
	
    return Vert;
}

float4 pShader(float2 vPosition : VPOS, VertexOut Vert) : COLOR
{
	return float4(Vert.color.r, Vert.color.g, Vert.color.b, 1 - (distance(Vert.center, vPosition) / Vert.radius.x));
}

technique FirstTechnique
{
    pass FirstPass
    {
        VertexShader = compile vs_3_0 vShader();
		PixelShader = compile ps_3_0 pShader();
		//FillMode = WIREFRAME;
    }
}