#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override {}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Init()override;
private:

	std::shared_ptr<KdModelData> m_model = nullptr;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;

	float m_thrust;
	float m_thrustspeed;
	float m_thrustoffspeed;
	float m_thrustMax;
	float m_thrustMin;

	Math::Vector3 m_inertia;
	Math::Vector3 m_modeldir;

	float m_speed;

	float m_anime;

	float m_scale;

	float m_gravity;

	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;

	float m_deg;
};