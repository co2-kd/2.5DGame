#include "Cloud2.h"


void Cloud2::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld, m_color);
}

void Cloud2::Init()
{
	m_polygon.SetMaterial("Asset/Textures/cloud2.png");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(m_scale);

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);


	m_mWorld = scaleMat * transMat;
}