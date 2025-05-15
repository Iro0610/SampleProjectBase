struct VS_IN
{
    float3 pos : POSITION0;//���_���W
    float3 normal : NORMAL0;//�@�����
    float2 uv : TEXCOORD0;//�e�N�X�`�����W
};
struct VS_OUT
{
    float4 pos : SV_POSITION;//���_�ʒu�i�N���b�v��ԁj
    float3 normal : NORMAL0;//���_�@���x�N�g��
    float2 uv : TEXCOORD0;//�e�N�X�`�����W
    float3 worldPos : POSITION0;//���_�ʒu�i���[���h��ԁj
};
    
cbuffer MatrixBuffer : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};
 //���_�V�F�[�_�[�̃��C������
//���̏����𒸓_���ƂɎ��s���܂�
VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    //���W�ϊ�
    vout.pos = float4(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    vout.worldPos = vout.pos;
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);
    //�@���x�N�g���̕ϊ�
    vout.normal = mul(vin.normal, (float3x3) world);
    //���_�f�[�^��UV���W���s�N�Z���V�F�[�_�[�ւ̏o�̓f�[�^�Ƃ��Đݒ�
    vout.uv = vin.uv;
    return vout;
}