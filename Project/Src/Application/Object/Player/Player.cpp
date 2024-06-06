#include "Player.h"

void Player::Update()
{
	//à⁄ìÆèàóù
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 1.0f;
		m_dir = -0.2;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 1.0f;
		m_dir = 0.2;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 1.0f;
	}


	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(0.2,0.2,m_dir);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

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
	m_dir = 0.2;
}