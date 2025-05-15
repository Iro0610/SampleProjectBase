struct VS_IN
{
    float3 pos : POSITION0;//頂点座標
    float3 normal : NORMAL0;//法線情報
    float2 uv : TEXCOORD0;//テクスチャ座標
};
struct VS_OUT
{
    float4 pos : SV_POSITION;//頂点位置（クリップ空間）
    float3 normal : NORMAL0;//頂点法線ベクトル
    float2 uv : TEXCOORD0;//テクスチャ座標
    float3 worldPos : POSITION0;//頂点位置（ワールド空間）
};
    
cbuffer MatrixBuffer : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};
 //頂点シェーダーのメイン処理
//この処理を頂点ごとに実行します
VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    //座標変換
    vout.pos = float4(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    vout.worldPos = vout.pos;
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);
    //法線ベクトルの変換
    vout.normal = mul(vin.normal, (float3x3) world);
    //頂点データのUV座標をピクセルシェーダーへの出力データとして設定
    vout.uv = vin.uv;
    return vout;
}