#pragma once

class P_Bullet :public KdGameObject
{
public:
	P_Bullet() { Init(); }
	~P_Bullet()override {}

	void Update()override;
	void PostUpdate()override;

	void DrawLit()override;

	void Init()override;
	void OnHit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetRotate(float _rotateX) { m_rotateX = _rotateX; }
	void SetDir(Math::Vector3 _dir) { m_dir = _dir; }
	void SetSpeed(float _speed) { m_speed = _speed; }

private:
	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_dir = Math::Vector3::Zero;
	//アニメーション情報
	float m_animeCnt;
	float m_animeSpeed;

	Math::Vector3 m_attackDir;

	float m_attackArea;
	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;
	float m_speed;

	float m_time;
};