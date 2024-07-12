#include "Player.h"
#include"../../main.h"
#include"../../Scene/GameScene/GameScene.h"
#include"../Mousehit/Mousehit.h"
#include"../../Scene/SceneManager.h"
#include"../P_Bullet/P_Bullet.h"

void Player::Update()
{

	m_cooltime--;
	if (m_cooltime < 0)
	{
		m_cooltime = 0;
	}

	//自機のディグリー変更
	MousePos();
	float diffdeg = m_targetdeg - m_deg;
	if (diffdeg < 0)
	{
		diffdeg += 360;
	}

	float turnDeg = 6.0f;
	if (diffdeg < 180)
	{
		if (diffdeg < turnDeg)
		{
			turnDeg = diffdeg;
		}
		m_deg += turnDeg;

		if (m_deg > 360)
		{
			m_deg = m_deg - 360;
		}
		m_deg = (int)m_deg % 360;
	}
	else if (diffdeg > 180)
	{
		if (diffdeg < turnDeg)
		{
			turnDeg = diffdeg;
		}
		m_deg -= turnDeg;
		if (m_deg < 0)
		{
			m_deg = m_deg + 360;
		}
		m_deg = (int)(m_deg + 360) % 360;
	}
	//行列用変数にディグリーを代入
	m_rotateX = m_deg;

	//機体の回転
	turnDeg = 3.0f;
	diffdeg = m_deg - m_rotateZ;
	if (diffdeg < 0)
	{
		diffdeg += 360;
	}
	if (diffdeg < 180)
	{
		if (diffdeg < turnDeg)
		{
			turnDeg = diffdeg;
		}
		
		m_rotateZ += turnDeg;

		if (m_rotateZ > 360)
		{
			m_rotateZ = m_rotateZ - 360;
		}
		m_rotateZ = (int)m_rotateZ % 360;
	}
	else if (diffdeg > 180)
	{
		if (diffdeg < turnDeg)
		{
			turnDeg = diffdeg;
		}
		m_rotateZ -= turnDeg;
		if (m_rotateZ < 0)
		{
			m_rotateZ = m_rotateZ + 360;
		}
		m_rotateZ = (int)(m_rotateZ + 360) % 360;
	}



	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_gravity += 0.01f;
		if (m_gravity > 7.0f)
		{
			m_gravity = 7;
		}
		m_thrust = 0.005f;
		m_thrustoffspeed = m_speed;
		m_thrustoffspeed -= m_thrust;
		if (m_thrustoffspeed < m_thrustMin)
		{
			m_thrustoffspeed = m_thrustMin;
		}
		m_inertia.Normalize();
		m_dir = m_inertia;
		m_speed = m_thrustoffspeed;
		m_thrustspeed = 0;
		
	}
	else
	{

		m_inertia = m_inertia * m_thrustoffspeed;
		m_modeldir = GetMatrix().Backward();
		m_modeldir = m_modeldir * m_thrustspeed;

		m_thrust = 0.3f;
		m_thrustoffspeed -= m_thrust;
		if (m_thrustoffspeed < m_thrustMin)
		{
			m_thrustoffspeed = m_thrustMin;
		}
		m_thrustspeed += m_thrust;
		if (m_thrustspeed > m_thrustMax)
		{
			m_thrustspeed = m_thrustMax;
		}


		if (m_inertia.Length() >= m_modeldir.Length())
		{

			m_speed = m_thrustoffspeed - m_thrustspeed;
			m_inertia.Normalize();
			m_dir = m_inertia;
			m_gravity -= 0.05f;
			if (m_gravity < 0)
			{
				m_gravity = 0;
			}

		}
		else
		{
			m_modeldir = GetMatrix().Backward();
			m_dir = m_modeldir;
			m_speed = m_thrustspeed - m_thrustoffspeed;
			m_gravity -= 0.05f;
			if (m_gravity < 0)
			{
				m_gravity = 0;
			}
		}

	}

	if (m_cooltime <= 0)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			//自分流
			//std::shared_ptr<Attack> attack;
			//attack = std::make_shared<Attack>();//１メモリ確保
			//attack->Init();//２初期化
			//attack->SetPos(m_pos + (m_attackDir * 0.4f));
			//SceneManager::Instance().AddObject(attack);

			//攻撃オブジェクトを出現させる座標を確定する
			Math::Vector3 _attackPos;

			_attackPos = m_pos;
			_attackPos += GetMatrix().Backward() * 5.0;

			std::shared_ptr<P_Bullet> p_bullet;
			p_bullet = std::make_shared<P_Bullet>();//１メモリ確保
			p_bullet->Init();//２初期化
			p_bullet->SetPos(_attackPos);
			p_bullet->SetRotate(m_rotateX);
			p_bullet->SetDir(GetMatrix().Backward());
			p_bullet->SetSpeed(5.0f);
			SceneManager::Instance().AddObject(p_bullet);

			//攻撃SE再生
			//KdAudioManager::Instance().Play("Asset/Sounds/p_bullet.mp3");
		}
		m_cooltime = 5;
	}

	//// キャラクターの移動速度
	//Math::Vector3 nowPos = GetPos();
	//Math::Vector3 moveVec = m_TargetPos - nowPos;

	//moveVec.Normalize();
	//m_pos += moveVec * m_speed;

	//m_dir = m_TargetPos - GetPos();

	//m_dir += m_modeldir;

	//m_dir.Normalize();

	

	m_pos += m_dir * m_speed;

	m_pos.y -= m_gravity;

	m_pos.z = 0;

	m_inertia = m_dir;
	//m_speed = oldspeed;
	//攻撃
}

