#ifndef __BOX_H__
#define __BOX_H__

#include "DirectXTex/SimpleMath.h"
#include <vector>

#pragma once
// ���N���X
class Box
{
public:

	Box();													// ���ʂɏ�����
	Box(DirectX::XMFLOAT3 pos);								// ���W�w�菉����
	// ���W+�F+�T�C�Y�w�菉����
	Box(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 color, DirectX::XMFLOAT3 scale);
	void SetColor(DirectX::XMFLOAT4 color);
	void InitPositon(DirectX::XMFLOAT3 pos);

	void Update(float tick);
	void Drow();
	void UpdateMinMaxPos();

	bool HitSphere(Box b);			// ��*���̔���
	bool HitAABB(Box b);			// AABB
	bool HitOBB(Box b);				// OBB
	float GetRadius();				// ���̔��a���擾
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetXaxis();
	DirectX::XMFLOAT3 GetYaxis();
	DirectX::XMFLOAT3 GetZaxis();
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();
	FLOAT LenSegOnSeparateAxis(DirectX::XMFLOAT3* Sep, DirectX::XMFLOAT3* e1, DirectX::XMFLOAT3* e2, DirectX::XMFLOAT3* e3 = 0);
public:
	bool isInput = false;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_angle;		// ���̊p�x
	bool isHit = false;

	// AABB�p�̍��W
	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float max_z;
	float min_z;

	
private:
	DirectX::XMFLOAT4X4 m_mat;		// ���[���h�s��
	DirectX::XMFLOAT4X4 m_mat_r;	// ��]�s��
	DirectX::XMFLOAT4X4 m_mat_s;	// �g�k�s��
	DirectX::XMFLOAT4 m_color;		// ���̐F
	DirectX::XMFLOAT3 m_scale;		// ���̃T�C�Y
	float m_baseRadius = 0.5f;		// ���a
};

#endif // __BOX_H__