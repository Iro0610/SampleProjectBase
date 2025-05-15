cbuffer LightBuffer : register(b0)
{
    float3 lightPos;
    float  pad1;
    float3 lightColor;
    float  pad2;
    float3 viewPos;
    float  pad3;
    float  shininess;
    float  specularStrength;
    float2 pad4;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float3 worldPos : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 N = normalize(input.normal);
    float3 L = normalize(lightPos - input.worldPos);
    float3 V = normalize(viewPos - input.worldPos);
    float3 R = reflect(-L, N);

    // ŠÂ‹«Œõ
    float3 ambient = 0.1 * lightColor;

    // ”½ŽË
    float diff = max(dot(N, L), 0.0);
    float3 diffuse = diff * lightColor;

    // ?–Ê”½ŽË
    float spec = 0.0;
    if (diff > 0.0)
    {
        spec = pow(max(dot(R, V), 0.0), shininess);
    }
    float3 specular = specularStrength * spec * lightColor;

    float3 finalColor = ambient + diffuse + specular;
    return float4(finalColor, 1.0);
}