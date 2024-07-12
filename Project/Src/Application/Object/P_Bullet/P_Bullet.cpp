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

	//アニメーション
	m_polygon.SetUVRect((int)m_animeCnt);
	m_animeCnt += m_animeSpeed;

	//アニメーションをループ
	if (m_animeCnt >= 5)
	{
		m_animeCnt = 0;
	}

	//======================================================
	//当たり判定
	//======================================================

	//球判定用の変数を作成
	KdCollider::SphereInfo sphereInfo;
	//球の中心位置を設定
	sphereInfo.m_sphere.Center = GetPos() + Math::Vector3(0, 0.5f, 0);
	//球の判定を設定
	sphereInfo.m_sphere.Radius = m_attackArea;
	//当たり判定をしたいタイプを設定
	sphereInfo.m_type = KdCollider::TypeDamage;

	//デバッグ用判定エリア
	//m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius, kRedColor);

	//球情報と当たり判定
	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		hit = obj->Intersects(sphereInfo, nullptr);

		//攻撃が当たった場合
		if (hit)
		{
			if (obj->GetObjType() == ObjectType::Enemy)
			{

				//HIT時の相手オブジェクトの処理
				obj->OnHit();

				//Hitした時の自分の処理
				OnHit();

				//ループから抜ける
				break;
			}
		}
	}
	m_pos += m_dir * m_speed;
}

void P_Bullet::PostUpdate()
{
	//座標更新
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

	//画像分割
	m_polygon.SetSplit(5, 1);

	//原点変更 
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Top);

	//デバッグ用
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
