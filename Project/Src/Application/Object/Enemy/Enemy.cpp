#include "Enemy.h"

#include"../../main.h"
void Enemy::Update()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	m_deg += 6.0f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_deg -= 6.0f;
	//}
	//m_deg = m_targetdeg;
	//float diffdeg = m_targetdeg - m_deg;
	//if (diffdeg < 0)
	//{
	//	diffdeg += 360;
	//} 

	//float turnDeg = 6.0f;
	//if (diffdeg < 180)
	//{
	//	if (diffdeg < turnDeg)
	//	{
	//		turnDeg = diffdeg;
	//	}
	//	m_deg += turnDeg;

	//	if (m_deg > 360)
	//	{
	//		m_deg = m_deg - 360;
	//	}
	//	m_deg = (int)m_deg % 360;
	//}
	//else if (diffdeg >= 180)
	//{
	//	if (diffdeg < turnDeg)
	//	{
	//		turnDeg = diffdeg;
	//	}
	//	m_deg -= turnDeg;
	//	if (m_deg < 0)
	//	{
	//		m_deg = m_deg + 360;
	//	}
	//	m_deg = (int)(m_deg + 360) % 360;
	//}
	//行列用変数にディグリーを代入
	/*m_rotateX = m_deg;*/

	//機体の回転
	//turnDeg = 3.0f;
	//diffdeg = m_deg - m_rotateZ;
	//if (diffdeg < 0)
	//{
	//	diffdeg += 360;
	//}
	//if (diffdeg < 180)
	//{
	//	if (diffdeg < turnDeg)
	//	{
	//		turnDeg = diffdeg;
	//	}

	//	m_rotateZ += turnDeg;

	//	if (m_rotateZ > 360)
	//	{
	//		m_rotateZ = m_rotateZ - 360;
	//	}
	//	m_rotateZ = (int)m_rotateZ % 360;
	//}
	//else if (diffdeg >= 180)
	//{
	//	if (diffdeg < turnDeg)
	//	{
	//		turnDeg = diffdeg;
	//	}
	//	m_rotateZ -= turnDeg;
	//	if (m_rotateZ < 0)
	//	{
	//		m_rotateZ = m_rotateZ + 360;
	//	}
	//	m_rotateZ = (int)(m_rotateZ + 360) % 360;
	//}

	//float x = m_target.lock()->GetPos().x;
	//float y = m_target.lock()->GetPos().y;
	//m_rad = atan2(y, x);
	//m_pos.x += cos(m_rad) * m_speed;
	//m_pos.y += sin(m_rad) * m_speed;//移動量足し込み

	//// キャラクターの移動速度
	//Math::Vector3 nowPos = GetPos();
	//Math::Vector3 moveVec = m_TargetPos - nowPos;

	//moveVec.Normalize();
	//m_pos += moveVec * m_speed;

	//m_dir = m_TargetPos - GetPos();

	//m_dir += m_modeldir;

	//m_dir.Normalize();

	//m_modeldir = GetMatrix().Backward();
	//m_dir = m_modeldir;
	//m_speed = 0;
	//m_gravity -= 0.05f;
	//if (m_gravity < 0)
	//{
	//	m_gravity = 0;
	//}

	//m_pos += m_dir * m_speed;

	//m_pos.y -= m_gravity;

	//m_pos.z = 0;

	//m_inertia = m_dir;

}

void Enemy::PostUpdate()
{
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

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(10);

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

void Enemy::DrawLit()
{
	if (!m_model) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::Init()
{
	m_objType = ObjectType::Enemy;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Enemy/Enemy2.gltf");
	m_pos = { 0,100,0 };
	m_dir = { 0,0,0 };
	m_scale = 1;

	m_thrust = 5.0f;
	m_thrustspeed = 5.0f;
	m_thrustMax = 5.0f;
	m_thrustMin = 0.0f;
	m_speed = 5.0f;

	m_anime = 0;

	m_modeldir = GetMatrix().Backward();

	m_gravity = 0;

	m_rotateX = 0;
	m_rotateY = 90;
	m_rotateZ = 0;
	m_deg = 0;
	m_TargetPos = {};
	m_rad = 0;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollison", { 0,0.5f,0 }, 0.2f, KdCollider::TypeDamage);
}

void Enemy::OnHit()
{
	Application::Instance().EnemyCnt();
	m_isExpired = true;
}

void Enemy::ImguiUpdate()
{
	ImGui::Text("enemy_pos.x : %f", m_pos.x);
	//ImGui::Text("m_TargetPos : %f %f %f", m_TargetPos.x, m_TargetPos.y, m_TargetPos.z);
}
