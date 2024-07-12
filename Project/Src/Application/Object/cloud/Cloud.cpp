#include "Cloud.h"


void Cloud::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld, m_color);
}

void Cloud::Init()
{
	m_polygon.SetMaterial("Asset/Textures/cloud.png");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(m_scale);

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);


	m_mWorld = scaleMat * transMat;
}