void Player::PostUpdate()
{
	//if (m_deg > 360)
	//{
	//	m_deg = m_deg - 360;
	//}
	//else if (m_deg < 0)
	//{
	//	m_deg = m_deg + 360;
	//}
	if (m_pos.x > 1600.0f)
	{
		m_pos.x = 1600.0f;
	}
	else if(m_pos.x < -1600.0f)
	{
		m_pos.x = -1600.0f;
	}

	if (m_pos.y > 1300.0f)
	{
		m_pos.y = 1300.0f;
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
	if (!m_model) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::Init()
{
	m_objType = ObjectType::Player;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/Player.gltf");
	m_pos = { -1000,0,0 };
	m_dir = { 0,0,0 };
	m_scale = 1;

	m_thrust = 0.3f;
	m_thrustspeed = 3.0f;
	m_thrustMax = 3.0f;
	m_thrustMin = 0.0f;
	m_speed = 0.0f;

	m_anime = 0;

	m_modeldir = GetMatrix().Backward();

	m_gravity = 0;

	m_rotateX = 0;
	m_rotateY = 90;
	m_rotateZ = 0;
	m_deg = 0;
	m_TargetPos = {};
	m_rad = 0;
	m_cooltime = 0;
}

void Player::MousePos()
{
	//マウス座標を取得する
	POINT _mousePos;
	GetCursorPos(&_mousePos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);
	_mousePos.x -= 640 ;
	_mousePos.y -= 360 ;


	//std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
	//if (_camera)
	//{
	//	Math::Vector3 _camPos = _camera->GetCameraMatrix().Translation();

	//	Math::Vector3 _rayDir = Math::Vector3::Zero;

	//	float _rayRange = 1000.0f;
	//	//レイの発射方向を求める
	//	_camera->GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);

	//	//実際にレイを飛ばして衝突位置を求める
	//	const std::shared_ptr<KdGameObject> _mousehit = m_target.lock();
	//	if (_mousehit)
	//	{
	//		Math::Vector3 _endRayPos = _camPos + (_rayDir * _rayRange);
	//		KdCollider::RayInfo _rayInfo(KdCollider::TypeMouseHit, _camPos, _endRayPos);

	//		//実際の当たり判定の処理
	//		std::list<KdCollider::CollisionResult> _results;

	//		_mousehit->Intersects(_rayInfo, &_results);

	//		//結果が１つでも返ってきていたら
	//		if (_results.size())
	//		{
	//			for (const KdCollider::CollisionResult& result : _results)
	//			{
	//				m_TargetPos = result.m_hitPos;
	//			}
	//		}
	//	}
	//}

	/*Math::Vector3 scroll = { 0,0,0 };
	if (m_pos.x > 1400.0f)
	{
		scroll.x = (m_pos.x - 1400.0f) / 0.32f;
	}
	else if (m_pos.x < -1400.0f)
	{
		scroll.x = (m_pos.x + 1400.0f) / 0.32f;
	}
	if (m_pos.y > 1200.0f)
	{
		scroll.y = (m_pos.y - 1200.0f) / 0.275f;
	}

	_mousePos.x -= scroll.x;
	_mousePos.y += scroll.y;*/
	//_mousePos.y *= -1;

	const float x = _mousePos.x;
	const float y = _mousePos.y;
	m_rad = atan2(y, x);
	float radian = DirectX::XMConvertToDegrees(m_rad);
	if (radian < 0)
	{
		radian = radian + 360;
	}
	m_targetdeg = radian;
	m_mouse = _mousePos;
}

void Player::ImguiUpdate()
{
	ImGui::Text("m_pos : %f %f %f", m_pos.x,m_pos.y,m_pos.z);
	ImGui::Text("m_mouse : %d %d ", (long)m_mouse.x,(long)m_mouse.y);
	ImGui::Text("m_TargetPos : %f %f %f", m_TargetPos.x, m_TargetPos.y, m_TargetPos.z);
}
