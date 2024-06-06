#include "Back.h"


void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/back.png");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(900, 600, 1);

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 0, 50);


	m_mWorld = scaleMat * transMat;
}