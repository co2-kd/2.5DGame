#include "Mousehit.h"

#include"../../Scene/SceneManager.h"
#include"../Player/Player.h"

void Mousehit::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Hit/hit.gltf");
	}

	//Math::Matrix transMat;
	//transMat = Math::Matrix::CreateTranslation(m_pos);

	//Math::Matrix scaleMat;
	//scaleMat = Math::Matrix::CreateScale(1, 1, 1);

	//m_mWorld = scaleMat * transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Mousehit", m_spModel, KdCollider::TypeMouseHit);
}

void Mousehit::Update()
{
	Math::Matrix transMat;
	Math::Matrix scaleMat;

	if (m_target.expired() == false)
	{
		m_pos = m_target.lock()->GetPos();
		m_pos.z = 0;
	}
	transMat = Math::Matrix::CreateTranslation(m_pos);
	scaleMat = Math::Matrix::CreateScale(1, 1, 1);

	m_mWorld = scaleMat * transMat;
}

void Mousehit::DrawLit()
{
	if (!m_spModel) return;
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Mousehit::SetTarget(std::weak_ptr<Player> _target)
{
	//_targetがshared_ptrとして有効ならセットする
	if (_target.expired() == false)
	{
		m_target = _target;
	}
}
