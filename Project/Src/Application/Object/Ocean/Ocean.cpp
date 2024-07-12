#include "Ocean.h"

void Ocean::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ocean/Ocean.gltf");

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, -1400, 350);

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(100, 10, 30);

	m_mWorld = scaleMat * transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollison", m_model, KdCollider::TypeGround);
}

void Ocean::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

