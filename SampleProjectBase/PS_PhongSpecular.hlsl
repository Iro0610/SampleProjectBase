struct PS_IN
{
    float4 pos : SV_POSITION; //�s�N�Z���̈ʒu
    float3 normal : NORMAL; //�@���x�N�g��
    float2 uv : TEXCOORD0; //�e�N�X�`�����W
    float3 worldPos : POSITION0;//���[���h���W
};
//���C�g����
cbuffer Light : register(b0)
{
    float4 lightDir; //���C�g�̕���
    float4 lightDiffuse; //���C�g�̔��ˌ�
    float4 lightAmbient; //���C�g�̊���
};
//�J�����̒萔�o�b�t�@
cbuffer Camera : register(b1)
{
    float4 camPos;//�J�����̈ʒu
};
//�e�N�X�`���ւ̃o�C���h
Texture2D tex : register(t0);
//�T���v���[�w�m�o�C���h
SamplerState samp : register(s0);
//�s�N�Z���V�F�[�_�[�̃��C������
//���_�ň͂܂�Ă���s�N�Z�����������s����
float4 main(PS_IN pin) : SV_TARGET
{
    float4 color;
    //�e�N�X�`������F���擾
    color = tex.Sample(samp, pin.uv);
    //�@���x�N�g���𐳋K��
    float3 N = normalize(pin.normal);
    //���C�g�̕����𐳋K��
    float3 L = normalize(-lightDir.xyz);
    //�g�U���ˌ��̌v�Z�i�@���x�N�g���ƃ��C�g�̕����̓��ρj
    float diffuse = saturate(dot(N, L));
    color *= diffuse * lightDiffuse + lightAmbient;//�J���[�Ɋg�U���ˌ��Ɗ�����K�p
    //�����x�N�g���Ɣ��˃x�N�g���̌v�Z
    float3 V = normalize(camPos.xyz - pin.worldPos);
    float3 R = normalize(reflect(-L, N));
    //���ʌ��̌v�Z
    float specular = saturate(dot(V, R));
    //�J���[�ɋ��ʌ������Z
    color += pow(specular, 5.0f);
    //�A���t�@��1.0�ɐݒ�
    color.a = 1.0f;
    return color;
}
