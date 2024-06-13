#include "Player.h"

void Player::Update()
{
	float oldspeed = m_speed;
	Math::Vector3 oldPos = m_pos;

	//移動処理
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//	m_pos.x -= 1.0f;
	//	m_dir = -0.2;
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//	m_pos.x += 1.0f;
	//	m_dir = 0.2;
	//}
	
	//自機のディグリー変更
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_deg += 6.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_deg -= 6.0f;
	}
	//行列用変数にディグリーを代入
	m_rotateX = m_deg;

	if (m_rotateZ != m_deg)
	{
		if (m_rotateZ < m_deg)
		{
			m_rotateZ += 3.0f;
		}
		else if (m_rotateZ > m_deg)
		{
			m_rotateZ -= 3.0f;
		}
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_gravity += 0.001f;
		m_thrust = 0;
		m_thrustspeed -= 0.005f;
		if (m_thrustspeed <= 0.0f)
		{
			m_thrustspeed = 0.0f;
		}
		m_dir = m_inertia;
		m_speed = m_thrustspeed;
	}
	else
	{
		m_thrust += 0.1f;
		m_thrustspeed = m_thrust;
		if (m_thrustspeed >= m_thrustMax)
		{
			m_thrustspeed = m_thrustMax;
			m_gravity -= 0.01f;
			if (m_gravity <= 0)
			{
				m_gravity = 0;
			}
		}
		if (m_thrustspeed < oldspeed)
		{
			m_inertia.Normalize();
			m_dir = m_inertia;
			m_speed = oldspeed - m_thrustspeed;
		}
		else
		{
			//モデルが向いている方向のベクトル
			m_modeldir = GetMatrix().Backward();
			m_dir = m_modeldir;
			m_speed = m_thrustspeed;
		}
	}



	//if (m_thrustspeed < oldspeed)
	//{
	//	m_dir = m_inertia;
	//	m_speed = oldspeed - m_thrustspeed;
	//}
	//else
	//{
	//	m_dir = m_modeldir;
	//	m_speed = m_thrustspeed;
	//}

	m_pos += m_dir * m_speed;

	m_pos.y -= m_gravity;

	m_inertia = m_dir;

	//m_speed = oldspeed;
}

void Player::PostUpdate()
{
	if (m_deg > 360)
	{
		m_deg = m_deg - 360;
	}
	if (m_rotateX > 360)
	{
		m_rotateX = m_rotateX - 360;
	}
	if (m_rotateY > 360)
	{
		m_rotateY = m_rotateY - 360;
	}
	if (m_rotateZ > 360)
	{
		m_rotateZ = m_rotateZ - 360;
	}

	m_pos.z = 0;

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1);

	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_rotateY),
		DirectX::XMConvertToRadians(m_rotateX),
		DirectX::XMConvertToRadians(m_rotateZ));
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	/*
		Math::Matrix rotateXMat;
		rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotateX));
		Math::Matrix rotateYMat;
		rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotateY));
		Math::Matrix rotateZMat;
		rotateZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotateZ));
		Math::Matrix transMat;
		transMat = Math::Matrix::CreateTranslation(m_pos);

		m_mWorld = scaleMat * rotateYMat * rotateZMat * rotateXMat * transMat;
	*/
	m_mWorld = scaleMat * rotateMat * transMat;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::Init()
{
	m_objType = ObjectType::Player;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/player.gltf");
	m_pos = { 0,0,0 };
	m_dir = { 0,0,0 };
	m_scale = 1;

	m_thrust = 5.0f;
	m_thrustspeed = 5.0f;
	m_thrustMax = 5.0f;
	m_speed = 0.0f;

	m_anime = 0;


	m_gravity = 0;

	m_rotateX = 0;
	m_rotateY = 90;
	m_rotateZ = 0;
	m_deg = 0;
}