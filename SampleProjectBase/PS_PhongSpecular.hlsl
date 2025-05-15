struct PS_IN
{
    float4 pos : SV_POSITION; //ピクセルの位置
    float3 normal : NORMAL; //法線ベクトル
    float2 uv : TEXCOORD0; //テクスチャ座標
    float3 worldPos : POSITION0;//ワールド座標
};
//ライト情報を
cbuffer Light : register(b0)
{
    float4 lightDir; //ライトの方向
    float4 lightDiffuse; //ライトの反射光
    float4 lightAmbient; //ライトの環境光
};
//カメラの定数バッファ
cbuffer Camera : register(b1)
{
    float4 camPos;//カメラの位置
};
//テクスチャへのバインド
Texture2D tex : register(t0);
//サンプラーヘノバインド
SamplerState samp : register(s0);
//ピクセルシェーダーのメイン処理
//頂点で囲まれているピクセル分だけ実行する
float4 main(PS_IN pin) : SV_TARGET
{
    float4 color;
    //テクスチャから色を取得
    color = tex.Sample(samp, pin.uv);
    //法線ベクトルを正規化
    float3 N = normalize(pin.normal);
    //ライトの方向を正規化
    float3 L = normalize(-lightDir.xyz);
    //拡散反射光の計算（法線ベクトルとライトの方向の内積）
    float diffuse = saturate(dot(N, L));
    color *= diffuse * lightDiffuse + lightAmbient;//カラーに拡散反射光と環境光を適用
    //視線ベクトルと反射ベクトルの計算
    float3 V = normalize(camPos.xyz - pin.worldPos);
    float3 R = normalize(reflect(-L, N));
    //鏡面光の計算
    float specular = saturate(dot(V, R));
    //カラーに鏡面光を加算
    color += pow(specular, 5.0f);
    //アルファを1.0に設定
    color.a = 1.0f;
    return color;
}
