#include "P_Bullet.h"
#include"../../Scene/SceneManager.h"

void P_Bullet::Update()
{
	m_time--;
	if (m_time < 0)
	{
		m_time = 0;
		m_isExpired = true;
	}

	//�A�j���[�V����
	m_polygon.SetUVRect((int)m_animeCnt);
	m_animeCnt += m_animeSpeed;

	//�A�j���[�V���������[�v
	if (m_animeCnt >= 5)
	{
		m_animeCnt = 0;
	}

	//======================================================
	//�����蔻��
	//======================================================

	//������p�̕ϐ����쐬
	KdCollider::SphereInfo sphereInfo;
	//���̒��S�ʒu��ݒ�
	sphereInfo.m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);
	//���̔����ݒ�
	sphereInfo.m_sphere.Radius = m_attackArea;
	//�����蔻����������^�C�v��ݒ�
	sphereInfo.m_type = KdCollider::TypeDamage;

	//�f�o�b�O�p����G���A
	//m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius, kRedColor);

	//�����Ɠ����蔻��
	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		hit = obj->Intersects(sphereInfo, nullptr);

		//�U�������������ꍇ
		if (hit)
		{
			if (obj->GetObjType() == ObjectType::Enemy)
			{

				//HIT���̑���I�u�W�F�N�g�̏���
				obj->OnHit();

				//Hit�������̎����̏���
				OnHit();

				//���[�v���甲����
				break;
			}
		}
	}
	m_pos += m_dir * m_speed;
}

void P_Bullet::PostUpdate()
{
	//���W�X�V
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_rotateY),
		DirectX::XMConvertToRadians(m_rotateX+90),
		DirectX::XMConvertToRadians(m_rotateZ));
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(10);
	m_mWorld = scaleMat * rotateMat * transMat;
}

void P_Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}


void P_Bullet::Init()
{
	m_objType = ObjectType::P_Bullet;

	m_polygon.SetMaterial("Asset/Textures/p_bullet.png");

	//�摜����
	m_polygon.SetSplit(5, 1);

	//���_�ύX 
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Top);

	//�f�o�b�O�p
	//m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	m_animeCnt = 0;
	m_animeSpeed = 1.0f;

	m_attackDir = { 0,0,0 };

	m_attackArea = 10.0f;

	m_rotateX = 0;
	m_rotateY = 90;
	m_rotateZ = 0;
	m_speed = 0;
	m_time = 200;
}

void P_Bullet::OnHit()
{
	m_isExpired = true;
}
