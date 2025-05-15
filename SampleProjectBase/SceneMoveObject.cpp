#include "SceneMoveObject.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

void SceneMoveObject::Init()
{
	// ���������^��
	ball_1.InitPositon(DirectX::XMFLOAT3(-10.0f, 0.0f, 0.0f));
	ball_1.SetSpeed(3.0f);

	// �������x�^��
	ball_2.InitPositon(DirectX::XMFLOAT3(-10.0f, 0.0f, -2.0f));
	ball_2.SetAcceleration(1.0f);
	ball_2.SetSpeed(1.0f);

	// ���R�����^��
	ball_3.InitPositon(DirectX::XMFLOAT3(0.0f, 10.0f, -4.0f));

	// ���������グ
	ball_4.InitPositon(DirectX::XMFLOAT3(0.0f, 5.0f, -6.0f));
	ball_4.SetSpeed(10.0f);

	// ��������
	ball_5.InitPositon(DirectX::XMFLOAT3(-5.0f, 8.0f, -8.0f));
	ball_5.SetSpeed(10.0f);

	// �Ε�����
	ball_6.InitPositon(DirectX::XMFLOAT3(-8.0f, 0.0f, -10.0f));
	ball_6.SetSpeed(15.0f);
	ball_6.SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));

	// +�����ڈ�
	ball_7.InitPositon(DirectX::XMFLOAT3(10.0f, 0.0f, 0.0f));
	ball_7.SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	ball_8.InitPositon(DirectX::XMFLOAT3(0.0f, 10.0f, 0.0f));
	ball_8.SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	ball_9.InitPositon(DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f));
	ball_9.SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
}

void SceneMoveObject::Uninit()
{
}

void SceneMoveObject::Update(float tick)
{
	// ���͊Ǘ�
	if (!IsKeyPress(VK_SHIFT))
	{
		// SHIFT�L�[��������Ă��Ȃ���Ε`��؂�ւ�
		if (IsKeyTrigger(VK_LEFT)){
			--drowIndex;
			if (drowIndex < 0) drowIndex = 6;
			Reset();
		}

		if (IsKeyTrigger(VK_RIGHT)){
			++drowIndex;
			if (drowIndex > 6) drowIndex = 0;
			Reset();
		}
	}

	// ���ԍX�V
	m_time += tick;
	ball_1.m_time += tick;
	ball_2.m_time += tick;
	ball_3.m_time += tick;
	ball_4.m_time += tick;
	ball_5.m_time += tick;
	ball_6.m_time += tick;

	// �ۑ�͈� ----------------------------------------------------------

    // ���������^��  
	ball_1.m_pos.x = ball_1.m_basePos.x + ball_1.m_speed * ball_1.m_time;

	// �������x�^��  
    ball_2.m_pos.x = ball_2.m_basePos.x + ball_2.m_speed * ball_2.m_time + 0.5f * ball_2.m_acceleration * ball_2.m_time * ball_2.m_time;
	
	// ���R�����^��
	ball_3.m_pos.y =
		ball_3.m_basePos.y - 0.5f * G * ball_3.m_time * ball_3.m_time;

	// ���������グ
	ball_4.m_pos.y =
		ball_4.m_basePos.y + ball_4.m_speed * ball_4.m_time - 0.5f * G * ball_4.m_time * ball_4.m_time;

	// ��������
	ball_5.m_pos.x =
		ball_5.m_basePos.x + ball_5.m_speed * ball_5.m_time;
	ball_5.m_pos.y =
		ball_5.m_basePos.y - 0.5f * G * ball_5.m_time * ball_5.m_time;

	// �Ε�����
	int deg = 60;				// ���ˊp�x
	deg = deg * XM_PI / 180.0f; //���W�A���ɕϊ�
	ball_6.m_pos.x =
		ball_6.m_basePos.x + ball_6.m_speed * cos(deg) * ball_6.m_time;
	ball_6.m_pos.y =
		ball_6.m_basePos.y + ball_6.m_speed * sin(deg) * ball_6.m_time - 0.5f * G * ball_6.m_time * ball_6.m_time;

	// -------------------------------------------------------------------
 
	// ��莞�Ԍナ�Z�b�g
	if (RESET_TIME != 0)
	{
		if (ball_1.m_time >= RESET_TIME) {
			ball_1.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_1.m_time = 0.0f;
		}
		if (ball_2.m_time >= RESET_TIME) {
			ball_2.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_2.m_time = 0.0f;
		}
		if (ball_3.m_time >= RESET_TIME){
			ball_3.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_3.m_time = 0.0f;
		}
		if (ball_4.m_time >= RESET_TIME) {
			ball_4.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_4.m_time = 0.0f;
		}
		if (ball_5.m_time >= RESET_TIME) {
			ball_5.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_5.m_time = 0.0f;
		}
		if (ball_6.m_time >= RESET_TIME) {
			ball_6.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_6.m_time = 0.0f;
		}
	}
}

void SceneMoveObject::Draw()
{
	switch (drowIndex)
	{
	case 0:
		ball_1.Drow();
		break;
	case 1:
		ball_2.Drow();
		break;
	case 2:
		ball_3.Drow();
		break;
	case 3:
		ball_4.Drow();
		break;
	case 4:
		ball_5.Drow();
		break;
	case 5:
		ball_6.Drow();
		break;
	case 6:
		ball_1.Drow();
		ball_2.Drow();
		ball_3.Drow();
		ball_4.Drow();
		ball_5.Drow();
		ball_6.Drow();
		break;
	}

	ball_7.Drow();
	ball_8.Drow();
	ball_9.Drow();
}

void SceneMoveObject::Reset()
{
	ball_1.m_time = RESET_TIME;
	ball_2.m_time = RESET_TIME;
	ball_3.m_time = RESET_TIME;
	ball_4.m_time = RESET_TIME;
	ball_5.m_time = RESET_TIME;
	ball_6.m_time = RESET_TIME;
}